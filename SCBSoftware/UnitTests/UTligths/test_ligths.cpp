#define LOG_TAG "testlights"

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include "INotificationService.h"
#include "HardwareService.h"

using namespace android;

int main(int argc, char** argv)
{
	if (argc < 2){
		ALOGI("Usage:\n");
		ALOGI("%s cmd\n", argv[0]);
		ALOGI("cmd:f(flash) s(stop flash and off) o(stop flash and on) i(led on) m(led off)\n", argv[0]);
		return -1;
	}

    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder = sm->getService(String16("lights.notification"));

	sp<INotificationService> service = interface_cast<INotificationService>(binder);
	
	if (binder == 0)
	{
        ALOGI("can't get hello service\n");
		return -1;
	}
	
	if(argv[1][0] == 'f')
	{
		for(int i = 0; i < 4; i++)
		{		
			service->setFlashing(i, 0xff, LIGHT_FLASH_TIMED , 20, 100);
		}
	}
	else if(argv[1][0] == 's')
	{
		for(int i = 0; i < 4; i++)
		{		
			service->stopFlashing(i, 0xff);//stopFlashing and led off
		}
	}
	else if(argv[1][0] == 'o')
	{
		for(int i = 0; i < 4; i++)
		{		
			service->stopFlashing(i, 0);//stopFlashing and led on
		}
	}
	else if(argv[1][0] == 'i')//led off
	{
		service->setBrightness(LIGHT_INDEX_LASER_CTRL, 0xff);
		service->setBrightness(LIGHT_INDEX_XRAY_GANTRY_INDICATOR, 0xff);
		service->setBrightness(LIGHT_INDEX_XRAY_READY_INDICATOR, 0xff);
		service->setBrightness(LIGHT_INDEX_XRAY_USE_INDICATOR, 0xff);
		service->setBrightness(LIGHT_INDEX_XRAY_CONTACTOR_CONTROL, 0xff);
	}
	else if(argv[1][0] == 'm')//led on
	{
		service->setBrightness(LIGHT_INDEX_LASER_CTRL, 0);
		service->setBrightness(LIGHT_INDEX_XRAY_GANTRY_INDICATOR, 0);
		service->setBrightness(LIGHT_INDEX_XRAY_READY_INDICATOR, 0);
		service->setBrightness(LIGHT_INDEX_XRAY_USE_INDICATOR, 0);
		service->setBrightness(LIGHT_INDEX_XRAY_CONTACTOR_CONTROL, 0);
	}
	return 0;
}

