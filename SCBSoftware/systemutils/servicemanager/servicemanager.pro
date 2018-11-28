#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T00:15:58
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)

QT       += core

QT       -= gui

TARGET = servicemanager
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += warn_off

TEMPLATE = app


SOURCES += \
    binder.c \
    service_manager.c

HEADERS += \
    binder.h

#the program output path
DESTDIR += $${BIN_PATH}
#test goal lib
LIBS += -L$$LIBS_PATH -llog

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

