#cp prebuilts/ndk/9/platforms/android-18/arch-arm/usr/include/android/ -rfd buildroot_x4418/output/host/opt/ext-toolchain/arm-linux-gnueabihf/libc/usr/include
#≤ª±‡“ÎCallStack.cpp ProcessCallStack.cpp

all:
	g++ -fPIC -shared -o ../libutils.so BasicHashtable.cpp BlobCache.cpp FileMap.cpp JenkinsHash.cpp LinearAllocator.cpp LinearTransform.cpp Log.cpp Printer.cpp PropertyMap.cpp RefBase.cpp SharedBuffer.cpp Static.cpp StopWatch.cpp String8.cpp String16.cpp Threads.cpp Timers.cpp Tokenizer.cpp Unicode.cpp VectorImpl.cpp misc.cpp SystemClock.cpp Looper.cpp -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_OFF64_T -DHAVE_POSIX_FILEMAP -I../include -ldl -lpthread
clean:
	rm ../libutils.so
