#define LOG_TAG "NotificationService"

#include <stdint.h>
#include <sys/types.h>

#include <utils/Errors.h>  // for status_t
#include <utils/String8.h>
#include "INotificationService.h"


namespace android {

enum {
    SETBRIGHTNESS = IBinder::FIRST_CALL_TRANSACTION,
	SETBRIGHTNESS2,
    SETFLASHING,
    STOPFLASHING,
};

class BpNotificationService: public BpInterface<INotificationService>
{
public:
	BpNotificationService(const sp<IBinder>& impl)
        : BpInterface<INotificationService>(impl)
    {
    }

	virtual void setBrightness(int index, int brightness)
    {    	
		Parcel data, reply;
		data.writeInterfaceToken(INotificationService::getInterfaceDescriptor());
		data.writeInt32(index);
		data.writeInt32(brightness);		
		remote()->transact(SETBRIGHTNESS, data, &reply);
	}
	
	virtual void setBrightness(int index, int brightness, int brightnessMode)
	{		
		Parcel data, reply;
		data.writeInterfaceToken(INotificationService::getInterfaceDescriptor());
		data.writeInt32(index);
		data.writeInt32(brightness);
		data.writeInt32(brightnessMode);
		remote()->transact(SETBRIGHTNESS2, data, &reply);
	}
	
	virtual void stopFlashing(int index, int color)
	{		
		Parcel data, reply;
		data.writeInterfaceToken(INotificationService::getInterfaceDescriptor());
		data.writeInt32(index);
		data.writeInt32(color);		
		remote()->transact(STOPFLASHING, data, &reply);
	}
	
	virtual void setFlashing(int index, int color, int mode, int onMS, int offMS)
	{		
		Parcel data, reply;
		data.writeInterfaceToken(INotificationService::getInterfaceDescriptor());
		data.writeInt32(index);
		data.writeInt32(color);		
		data.writeInt32(mode); 	
		data.writeInt32(onMS); 	
		data.writeInt32(offMS);		
		remote()->transact(SETFLASHING, data, &reply);
	}
		
};

IMPLEMENT_META_INTERFACE(NotificationService, "android.lights.INotificationService");

// ----------------------------------------------------------------------

status_t BnNotificationService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch (code) {
        case SETBRIGHTNESS: {			
			CHECK_INTERFACE(INotificationService, data, reply);
			int index  = data.readInt32();
			int brightness  = data.readInt32();
			setBrightness(index, brightness);
            return NO_ERROR;
        } break;
        case SETBRIGHTNESS2: {
			CHECK_INTERFACE(INotificationService, data, reply);
			int index  = data.readInt32();
			int brightness  = data.readInt32();
			int brightnessMode  = data.readInt32();
			setBrightness(index, brightness, brightnessMode);
            return NO_ERROR;
        } break;		
        case SETFLASHING: {
			CHECK_INTERFACE(INotificationService, data, reply);
			int index  = data.readInt32();
			int color  = data.readInt32();
			int mode  = data.readInt32();
			int onMS  = data.readInt32();
			int offMS  = data.readInt32();
			setFlashing(index, color, mode, onMS, offMS);
            return NO_ERROR;
        } break;		
        case STOPFLASHING: {
			CHECK_INTERFACE(INotificationService, data, reply);
			int index  = data.readInt32();
			int color  = data.readInt32();
			stopFlashing(index, color);
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

}


