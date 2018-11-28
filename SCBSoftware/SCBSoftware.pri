#-------------------------------------------------
#
# Project include file created by weiqiang  2018-03-09T03:09:30
#
#-------------------------------------------------

#Only about project path set in thi file

CONFIG(debug, debug|release){
    LIBS_PATH =$${PWD}/../lib_x86
    HW_PATH=$${PWD}/../lib_x86/hw
    BIN_PATH =$${PWD}/../bin_x86
    UT_PATH =$${PWD}/../UnitTest_x86
}
else{
    LIBS_PATH =$${PWD}/../lib
    HW_PATH=$${PWD}/../lib/hw
    BIN_PATH =$${PWD}/../bin
    UT_PATH =$${PWD}/../UnitTest
}

SOFTWARE_TOP_PATH = $${PWD}

CONFIG += c++11
