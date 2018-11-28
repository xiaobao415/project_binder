all:
	g++ -fPIC -shared -o ../../systemlib/libhardwareservice.so LightsService.cpp NotificationService.cpp CansService.cpp CansCommService.cpp -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -I../../systemlib/include -I../../hardware/include -I../include -L ../../systemlib -llog -lutils -lbinder
clean:
	rm ../../systemlib/libhardwareservice.so
