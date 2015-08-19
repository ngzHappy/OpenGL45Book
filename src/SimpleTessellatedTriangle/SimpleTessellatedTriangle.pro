
include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)


TEMPLATE = app

QT+=core
QT+=widgets
QT+=gui
QT+=opengl

SOURCES+= \
    main.cpp \
    SimpleTessellatedTriangle.cpp
HEADERS+= \
    SimpleTessellatedTriangle.hpp



INCLUDEPATH+=$$PWD/../OpenGLTool


win32-msvc*:{
CONFIG *= console
}

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



