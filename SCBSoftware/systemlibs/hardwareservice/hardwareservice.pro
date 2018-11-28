#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T01:49:13
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/utils/utils.pri)
include($${PWD}/../../systemlibs/binder/binder.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/hardware/hardware.pri)
include($${PWD}/../../systemlibs/lights/lights.pri)


include(hardwareservice.pri)


QT       -= core gui

TARGET = hardwareservice
TEMPLATE = lib

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

SOURCES += \
    LightsService.cpp \
    NotificationService.cpp


HEADERS += \
    LightsService.h \
    NotificationService.h
    UartsCommService.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$$LIBS_PATH -llog -lutils -lcutils -lbinder -lhardware -lhardwareproxy

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

