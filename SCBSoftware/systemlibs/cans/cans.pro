#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T08:56:38
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/hardware/hardware.pri)
include($${PWD}/../../systemlibs/socketcan/socketcan.pri)
include(cans.pri)

QT       -= core gui

TARGET = cans.default
TEMPLATE = lib

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

SOURCES += \
    cans.c

HEADERS += \
    cans.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$$LIBS_PATH -llog -lsocketcan

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

QMAKE_CFLAGS += -Wno-unused-parameter
QMAKE_CFLAGS += -Wno-unused-variable
QMAKE_CFLAGS += -Wno-unused-function

CONFIG+=plugin
DESTDIR += $${HW_PATH}

unix{
    CODE_ISDIFF = $$system(svn diff $${PWD} |wc -l)
    CODE_VERSION = $$system(svn info $${PWD} |grep \'Changed Rev\'| cut -d : -f 2)
    VERSTR = '$${CODE_VERSION}'
    isEqual(CODE_ISDIFF, 0){
        #message($$VERSTR)
        VERSTR = '\\"0000$${VERSTR}\\"'
    }else{
        VERSTR = '\\"FFFF$${VERSTR}\\"'
    }
    message($${PWD}$$VERSTR)
    DEFINES += VER=$$VERSTR
}
