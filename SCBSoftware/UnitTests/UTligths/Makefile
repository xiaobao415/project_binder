all:
	arm-linux-gnueabihf-g++ -fPIC -o ../testligths test_ligths.cpp -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -I../../systemlib/include -I../../frameworks/include -L ../../systemlib -llog -lutils -lbinder -lcutils -lhardwareproxy
clean:
	rm ../testligths
