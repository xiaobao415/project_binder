all:
	g++ -fPIC -shared -o ../libbinder.so AppOpsManager.cpp Binder.cpp BpBinder.cpp BufferedTextOutput.cpp Debug.cpp IAppOpsCallback.cpp IAppOpsService.cpp IInterface.cpp IMemory.cpp IPCThreadState.cpp IPermissionController.cpp IServiceManager.cpp MemoryDealer.cpp MemoryBase.cpp MemoryHeapBase.cpp Parcel.cpp PermissionCache.cpp ProcessState.cpp Static.cpp TextOutput.cpp -I../include -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS -lpthread
clean:
	rm ../libbinder.so
	

