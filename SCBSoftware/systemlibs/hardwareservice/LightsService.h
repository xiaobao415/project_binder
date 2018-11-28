/**
  * @brief  logic of light operation
  * @author haigang.zhu
  * @date   2018.4.24
  * @detail
  * @version
  * @warning
  * @note
  * @copyright   Copyright(C): FMI Medical Systems 2018. All rights reserved.
  */

#ifndef LIGHTSSERVICE_H
#define LIGHTSSERVICE_H

#include <utils/Log.h>
#include <utils/RefBase.h>
#include <utils/Mutex.h>
#include <hardware.h>
#include "lights.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"HardwareService.h"

namespace android
{						
	struct Devices {
    	light_device_t* lights[LIGHT_COUNT];
	};

	class Light
	{
		private:
            int m_Id;
            int m_iColor;
            int m_iMode;
            int m_iOnMS;
            int m_iOffMS;
            Mutex m_Lock;
            Devices* m_pDevices;//light devices
			
            /**
             * @brief
             * @remark param reference struct light_state_t
             * @param[in] id
             * @param[in] color
             * @param[in] mode
             * @param[in] onMS
             * @param[in] offMS
             * @param[in] brightnessMode
             * @return
             */
			void setLightLocked(int id, int color, int mode, int onMS, int offMS, int brightnessMode);

		public:
			Light(int id, Devices* devices);

            /**
             * @brief
             * @remark Reference intface file
             * @return
             */
			void setBrightness(int brightness);
			void setBrightness(int brightness, int brightnessMode);
			void stopFlashing(int color);
			void setFlashing(int color, int mode, int onMS, int offMS);
		
	};
	
	class LightsService : public virtual RefBase
	{			
		public:			
			LightsService();
			~LightsService();

            /**
             * @brief find light by id
             * @remark
             * @param[in] id
             * @param[out] Light*
             * @return
             */
			Light* getLight(int id);
			
		private:
            Light *m_pLights[LIGHT_COUNT];
			Devices* m_pDevices;
			
            /**
             * @brief init light devices
             * @remark
             * @return
             */
            Devices* initNative();

            /**
             * @brief uninit light devices
             * @remark
             * @return
             */
			void finalize(Devices* devices);

            /**
             * @brief get light device by name
             * @remark
             * @return light_device_t*
             */
            light_device_t* getDevice(hw_module_t* module, char const* name);
	};
	
};

#endif

