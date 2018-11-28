#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T19:47:56
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include(cutils.pri)

QT       -= core gui

TARGET = cutils
TEMPLATE = lib

CONFIG += warn_off

CONFIG(debug, debug|release){
    DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H ANDROID_SMP __x86_64__ HAVE_STRLCPY HAVE_ANDROID_OS HAVE_SYS_SOCKET_H HAVE_SYSTEM_PROPERTY_SERVER  
    SOURCES += \
            memory.c
}
else{
    DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H ANDROID_SMP __arm__ HAVE_ANDROID_OS HAVE_SYS_SOCKET_H HAVE_SYSTEM_PROPERTY_SERVER
    SOURCES += \
            arch-arm/memset32.S
}


SOURCES += \
    ashmem-dev.c \
    atomic.c \
    config_utils.c \
    cpu_info.c \
    hashmap.c \
    iosched_policy.c \
    klog.c \
    list.c \
    load_file.c \
    native_handle.c \
    open_memstream.c \
    partition_utils.c \
    process_name.c \
    properties.c \
    record_stream.c \
    sched_policy.c \
    socket_inaddr_any_server.c \
    socket_local_client.c \
    socket_local_server.c \
    socket_loopback_client.c \
    socket_loopback_server.c \
    socket_network_client.c \
    sockets.c \
    strdup16to8.c \
    strdup8to16.c \
    threads.c \
    uevent.c


HEADERS += \
    cutils/aref.h \
    cutils/ashmem.h \
    cutils/atomic-arm.h \
    cutils/atomic-inline.h \
    cutils/atomic-mips.h \
    cutils/atomic-x86.h \
    cutils/atomic.h \
    cutils/bitops.h \
    cutils/compiler.h \
    cutils/config_utils.h \
    cutils/cpu_info.h \
    cutils/debugger.h \
    cutils/dir_hash.h \
    cutils/fs.h \
    cutils/hashmap.h \
    cutils/iosched_policy.h \
    cutils/jstring.h \
    cutils/klog.h \
    cutils/list.h \
    cutils/log.h \
    cutils/memory.h \
    cutils/misc.h \
    cutils/multiuser.h \
    cutils/native_handle.h \
    cutils/open_memstream.h \
    cutils/partition_utils.h \
    cutils/process_name.h \
    cutils/properties.h \
    cutils/qtaguid.h \
    cutils/record_stream.h \
    cutils/sched_policy.h \
    cutils/sockets.h \
    cutils/str_parms.h \
    cutils/threads.h \
    cutils/trace.h \
    cutils/tztime.h \
    cutils/uevent.h \
    loghack.h \
    socket_local.h \
    private/android_filesystem_capability.h \
    private/android_filesystem_config.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -lpthread

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

