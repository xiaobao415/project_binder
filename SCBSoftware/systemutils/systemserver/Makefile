all:
	arm-linux-gnueabihf-g++ -fPIC -o ../systemserver systemserver.cpp -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -I../../systemlib/include -I../../frameworks/include -I../../hardware/include -L ../../systemlib -llog -lutils -lcutils -lbinder -lhardwareservice -lhardwareproxy -lhardware
clean:
	rm ../systemserver
