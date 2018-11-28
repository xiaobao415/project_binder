/**
  * @brief application access enum
  * @author haigang.zhu
  * @date   2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */


#ifndef HARDWARESERVICE_H
#define HARDWARESERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>

namespace android
{
	
	/* ***********************1.light*************************************************
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

enum {
    LIGHT_INDEX_FPGA_LED0 = 0,
    LIGHT_INDEX_FPGA_LED1 = 1,
    LIGHT_INDEX_FPGA_LED2 = 2,
    LIGHT_INDEX_FPGA_LED3 = 3,
    LIGHT_INDEX_LASER_CTRL = 4,
    LIGHT_INDEX_XRAY_GANTRY_INDICATOR = 5,
    LIGHT_INDEX_XRAY_READY_INDICATOR = 6,
    LIGHT_INDEX_XRAY_USE_INDICATOR = 7,
    LIGHT_INDEX_XRAY_CONTACTOR_CONTROL = 8,
    LIGHT_COUNT
};


/* ***********************2.can*************************************************/
enum {
	    CAN_INDEX_FPGA = 0,
	    CAN_INDEX_HPS = 1,
	    CAN_COUNT
};

/* ***********************3.sernsor*************************************************/
enum {
        SENSOR_INDEX_HUMI_TEMP = 0,
        SENSOR_COUNT
};

/* ***********************4.input*************************************************/
struct RawEvent {
    int deviceId;
    struct input_event event;
};


enum
{
    SWITCH2 = 100,
    SWITCH4 = 101,
    TOUCH_SW1 = 102,
    TOUCH_SW2 = 103,
    TOUCH_SW3 = 104,
    TOUCH_SW4 = 105,
    ESTOP_OP_ST = 106,
    ESTOP_RG_ST = 107,
    ESTOP_LG_ST = 108,
    ESTOP_RS_ST = 109,
    ESTOP_FS_ST = 110,
    DOOR_SW = 111,
    ESTOP_ST = 112,//change XRAY_CTRL_ST to ESTOP_ST
    COVER_SW_BEHIND = 113,
    COVER_SW_FRONT = 114,
    INPUT_COUNT
};

/* ***********************5.dipswitch*************************************************/

/*DIP-SW1 D5-D0 system type*/
#define	MFCT_100    0x00		/* ScintCare CT16 framer	*/
#define	MFCT_101    0x01        /* ScintCare CT16 DCB       */
#define	MFCT_102    0x02		/* ScintCare CT16E          */
#define	MFCT_103    0x03		/* ScintCare CT16E kitty    */
#define	MFCT_104    0x04		/* ScintCare CT16B jupiter  */
#define	MFCT_201  	0x05		/* ScintCare CT16P          */
#define	MFCT_202 	0x06		/* ScintCare CT64           */
#define	MFCT_203  	0x07		/* ScintCare CT128          */
#define	MFCT_301  	0x08		/* ScintCare CT256          */

/*DIP-SW1 D7-D6 FPGA reserved*/

/*DIP-SW2 D4-D0 Tube*/
#define	HFG_TUBE00    0x00		/* Spellman 50kw(4393W)+Dunlee 2150 5.3MHU      */
#define	HFG_TUBE01    0x01      /* Spellman 50kw(4393NW)+Dunlee 2251 5.3MHU     */
#define	HFG_TUBE02    0x02		/* Spellman 50kw+Varian GS-517XX 5.47MHU        */
#define	HFG_TUBE03    0x03		/* Spellman 42kw+Varian GS-20722 2MHU           */
#define	HFG_TUBE04    0x04		/* Spellman 42kw+Varian GS-30722 3.5MHU         */
#define	HFG_TUBE05    0x05		/* Spellman 80kw+Dunlee 2280 8MHU               */
#define	HFG_TUBE06    0x06		/* Spellman 36kw+Varian GS-20722 2MHU           */
#define	HFG_TUBE07    0x07		/* Spellman 36kw+Varian GS-30722 3.5MHU         */
#define	HFG_TUBE08    0x08		/* xxxkw+xxx8MHU   CT256                        */

/*DIP-SW2 D5*/
#define USB_COVER 0
#define CAN_COVER 1

/*DIP-SW2 D6*/
#define ZHENZHENG 0
#define GALIL 1

/*DIP-SW2 D7*/
#define TABLE_SHORT 0
#define TABLE_LONG 1

/* ***********************6.uart*************************************************/
enum {
        UART_INDEX_TTYACM0 = 0,
        UART_INDEX_TTYACM1 = 1,
        UART_INDEX_TTYS1 = 2,
        UART_COUNT
};

#define UART_BUF 512

/**
 * struct uartFrame - uartFrame structure
 * @sendBuf: send buf
 * @sendLen: the data length field of the send frame
 * @recBuf:  recive frame.
 * @recLen: the data length field of the recive frame
 */
struct uart_frame {
    unsigned char sendBuf[UART_BUF];
    int sendLen;
    unsigned char recBuf1[UART_BUF];
    int recLen1;
    unsigned char recBuf2[UART_BUF];
    int recLen2;
};


}//end namespace


#endif

