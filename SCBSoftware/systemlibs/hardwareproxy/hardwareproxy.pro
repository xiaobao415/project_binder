#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T03:14:08
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/utils/utils.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/binder/binder.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include($${PWD}/../../systemlibs/hardwareservice/hardwareservice.pri)

include(hardwareproxy.pri)



QT       -= core gui

TARGET = hardwareproxy
TEMPLATE = lib

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H

SOURCES += \
    INotificationService.cpp

HEADERS +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$$LIBS_PATH -llog -lcutils -lutils -lbinder

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

