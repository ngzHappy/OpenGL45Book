
include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)

TEMPLATE = app

QT+=core

win32-msvc*:{
CONFIG *= console
}

TARGET = projectModel
INCLUDEPATH+=$$PWD/../OpenGLTool

CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
LIBS += -L$$OUT__DIR__BASE__/bind -lQLOpenGLTool
LIBS += -L$$OUT__DIR__BASE__/bind -lQLAssimp
}else{
DESTDIR = $$OUT__DIR__BASE__/bin
LIBS += -L$$OUT__DIR__BASE__/bin -lQLOpenGLTool
LIBS += -L$$OUT__DIR__BASE__/bin -lQLAssimp
}

include($$PWD/../openglBaseLibs.pri)

SOURCES += \
    projectModel.cpp



