
#define LOG_TAG "cans"
#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "cans.h"

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

const char *can_states[CAN_STATE_MAX] = {
    "ERROR-ACTIVE",
    "ERROR-WARNING",
    "ERROR-PASSIVE",
    "BUS-OFF",
    "STOPPED",
    "SLEEPING"
};

static int do_show_state(const char *name)
{
    int ret = -1;
    int state = -1;
    ret = can_get_state(name, &state);
    if(ret < 0)
        return ret;
    if (state >= 0 && state < CAN_STATE_MAX)
        ALOGI("%s state: %s\n",name, can_states[state]);
    return state;
}

static int connectCan(struct can_device_t* dev, struct can_filter *filter, int filter_count, int bitrate)
{
    int ret = -1;
    struct can_bittiming bt;
    struct can_ctrlmode cm;
    struct ifreq ifr;
    int family = PF_CAN, type = SOCK_RAW, proto = CAN_RAW;
    int s = -1;
    char l_c8Command[128] = {0};
    memset(&cm, 0, sizeof(cm));

    ret = can_do_stop(dev->name);
    if(ret < 0)
        return ret;
    ret = do_show_state(dev->name);
    if(ret < 0)
        return ret;

    ret = can_set_bitrate(dev->name,bitrate);
    if(ret < 0)
        return ret;

    ret = can_get_bittiming(dev->name, &bt);
    if(ret < 0)
        return ret;
    else
        ALOGI("%s bitrate: %u, sample-point: %0.3f\n",dev->name, bt.bitrate,(float)((float)bt.sample_point / 1000));

    // 设置tx_queue_len
    memset(l_c8Command, 0, sizeof(l_c8Command));
    sprintf(l_c8Command, "echo %d > /sys/class/net/%s/tx_queue_len", 4096, dev->name);
    system(l_c8Command);

    cm.flags |= CAN_CTRLMODE_3_SAMPLES;
    cm.mask  |= CAN_CTRLMODE_3_SAMPLES;
    ret = can_set_ctrlmode(dev->name, &cm);
    if(ret < 0)
        return ret;

    ret = can_get_ctrlmode(dev->name, &cm);
    if(ret < 0)
        return ret;
    else
          ALOGI("%s ctrlmode:loopback[%s], listen-only[%s], tripple-sampling[%s],"
            "one-shot[%s], berr-reporting[%s]\n",dev->name,
            ((cm.flags) & CAN_CTRLMODE_LOOPBACK) ? "ON" : "OFF",
            ((cm.flags) & CAN_CTRLMODE_LISTENONLY) ? "ON" : "OFF",
            ((cm.flags) & CAN_CTRLMODE_3_SAMPLES) ? "ON" : "OFF",
            ((cm.flags) & CAN_CTRLMODE_ONE_SHOT) ? "ON" : "OFF",
            ((cm.flags) & CAN_CTRLMODE_BERR_REPORTING) ? "ON" : "OFF");

    ret = can_do_start(dev->name);
    if(ret < 0)
        return ret;
    ret = do_show_state(dev->name);
    if(ret < 0)
        return ret;

    if ((s = socket(family, type, proto)) < 0)
    {
            ALOGE("create socket error");
            return -1;
    }

    ALOGI("interface = %s, family = %d, type = %d, proto = %d\n",
               dev->name, family, type, proto);

    dev->addr.can_family = family;
    strncpy(ifr.ifr_name, dev->name, sizeof(ifr.ifr_name));
    if (ioctl(s, SIOCGIFINDEX, &ifr)) {
        ALOGE("ioctl SIOCGIFINDEX error");
        return -1;
    }
    dev->addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&(dev->addr), sizeof(dev->addr)) < 0) {
        ALOGE("socket bind error");
        if (s != -1)
        {
            close(s);
        }
        return -1;
    }

    dev->sockfd = s;

    if (filter)
    {
        if (setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, filter,
                   filter_count * sizeof(struct can_filter)) != 0) {
            ALOGE("setsockopt CAN_RAW_FILTER error");
            return -1;
        }
    }

	return 0;
}

static int disconnectCan(struct can_device_t* dev)
{
    int ret = -1;
    if(dev->sockfd >= 0)
    {
        close(dev->sockfd);
        dev->sockfd = -1;
    }
    ret = can_do_stop(dev->name);
    if(ret < 0)
        return ret;
    return  do_show_state(dev->name);
}


