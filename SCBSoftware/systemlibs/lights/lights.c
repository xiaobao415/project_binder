
#define LOG_TAG "lights"
#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdlib.h>
#include "lights.h"

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

static int write_int(char const *path, int value)
{
	int fd;
	static int already_warned = 0;
	fd = open(path, O_RDWR);
	if (fd < 0) {
		if (already_warned == 0) {
			ALOGE("write_int failed to open %s\n", path);
			already_warned = 1;
		}
		return -errno;
	}
	char buffer[20];
	int bytes = snprintf(buffer, sizeof(buffer), "%d\n", value);
	int written = write (fd, buffer, bytes);
	close(fd);
	return written == -1 ? -errno : 0;
}

static int write_string (const char *path, const char *value)
{
	int fd;
	static int already_warned = 0;
	fd = open(path, O_RDWR);
	if (fd < 0) {
		if (already_warned == 0) {
			ALOGE("write_string failed to open %s\n", path);
			already_warned = 1;
		}
		return -errno;
	}
	char buffer[20];
	int bytes = snprintf(buffer, sizeof(buffer), "%s\n", value);
	int written = write (fd, buffer, bytes);
	close(fd);
	return written == -1 ? -errno : 0;
}

static int rgb_to_brightness(struct light_state_t const *state)
{
	int color = state->color & 0x00ffffff;

	return ((77*((color>>16) & 0x00ff))
		+ (150*((color>>8) & 0x00ff)) + (29*(color & 0x00ff))) >> 8;
}


static int set_light_leds_indicator(struct light_device_t *dev,
			struct light_state_t const *state)
{
	int err = 0;	
	int brightness = rgb_to_brightness(state);
	char indicator_file[150] = {0};
	sprintf(indicator_file, "%s/brightness", dev->path);
	
	ALOGD("%s brightness=%d,color=0x%08x", __func__, brightness, state->color);
	pthread_mutex_lock(&g_lock);
	err = write_int(indicator_file, brightness);

	pthread_mutex_unlock(&g_lock);
	return err;
}

static int close_lights(struct hw_device_t *dev)
{
	pthread_mutex_destroy(&g_lock);

	if (dev)
		free(dev);

	return 0;
}

static int set_light_leds_fpga(struct light_device_t *dev, struct light_state_t const *state)
{
	int r, g, b;
	int delayOn,delayOff;	
	char led_file_trigger[150] = {0};
	char led_file_delayon[150] = {0};
	char led_file_delayoff[150] = {0};
	char led_file[150] = {0};
	
	sprintf(led_file_trigger, "%s/trigger", dev->path);		
	sprintf(led_file_delayon, "%s/delay_on", dev->path);		
	sprintf(led_file_delayoff, "%s/delay_off", dev->path);
	sprintf(led_file, "%s/brightness", dev->path);
	
	ALOGD("%s flashMode=%d onMS = %d offMS = %d color=0x%08x", __func__,state->flashMode,state->flashOnMS,state->flashOffMS,state->color);
	pthread_mutex_lock (&g_lock);
	
	delayOn = state->flashOnMS;
	delayOff = state->flashOffMS;
	if (state->flashMode != LIGHT_FLASH_NONE) {
		write_string (led_file_trigger, "timer");
		write_int (led_file_delayon, delayOn);
		write_int (led_file_delayoff, delayOff);
	} else {
		write_string (led_file_trigger, "none");
	}

	write_int (led_file, state->color);

	pthread_mutex_unlock (&g_lock);

    return 0;
}

/* Initializations */
void init_globals () {
	pthread_mutex_init (&g_lock, NULL);
}

static int open_lights(const struct hw_module_t *module, char const *name,
						struct hw_device_t **device)
{
	int (*set_light)(struct light_device_t *dev,
		struct light_state_t const *state);

//	ALOGD("open_lights: open with %s", name);

    if (strcmp(LIGHT_ID_LASER_CTRL, name) == 0 || strcmp(LIGHT_ID_XRAY_GANTRY_INDICATOR, name) == 0 ||
		strcmp(LIGHT_ID_XRAY_READY_INDICATOR, name) == 0 || strcmp(LIGHT_ID_XRAY_USE_INDICATOR, name) == 0 || 
		strcmp(LIGHT_ID_XRAY_CONTACTOR_CONTROL, name) == 0)
        set_light = set_light_leds_indicator;
    else if (strcmp(LIGHT_ID_FPGA_LED0, name) == 0 || strcmp(LIGHT_ID_FPGA_LED1, name) == 0 || 
		strcmp(LIGHT_ID_FPGA_LED2, name) == 0 || strcmp(LIGHT_ID_FPGA_LED3, name) == 0)
        set_light = set_light_leds_fpga;
    else
        return -EINVAL;

	pthread_once (&g_init, init_globals);
	
	struct light_device_t *dev = (struct light_device_t *)malloc(sizeof(struct light_device_t));
	memset(dev, 0, sizeof(*dev));

	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (struct hw_module_t *)module;
	dev->common.close = close_lights;
	dev->set_light = set_light;
	sprintf(dev->path,"/sys/class/leds/%s", name);
	
	*device = (struct hw_device_t *)dev;

//    ALOGD("%s exit", __func__);
	return 0;
}

static struct hw_module_methods_t lights_module_methods = {
    .open = open_lights,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "lights Module",
    .methods = &lights_module_methods,
};

