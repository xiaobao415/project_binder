#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T19:41:07
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)

QT       += core

QT       -= gui

TARGET = logcat
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += warn_off

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H HAVE_IOCTL

TEMPLATE = app


SOURCES += \
    logcat.cpp

#the program output path
DESTDIR += $${BIN_PATH}
#test goal lib
LIBS += -lpthread -L$$LIBS_PATH -llog

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH
