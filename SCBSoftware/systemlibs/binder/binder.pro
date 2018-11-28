#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T00:03:39
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/utils/utils.pri)
include(binder.pri)

QT       -= core gui

TARGET = binder
TEMPLATE = lib

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H HAVE_ENDIAN_H HAVE_ANDROID_OS

CONFIG += warn_off

SOURCES += \
    AppOpsManager.cpp \
    Binder.cpp \
    BpBinder.cpp \
    BufferedTextOutput.cpp \
    Debug.cpp \
    IAppOpsCallback.cpp \
    IAppOpsService.cpp \
    IInterface.cpp \
    IMemory.cpp \
    IPCThreadState.cpp \
    IPermissionController.cpp \
    IServiceManager.cpp \
    MemoryBase.cpp \
    MemoryDealer.cpp \
    MemoryHeapBase.cpp \
    Parcel.cpp \
    PermissionCache.cpp \
    ProcessState.cpp \
    Static.cpp \
    TextOutput.cpp

HEADERS += \
    binder/AppOpsManager.h \
    binder/Binder.h \
    binder/BinderService.h \
    binder/BpBinder.h \
    binder/BufferedTextOutput.h \
    binder/Debug.h \
    binder/IAppOpsCallback.h \
    binder/IAppOpsService.h \
    binder/IBinder.h \
    binder/IInterface.h \
    binder/IMemory.h \
    binder/IPCThreadState.h \
    binder/IPermissionController.h \
    binder/IServiceManager.h \
    binder/MemoryBase.h \
    binder/MemoryDealer.h \
    binder/MemoryHeapBase.h \
    binder/Parcel.h \
    binder/PermissionCache.h \
    binder/ProcessState.h \
    binder/TextOutput.h \
    private/binder/binder_module.h \
    private/binder/Static.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


LIBS += -lpthread -L$$LIBS_PATH -lcutils -lutils

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

