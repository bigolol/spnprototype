TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../libs/googletest/googletest/googletest/build/release/ -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../libs/googletest/googletest/googletest/build/debug/ -lgtest
else:unix: LIBS += -L$$PWD/../../../libs/googletest/googletest/googletest/build/ -lgtest -lpthread

INCLUDEPATH += $$PWD/../../../libs/googletest/googletest/googletest/include
DEPENDPATH += $$PWD/../../../libs/googletest/googletest/googletest/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../libs/googletest/googletest/googletest/build/release/libgtest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../libs/googletest/googletest/googletest/build/debug/libgtest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../libs/googletest/googletest/googletest/build/release/gtest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../libs/googletest/googletest/googletest/build/debug/gtest.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../libs/googletest/googletest/googletest/build/libgtest.a

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

HEADERS += \
    spntest.h \
    mulitplicationlayertest.h \
    randomvarlayertest.h \
    additionlayertest.h
