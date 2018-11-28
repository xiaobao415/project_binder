#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T01:27:43
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
#include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/hardware/hardware.pri)
include(lights.pri)

QT       -= core gui

TARGET = lights.default
TEMPLATE = lib

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

SOURCES += \
    lights.c

HEADERS += \
    lights.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$$LIBS_PATH -llog

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

QMAKE_CFLAGS += -Wno-unused-parameter
QMAKE_CFLAGS += -Wno-unused-variable
QMAKE_CFLAGS += -Wno-unused-function

CONFIG+=plugin
DESTDIR += $${HW_PATH}

