/**
  * @brief light application access interface
  * @author haigang.zhu
  * @date   2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */
#ifndef ANDROID_INOTIFICATIONSERVICE_H
#define ANDROID_INOTIFICATIONSERVICE_H

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

class INotificationService: public IInterface
{
public:
    DECLARE_META_INTERFACE(NotificationService);

    /**
     * @brief	set Brightness
     * @remark
     * @param[in] index:default=LIGHT_INDEX_FPGA_LED0 or LIGHT_INDEX_XRAY_GANTRY_INDICATOR and so on
     * @param[in] brightness 0~0xff
     * @return
     */
	virtual void setBrightness(int index, int brightness) = 0;

    /**
     * @brief	set Brightness
     * @remark
     * @param[in] index:LIGHT_INDEX_FPGA_LED0 and so on
     * @param[in] brightness 0~0xff
     * @param[in] brightnessMode : BRIGHTNESS_MODE_USER or BRIGHTNESS_MODE_SENSOR
     * @return
     */
	virtual void setBrightness(int index, int brightness, int brightnessMode) = 0;

    /**
     * @brief	stop Flashing
     * @remark
     * @param[in] index:LIGHT_INDEX_XRAY_GANTRY_INDICATOR and so on
     * @param[in] color 0~0xff
     * @return
     */
	virtual void stopFlashing(int index, int color) = 0;

    /**
     * @brief	set Flashing
     * @remark
     * @param[in] index:LIGHT_INDEX_XRAY_GANTRY_INDICATOR and so on
     * @param[in] color 0~0xff
     * @param[in] mode : LIGHT_FLASH_TIMED
     * @param[in] onMS: on ms
     * @param[in] offMS: off ms
     * @return
     */
	virtual void setFlashing(int index, int color, int mode, int onMS, int offMS) = 0;
};

// ----------------------------------------------------------------------------

class BnNotificationService: public BnInterface<INotificationService>
{
public:
    /**
     * @brief	The client send the request, and the server responds to different commands
     * @remark
     * @param[in] code:SETBRIGHTNESS,SETBRIGHTNESS2,SETFLASHING,STOPFLASHING,
     * @param[in] data :parameter of request
     * @param[out] reply:info of responds
     * @return 0 on succes, error code on failure.
     */
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

}; // namespace android

#endif // ANDROID_INOTIFICATIONSERVICE_H

