all:
	g++ -fPIC -shared -o ../../systemlib/libhardwareproxy.so INotificationService.cpp ICansCommService.cpp -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -I../../systemlib/include -I../include -L ../../systemlib -llog -lutils -lbinder
clean:
	rm ../../systemlib/libhardwareproxy.so
