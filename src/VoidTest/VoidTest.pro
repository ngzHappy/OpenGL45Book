include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)
include($$PWD/../openglBaseLibs.pri)

QT+=core
TEMPLATE = app

TARGET = VoidTest

SOURCES += \
    main.cpp

HEADERS += \
    test.hpp

DISTFILES += \
    ../../ConfigureProject.py \
    ../../CopyDirTree.py \
    ../../fnmatchs.py \
    ../../zipProject.py \
    ../../createPNG.py \
    ../../randCreatePNG.py

win32-msvc*:CONFIG(debug,debug|release){
CONFIG *= console
}

CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
}else{
DESTDIR = $$OUT__DIR__BASE__/bin
}






