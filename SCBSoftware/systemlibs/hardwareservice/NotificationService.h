/**
  * @brief the server responds to different commands, process internal operation
  * @author haigang.zhu
  * @date   2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */

#ifndef ANDROID_NOTIFICATIONSERVICE_H
#define ANDROID_NOTIFICATIONSERVICE_H

#include <stdint.h>
#include <sys/types.h>
#include <utils/Errors.h>  // for status_t
#include <utils/String8.h>

#include "INotificationService.h"
#include "LightsService.h"


namespace android {

class NotificationService : public BnNotificationService
{

public:
    /**
    * @brief add light service
    * @remark service name is lights.notification
    * @return
    */
    static  void                instantiate();

    /**
     * @brief
     * @remark Reference intface file
     * @return
     */
	virtual void setBrightness(int index, int brightness);
	virtual void setBrightness(int index, int brightness, int brightnessMode);
	virtual void stopFlashing(int index, int color);
	virtual void setFlashing(int index, int color, int mode, int onMS, int offMS);
	
private:

    NotificationService();
    virtual ~NotificationService();

private:
    sp<LightsService> m_pLightsService;
};

// ----------------------------------------------------------------------------

}; // namespace android

#endif // ANDROID_NOTIFICATIONSERVICE_H
