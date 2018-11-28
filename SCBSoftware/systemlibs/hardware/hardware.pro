#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T01:14:50
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/utils/utils.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include(hardware.pri)

QT       -= core gui

CONFIG += warn_off

TARGET = hardware
TEMPLATE = lib

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

SOURCES += \
    hardware.c

HEADERS += \
    hardware.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -ldl -L$$LIBS_PATH -llog -lcutils

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

