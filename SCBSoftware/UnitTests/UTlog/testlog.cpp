#define LOG_TAG "testlog"

#include <iostream>
#include <log/log.h>
#include <sys/time.h>
#include <limits.h>

int main(int argc, char** argv)
{
    int timeout2 = 5000;
    long reltime2 = timeout2 * 1000;
    struct timeval tv_timeout;
    tv_timeout.tv_sec = reltime2/1000000;
    tv_timeout.tv_usec = reltime2%1000000;
    if (tv_timeout.tv_usec >= 1000000) {
        tv_timeout.tv_usec -= 1000000;
        tv_timeout.tv_sec  += 1;
    }


    printf("LLONG_MAX=%lld, __WORDSIZE=%d\n", LLONG_MAX, __WORDSIZE);
    struct timeval now;
    struct timespec out_time;
    long long timeout = 5000;//1s
    long long reltime = timeout*1000000;



    gettimeofday(&now, NULL);
    out_time.tv_sec = now.tv_sec;
    out_time.tv_nsec = now.tv_usec * 1000;

    ALOGI("now tv_sec=%lu, tv_nsec=%lu", out_time.tv_sec, out_time.tv_nsec);


    out_time.tv_sec += reltime/1000000000;
    out_time.tv_nsec+= reltime%1000000000;
    if (out_time.tv_nsec >= 1000000000) {
        out_time.tv_nsec -= 1000000000;
        out_time.tv_sec  += 1;
    }

    ALOGI("abs tv_sec=%lu, tv_nsec=%lu", out_time.tv_sec, out_time.tv_nsec);

	if (argc < 2){
		ALOGI("Usage:\n");
		usleep(1000);
		ALOGI("%s <hello>\n", argv[0]);
		usleep(100);
		ALOGI("%s <hello> <name>\n", argv[0]);
		usleep(500);
		ALOGI("%s <hello> <name>\n", argv[0]);
		return -1;
	}

	return 0;
}

