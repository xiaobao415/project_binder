all:
	arm-linux-gnueabihf-g++ -o ../logcat logcat.cpp -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_IOCTL -I../../systemlib/include  -L ../../systemlib -lpthread -llog
clean:
	rm ../logcat
