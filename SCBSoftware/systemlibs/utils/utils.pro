#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T19:47:56
#
#-------------------------------------------------
include($${PWD}/../../SCBSoftware.pri)
include($${PWD}/../systemlibs.pri)
include($${PWD}/../../systemlibs/cutils/cutils.pri)
include($${PWD}/../../systemlibs/log/log.pri)
include(utils.pri)

QT       -= core gui

TARGET = utils
TEMPLATE = lib
CONFIG += warn_off

DEFINES += HAVE_PTHREADS HAVE_SYS_UIO_H HAVE_ENDIAN_H HAVE_OFF64_T HAVE_POSIX_FILEMAP

SOURCES += \
    BasicHashtable.cpp \
    BlobCache.cpp \
    FileMap.cpp \
    JenkinsHash.cpp \
    LinearAllocator.cpp \
    LinearTransform.cpp \
    Log.cpp \
    Looper.cpp \
    misc.cpp \
    Printer.cpp \
    PropertyMap.cpp \
    RefBase.cpp \
    SharedBuffer.cpp \
    Static.cpp \
    StopWatch.cpp \
    String16.cpp \
    String8.cpp \
    SystemClock.cpp \
    Threads.cpp \
    Timers.cpp \
    Tokenizer.cpp \
    Unicode.cpp \
    VectorImpl.cpp


HEADERS += \
    utils/AndroidThreads.h \
    utils/ashmem.h \
    utils/Atomic.h \
    utils/BasicHashtable.h \
    utils/BitSet.h \
    utils/BlobCache.h \
    utils/ByteOrder.h \
    utils/Compat.h \
    utils/Condition.h \
    utils/Debug.h \
    utils/Endian.h \
    utils/Errors.h \
    utils/FileMap.h \
    utils/Flattenable.h \
    utils/Functor.h \
    utils/JenkinsHash.h \
    utils/KeyedVector.h \
    utils/LinearAllocator.h \
    utils/LinearTransform.h \
    utils/List.h \
    utils/Log.h \
    utils/Looper.h \
    utils/LruCache.h \
    utils/misc.h \
    utils/Mutex.h \
    utils/Printer.h \
    utils/PropertyMap.h \
    utils/RefBase.h \
    utils/RWLock.h \
    utils/SharedBuffer.h \
    utils/Singleton.h \
    utils/SortedVector.h \
    utils/StopWatch.h \
    utils/String16.h \
    utils/String8.h \
    utils/StrongPointer.h \
    utils/SystemClock.h \
    utils/Thread.h \
    utils/ThreadDefs.h \
    utils/threads.h \
    utils/Timers.h \
    utils/Tokenizer.h \
    utils/Trace.h \
    utils/TypeHelpers.h \
    utils/Unicode.h \
    utils/UniquePtr.h \
    utils/Vector.h \
    utils/VectorImpl.h \
    utils/CallStack.h \
    system/audio.h \
    system/audio_policy.h \
    system/camera.h \
    system/graphics.h \
    system/thread_defs.h \
    system/window.h \
    corkscrew/backtrace.h \
    corkscrew/demangle.h \
    corkscrew/map_info.h \
    corkscrew/ptrace.h \
    corkscrew/symbol_table.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -lpthread

INCLUDEPATH +=$$SYSTEMLIB_INCLUDEPATH
DEPENDPATH +=$$SYSTEMLIB_INCLUDEPATH

