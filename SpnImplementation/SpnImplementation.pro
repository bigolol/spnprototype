TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

HEADERS += \
    spn.h \
    multiplicationlayer.h \
    randomvariablelayer.h \
    randomvariable.h \
    summationlayer.h \
    binaminaldistributionrandomvar.h \
    nodelayer.h \
    binaryrandomvar.h \
    spngenerator.h
