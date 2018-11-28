#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T02:38:11
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../../systemlibs/log/log.pri)

QT       += core

QT       -= gui

TARGET = test_log
CONFIG   += console
CONFIG   -= app_bundle
DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H HAVE_IOCTL



TEMPLATE = app


SOURCES += \
    testlog.cpp

#the program output path
DESTDIR += $${UT_PATH}
#test goal lib
LIBS += -L$$LIBS_PATH -llog

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH
