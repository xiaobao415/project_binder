/**
  * @brief add Various services
  * @author haigang.zhu
  * @date 2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */

#define LOG_TAG "systemserver"
//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>

#include"NotificationService.h"

using namespace android;

int main(int argc, char** argv)
{
	sp<ProcessState> proc(ProcessState::self());
	
    //add Various services
	NotificationService::instantiate();

	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();

	return 0;
}


