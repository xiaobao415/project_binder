


//#define LOG_NDEBUG 0
#define LOG_TAG "NotificationService"
#include <utils/Log.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>

#include "NotificationService.h"

namespace android {

void NotificationService::instantiate() {
    defaultServiceManager()->addService(
            String16("lights.notification"), new NotificationService());
}

NotificationService::NotificationService()
{
    ALOGV("NotificationService created");
    m_pLightsService = new LightsService();
}

NotificationService::~NotificationService()
{
}

void NotificationService::setBrightness(int index, int brightness)
{
    Light *light = m_pLightsService->getLight(index);
	light->setBrightness(brightness);
}

void NotificationService::setBrightness(int index, int brightness, int brightnessMode)
{	
    Light *light = m_pLightsService->getLight(index);
	light->setBrightness(brightness, 0);
}

void NotificationService::stopFlashing(int index, int color)
{
	
    Light *light = m_pLightsService->getLight(index);
	light->stopFlashing(color);
}

void NotificationService::setFlashing(int index, int color, int mode, int onMS, int offMS)
{
	
    Light *light = m_pLightsService->getLight(index);
	light->setFlashing(color, mode, onMS, offMS);
}
	

} // namespace android
