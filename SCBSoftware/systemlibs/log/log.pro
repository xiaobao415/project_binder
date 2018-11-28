#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T00:40:54
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
#the lib project include file(pri)
include($${PWD}/../systemlibs.pri)
include(log.pri)

QT       -= core gui

TARGET = log
TEMPLATE = lib
CONFIG += plugin
DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

SOURCES += \
    event_tag_map.c \
    logd_write.c \
    logprint.c

HEADERS += \
    android/log.h \
    log/event_tag_map.h \
    log/log.h \
    log/logd.h \
    log/logger.h \
    log/logprint.h \
    log/uio.h


QMAKE_CFLAGS += -Wno-unused-parameter
QMAKE_CFLAGS += -Wno-unused-variable
QMAKE_CFLAGS += -Wno-unused-function

