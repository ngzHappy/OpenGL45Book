
include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)


TEMPLATE = app

QT+=core
QT+=widgets
QT+=gui
QT+=opengl

SOURCES+= \
    main.cpp \
    SimpleDebug.cpp
HEADERS+= \
    SimpleDebug.hpp



INCLUDEPATH+=$$PWD/../OpenGLTool


CONFIG *= console


CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
LIBS += -L$$OUT__DIR__BASE__/bind -lQLOpenGLTool

}else{
DESTDIR = $$OUT__DIR__BASE__/bin
LIBS += -L$$OUT__DIR__BASE__/bin -lQLOpenGLTool

}



include($$PWD/../openglBaseLibs.pri)



