system/core/include/cutils/uevent.h
#define SCM_CREDENTIALS 0x02  

struct ucred {
 unsigned int pid;
 unsigned int uid;
 unsigned int gid;
};


system/core/libcutils/sockets.c
struct ucred {
 __u32 pid;
 __u32 uid;
 __u32 gid;
};

ashmem-dev.c
