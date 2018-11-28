
#define LOG_TAG "LightsService"

#include "LightsService.h"

namespace android
{
	
	LightsService::LightsService()
	{
        m_pDevices = initNative();
		for (int i = 0; i < LIGHT_COUNT; i++) {
            m_pLights[i] = new Light(i, m_pDevices);
        }
	}

	LightsService::~LightsService()
	{
        finalize(m_pDevices);
		for (int i = 0; i < LIGHT_COUNT; i++) {
            delete m_pLights[i];
        }
	}

    light_device_t* LightsService::getDevice(hw_module_t* module, char const* name)
	{
		int err;
	    hw_device_t* device;
	    err = module->methods->open(module, name, &device);
	    if (err == 0) {
	        return (light_device_t*)device;
	    } else {
	        return NULL;
	    }
	}
	
    Devices* LightsService::initNative()
	{
		int err;
	    hw_module_t* module;
	    Devices* devices;
	    
	    devices = (Devices*)malloc(sizeof(Devices));

	    err = hw_get_module(LIGHTS_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
	    if (err == 0) {
	        devices->lights[LIGHT_INDEX_FPGA_LED0]
                    = getDevice(module, LIGHT_ID_FPGA_LED0);
	        devices->lights[LIGHT_INDEX_FPGA_LED1]
                    = getDevice(module, LIGHT_ID_FPGA_LED1);
	        devices->lights[LIGHT_INDEX_FPGA_LED2]
                    = getDevice(module, LIGHT_ID_FPGA_LED2);
	        devices->lights[LIGHT_INDEX_FPGA_LED3]
                    = getDevice(module, LIGHT_ID_FPGA_LED3);
	        devices->lights[LIGHT_INDEX_LASER_CTRL]
                    = getDevice(module, LIGHT_ID_LASER_CTRL);
	        devices->lights[LIGHT_INDEX_XRAY_GANTRY_INDICATOR]
                    = getDevice(module, LIGHT_ID_XRAY_GANTRY_INDICATOR);
	        devices->lights[LIGHT_INDEX_XRAY_READY_INDICATOR]
                    = getDevice(module, LIGHT_ID_XRAY_READY_INDICATOR);
	        devices->lights[LIGHT_INDEX_XRAY_USE_INDICATOR]
                    = getDevice(module, LIGHT_ID_XRAY_USE_INDICATOR);
			devices->lights[LIGHT_INDEX_XRAY_CONTACTOR_CONTROL]
                    = getDevice(module, LIGHT_ID_XRAY_CONTACTOR_CONTROL);
	    } else {
	        memset(devices, 0, sizeof(Devices));
	    }

    	return devices;
	}

	void LightsService::finalize(Devices* devices)
	{	
	    if (devices == NULL) {
	        return;
	    }

	    free(devices);
	}
			
	Light* LightsService::getLight(int id)
	{
        return m_pLights[id];
	}

	Light::Light(int id, Devices* devices)
	{
        m_Id = id;
		m_iColor = -1;
		m_iMode = -1;
		m_iOnMS = -1;
		m_iOffMS = -1;
        m_pDevices = devices;
	}

	void Light::setBrightness(int brightness)
	{
		setBrightness(brightness, BRIGHTNESS_MODE_USER);
	}
	
	void Light::setBrightness(int brightness, int brightnessMode)
	{
		AutoMutex _l(m_Lock);		
		int color = brightness & 0x000000ff;
		color = 0xff000000 | (color << 16) | (color << 8) | color;
        setLightLocked(m_Id, color, LIGHT_FLASH_NONE, 0, 0, brightnessMode);
	}

	void Light::stopFlashing(int color)
	{
		AutoMutex _l(m_Lock);
        setLightLocked(m_Id, color, LIGHT_FLASH_NONE, 0, 0, 0);
	}

	void Light::setFlashing(int color, int mode, int onMS, int offMS)
	{
		AutoMutex _l(m_Lock);
        setLightLocked(m_Id, color, mode, onMS, offMS, BRIGHTNESS_MODE_USER);
	}

	void Light::setLightLocked(int id, int color, int mode, int onMS, int offMS, int brightnessMode)
	{	
        Devices* devices = m_pDevices;
		light_state_t state;

		if (color != m_iColor || mode != m_iMode || onMS != m_iOnMS || offMS != m_iOffMS) {
			m_iColor = color;
			m_iMode = mode;
			m_iOnMS = onMS;
			m_iOffMS = offMS;
			
			if (devices == NULL || id < 0 || id >= LIGHT_COUNT || devices->lights[id] == NULL) {
				return ;
			}
			
			memset(&state, 0, sizeof(light_state_t));
			state.color = color;
			state.flashMode = mode;
			state.flashOnMS = onMS;
			state.flashOffMS = offMS;
			state.brightnessMode = brightnessMode;
			
			devices->lights[id]->set_light(devices->lights[id], &state);
		}
	}
};
