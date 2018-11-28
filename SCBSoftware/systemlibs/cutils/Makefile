#cp  prebuilts/ndk/9/platforms/android-18/arch-arm/usr/include/sys/_system_properties.h system_properties.h /usr/include/linux
#cp  prebuilts/ndk/9/platforms/android-18/arch-arm/usr/include/linux/compat.h /usr/include/linux
#cp kernel/drivers/staging/android/ashmem.h /usr/include/linux
#not add file of debugger.c,trace.c,android_reboot.c,qtaguid.c,str_parms.c
all:
	gcc -fPIC -shared -o ../libcutils.so hashmap.c atomic.c native_handle.c socket_inaddr_any_server.c socket_local_client.c socket_local_server.c socket_loopback_client.c socket_loopback_server.c socket_network_client.c sockets.c config_utils.c cpu_info.c load_file.c list.c open_memstream.c strdup16to8.c strdup8to16.c record_stream.c process_name.c threads.c sched_policy.c iosched_policy.c ashmem-dev.c klog.c partition_utils.c properties.c uevent.c memory.c -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DANDROID_SMP -D__x86_64__ -DHAVE_STRLCPY -DHAVE_ANDROID_OS -DHAVE_SYS_SOCKET_H -DHAVE_SYSTEM_PROPERTY_SERVER -I../include -lpthread
clean:
	rm ../libcutils.so
