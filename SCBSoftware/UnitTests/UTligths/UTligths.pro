#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T04:23:04
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/utils/utils.pri)
include($${PWD}/../../systemlibs/binder/binder.pri)
include($${PWD}/../../systemlibs/hardwareproxy/hardwareproxy.pri)
include($${PWD}/../../systemlibs/hardware/hardware.pri)
include($${PWD}/../../systemlibs/hardwareservice/hardwareservice.pri)
QT       += core

QT       -= gui

TARGET = UTligths
CONFIG   += console
CONFIG   -= app_bundle
DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

TEMPLATE = app


SOURCES += \
    test_ligths.cpp

#the program output path
DESTDIR += $${UT_PATH}

LIBS += -L$$LIBS_PATH -llog -lutils -lbinder -lcutils -lhardwareproxy

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

HEADERS +=
