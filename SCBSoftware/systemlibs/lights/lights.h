/**
  * @brief light hardware operation
  * @author haigang.zhu
  * @date 2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */

#ifndef ANDROID_LIGHTS_INTERFACE_H
#define ANDROID_LIGHTS_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware.h>

__BEGIN_DECLS

/**
 * The id of this module
 */
#define LIGHTS_HARDWARE_MODULE_ID "lights"

/*
 * These light IDs correspond to logical lights, not physical.
 * So for example, if your INDICATOR light is in line with your
 * BUTTONS, it might make sense to also light the INDICATOR
 * light to a reasonable color when the BUTTONS are lit.
 */
#define LIGHT_ID_FPGA_LED0          			"fpga_led0"
#define LIGHT_ID_FPGA_LED1          			"fpga_led1"
#define LIGHT_ID_FPGA_LED2          			"fpga_led2"
#define LIGHT_ID_FPGA_LED3          			"fpga_led3"
#define LIGHT_ID_LASER_CTRL           			"laser_ctrl"
#define LIGHT_ID_XRAY_GANTRY_INDICATOR          "xray_gantry_indicator"
#define LIGHT_ID_XRAY_READY_INDICATOR           "xray_ready_indicator"
#define LIGHT_ID_XRAY_USE_INDICATOR      		"xray_use_indicator"
#define LIGHT_ID_XRAY_CONTACTOR_CONTROL         "xray_contactor_control"

	/* ***********************1.lights*************************************************
 * Flash modes for the flashMode field of light_state_t.
 */

#define LIGHT_FLASH_NONE            0

/**
 * To flash the light at a given rate, set flashMode to LIGHT_FLASH_TIMED,
 * and then flashOnMS should be set to the number of milliseconds to turn
 * the light on, followed by the number of milliseconds to turn the light
 * off.
 */
#define LIGHT_FLASH_TIMED           1

/**
 * To flash the light using hardware assist, set flashMode to
 * the hardware mode.
 */
#define LIGHT_FLASH_HARDWARE        2

/**
 * Light brightness is managed by a user setting.
 */
#define BRIGHTNESS_MODE_USER        0

/**
 * Light brightness is managed by a light sensor.
 */
#define BRIGHTNESS_MODE_SENSOR      1
/**
 * The parameters that can be set for a given light.
 *
 * Not all lights must support all parameters.  If you
 * can do something backward-compatible, you should.
 */
struct light_state_t {
    /**
     * The color of the LED in ARGB.
     *
     * Do your best here.
     *   - If your light can only do red or green, if they ask for blue,
     *     you should do green.
     *   - If you can only do a brightness ramp, then use this formula:
     *      unsigned char brightness = ((77*((color>>16)&0x00ff))
     *              + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
     *   - If you can only do on or off, 0 is off, anything else is on.
     *
     * The high byte should be ignored.  Callers will set it to 0xff (which
     * would correspond to 255 alpha).
     */
    unsigned int color;

    /**
     * See the LIGHT_FLASH_* constants
     */
    int flashMode;
    int flashOnMS;
    int flashOffMS;

    /**
     * Policy used by the framework to manage the light's brightness.
     * Currently the values are BRIGHTNESS_MODE_USER and BRIGHTNESS_MODE_SENSOR.
     */
    int brightnessMode;
};

struct light_device_t {
    struct hw_device_t common;

    /**
     * Set the provided lights to the provided values.
     *
     * Returns: 0 on succes, error code on failure.
     */
    int (*set_light)(struct light_device_t* dev,
            struct light_state_t const* state);
	char path[100];
};

/* return the code's svn version number
 * the version number is generated at compile time (code in pro file)
 */
const char* getSvnVersion();

__END_DECLS

#endif  // ANDROID_LIGHTS_INTERFACE_H