static int writeCan(struct can_device_t* dev, const struct can_frame *frame)
{
    int len = -1;
    if(dev->sockfd >= 0)
    {
        pthread_mutex_lock(&g_lock);
        len = sendto(dev->sockfd, frame, sizeof(struct can_frame), 0, (struct sockaddr*)&(dev->addr), sizeof(dev->addr));
        pthread_mutex_unlock(&g_lock);
        if (len == -1) {
             ALOGE("writeCan error=%d, 0x%x", errno,(unsigned int)frame);
             if(frame != NULL && errno == EINVAL)
             {
                ALOGE("writeCan EINVAL can_id=%d,can_dlc=%d,data=0x%x,0x%x\n",
                      frame->can_id, frame->can_dlc, frame->data[0],frame->data[1]);
             }
        }
        else if(len == 0)
        {
            ALOGE("writeCan len == 0 error=%d, 0x%x", errno,(unsigned int)frame);
            if(frame != NULL)
                ALOGE("writeCan EINVAL can_id=%d,can_dlc=%d,data=0x%x,0x%x\n",
                    frame->can_id, frame->can_dlc, frame->data[0],frame->data[1]);
        }
        else if (len < 0)
        {
            ALOGE("writeCan len < 0 error=%d, 0x%x", errno,(unsigned int)frame);
            if(frame != NULL)
                ALOGE("writeCan EINVAL can_id=%d,can_dlc=%d,data=0x%x,0x%x\n",
                    frame->can_id, frame->can_dlc, frame->data[0],frame->data[1]);
        }
        else if(len < (int)sizeof(struct can_frame))
        {
            ALOGE("write: incomplete CAN frame,errno=%d\n", errno);
            if(frame != NULL)
                ALOGE("writeCan EINVAL can_id=%d,can_dlc=%d,data=0x%x,0x%x\n",
                    frame->can_id, frame->can_dlc, frame->data[0],frame->data[1]);
        }

    }
    return len;

}

static int readCan(struct can_device_t* dev, struct can_frame *frame)
{
    int nbytes = -1;
    struct timeval tv_timeout;
    tv_timeout.tv_sec  = 0;
    tv_timeout.tv_usec = 500000;
    fd_set fs_read;
    int ret;
    struct sockaddr_can addr;
    socklen_t len = sizeof(dev->addr);

    if(dev->sockfd >= 0)
    {
        FD_ZERO(&fs_read);
        FD_SET(dev->sockfd, &fs_read);
        ret = select((int)dev->sockfd + 1, &fs_read, NULL, NULL, &tv_timeout);
        if(ret == 0)
        {
            return ret;
        }
        else if(ret < 0)
        {
            ALOGE("select can error=%d", errno);
            return ret;
        }

        pthread_mutex_lock(&g_lock);
        nbytes = recvfrom(dev->sockfd, frame, sizeof(struct can_frame), 0, (struct sockaddr *)&(addr), &len);
        pthread_mutex_unlock(&g_lock);

        if(nbytes < 0)
        {
            ALOGE("read can error=%d", errno);
        }
        else if(nbytes < (int)sizeof(struct can_frame))
        {
            ALOGE("read: incomplete CAN frame,errno=%d\n", errno);
        }
    }
    return nbytes;
}

static int close_cans(struct hw_device_t *dev)
{
    disconnectCan((struct can_device_t*)dev);

    pthread_mutex_destroy(&g_lock);

    if (dev)
        free(dev);

    return 0;
}

/* Initializations */
void init_globals () {
    pthread_mutex_init (&g_lock, NULL);
}

static int open_cans(const struct hw_module_t *module, char const *name,
						struct hw_device_t **device)
{

//    ALOGD("open_cans: open with %s", name);

    if (strcmp(CAN_ID_FPGA, name) == 0 || strcmp(CAN_ID_HPS, name) == 0)
    {

    }
    else
        return -EINVAL;
	
    pthread_once (&g_init, init_globals);

	struct can_device_t *dev = (struct can_device_t *)malloc(sizeof(struct can_device_t));
	memset(dev, 0, sizeof(*dev));

	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (struct hw_module_t *)module;
	dev->common.close = close_cans;
    dev->connectCan = connectCan;
    dev->disconnectCan = disconnectCan;
	dev->writeCan = writeCan;
	dev->readCan = readCan;
    memcpy(dev->name, name, strlen(name));
    dev->sockfd = -1;

	*device = (struct hw_device_t *)dev;

//    ALOGD("%s exit", __func__);
	return 0;
}

static struct hw_module_methods_t cans_module_methods = {
    .open = open_cans,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = CANS_HARDWARE_MODULE_ID,
    .name = "cans Module",
    .methods = &cans_module_methods,
};

const char* getSvnVersion()
{
    return VER;
}
