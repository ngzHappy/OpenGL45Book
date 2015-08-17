include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)
include($$PWD/../openglBaseLibs.pri)


CONFIG +=  staticlib
TEMPLATE = lib

INCLUDEPATH+=$$PWD

QT+=core
QT+=gui
QT+=widgets
QT+=opengl

TARGET = QLOpenGLTool

HEADERS += \
    GLMTool.hpp \
    glm/common.hpp \
    glm/exponential.hpp \
    glm/ext.hpp \
    glm/fwd.hpp \
    glm/geometric.hpp \
    glm/glm.hpp \
    glm/integer.hpp \
    glm/mat2x2.hpp \
    glm/mat2x3.hpp \
    glm/mat2x4.hpp \
    glm/mat3x2.hpp \
    glm/mat3x3.hpp \
    glm/mat3x4.hpp \
    glm/mat4x2.hpp \
    glm/mat4x3.hpp \
    glm/mat4x4.hpp \
    glm/matrix.hpp \
    glm/packing.hpp \
    glm/trigonometric.hpp \
    glm/vec2.hpp \
    glm/vec3.hpp \
    glm/vec4.hpp \
    glm/vector_relational.hpp \
    OpenGLTool/OpenGLAPI.hpp \
    OpenGLTool/OpenGLTemplateString.hpp \
    OpenGLTool/QGLTools.hpp \
    OpenGLTool/OpenGLAPIPrivate/BaseType.hpp \
    OpenGLTool/OpenGLAPIPrivate/BufferFunction.hpp \
    OpenGLTool/OpenGLAPIPrivate/BufferType.hpp \
    OpenGLTool/OpenGLAPIPrivate/DrawFunctions.hpp \
    OpenGLTool/OpenGLAPIPrivate/FBOFunctionGL.hpp \
    OpenGLTool/OpenGLAPIPrivate/FBOTypeGL.hpp \
    OpenGLTool/OpenGLAPIPrivate/FunctionTexttureOpenglTool.hpp \
    OpenGLTool/OpenGLAPIPrivate/GlobalFunctionOpengl.hpp \
    OpenGLTool/OpenGLAPIPrivate/GLTemplateString.hpp \
    OpenGLTool/OpenGLAPIPrivate/IsFinishedGL.hpp \
    OpenGLTool/OpenGLAPIPrivate/OpenGLBase.hpp \
    OpenGLTool/OpenGLAPIPrivate/PointsOpengl.hpp \
    OpenGLTool/OpenGLAPIPrivate/PrivateVFSourceLoader.hpp \
    OpenGLTool/OpenGLAPIPrivate/ProgramFunction.hpp \
    OpenGLTool/OpenGLAPIPrivate/ProgramType.hpp \
    OpenGLTool/OpenGLAPIPrivate/QGLDebugTool.hpp \
    OpenGLTool/OpenGLAPIPrivate/TexttureOpenglTool.hpp \
    OpenGLTool/OpenGLAPIPrivate/VertexArrayFunction.hpp \
    OpenGLTool/OpenGLAPIPrivate/VertexArrayType.hpp \
    OpenGLTool/QInitializeDebugContext.hpp \
    OpenGLTool/QConsoleWidget.hpp \
    OpenGLTool/QConsoleWidgetPrivate.hpp \
    OpenGLTool/QGLApplication.hpp \
    OpenGLTool/ModelLoader.hpp \
    OpenGLTool/ModelLoaderCallbacks.hpp \
    OpenGLTool/OpenGLAPIPrivate/MultiSampleTextureRender.hpp \
    OpenGLTool/OpenGLAPIPrivate/TextureRender.hpp \
    GLEWGL/glew.h

SOURCES += \
    glew.c \
    OpenGLTool/QTInitDebugContext.cpp \
    OpenGLTool/QConsoleWidget.cpp \
    OpenGLTool/QGLApplication.cpp \
    boostscan.cpp \
    OpenGLTool/ModelLoader.cpp \
    OpenGLTool/ModelLoaderCallbacks.cpp

include($$PWD/QuaZip/quazip.pri)


CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
LIBS += -L$$OUT__DIR__BASE__/bind -lQLAssimp
}else{
DESTDIR = $$OUT__DIR__BASE__/bin
LIBS += -L$$OUT__DIR__BASE__/bin -lQLAssimp
}







