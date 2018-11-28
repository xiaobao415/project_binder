TEMPLATE = subdirs

SUBDIRS += \
    systemlibs \
    systemutils  \
    UnitTests 



#compile the project by order
CONFIG += ordered
CONFIG   += c++11
