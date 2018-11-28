#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T00:22:40
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/utils/utils.pri)
include($${PWD}/../../systemlibs/binder/binder.pri)
include($${PWD}/../../systemlibs/hardwareservice/hardwareservice.pri)
include($${PWD}/../../systemlibs/hardwareproxy/hardwareproxy.pri)
include($${PWD}/../../systemlibs/hardware/hardware.pri)
include($${PWD}/../../systemlibs/lights/lights.pri)

QT       += core

QT       -= gui

TARGET = systemserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H HAVE_IOCTL

SOURCES += \
    systemserver.cpp

#the program output path
DESTDIR += $${BIN_PATH}
#test goal lib
LIBS += -L$$LIBS_PATH -llog -lutils -lcutils -lbinder -lhardwareservice -lhardwareproxy -lhardware

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

HEADERS += \
