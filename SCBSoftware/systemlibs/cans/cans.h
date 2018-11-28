/**
  * @brief can hardware operation
  * @author haigang.zhu
  * @date 2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */


#ifndef ANDROID_CANS_INTERFACE_H
#define ANDROID_CANS_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#include <poll.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <hardware.h>
#include "libsocketcan.h"

__BEGIN_DECLS

/**
 * The id of this module
 */
#define CANS_HARDWARE_MODULE_ID "cans"

/*
 * These can IDs correspond to logical cans
 */
#define CAN_ID_FPGA          			"can0"
#define CAN_ID_HPS          			"can1"


struct can_device_t {
    struct hw_device_t common;

    /**
     * @brief	connect can
     * @remark
     * @param[in] struct can_device_t* dev
     * @param[in] struct can_filter *filter
     * @param[in] filter_count
     * @param[in] bitrate
     * @return 0 on succes, error code on failure.
     */
    int (*connectCan)(struct can_device_t* dev, struct can_filter *filter, int filter_count, int bitrate);

    /**
     * @brief disconnect can
     * @remark
     * @param[in] struct can_device_t* dev
     * @return 0 on succes, error code on failure.
     */
    int (*disconnectCan)(struct can_device_t* dev);

    /**
     * @brief send frame to can device(eg,dcb board)
     * @remark
     * @param[in] struct can_device_t* dev
     * @param[in] struct can_frame *frame
     * @return write counts. > 0 success, <=0 error.
     */
    int (*writeCan)(struct can_device_t* dev, const struct can_frame *frame);

    /**
     * @brief read frame from scb
     * @remark
     * @param[in] struct can_device_t* dev
     * @param[out] struct can_frame *frame
     * @return read counts. > 0 success, <=0 error.
     */
    int (*readCan)(struct can_device_t* dev, struct can_frame *frame);

    char name[10];//can name
    int sockfd; //socket fd
    struct sockaddr_can addr;
};

/* return the code's svn version number
 * the version number is generated at compile time (code in pro file)
 */
const char* getSvnVersion();

__END_DECLS

#endif  // ANDROID_CANS_INTERFACE_H

