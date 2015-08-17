/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleImageShow.hpp"
#include <memory>
#include <QImage>
#include <mutex>

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleImageShow::ThisPrivate{
public:
    SimpleImageShow * super ;
    ThisPrivate(SimpleImageShow * s):super(s){
        glClearDepth(1);
        glClearColor(0.1f,0.2f,0.3f,1);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
    gl::NamedTexture texture ;
    gl::Program program ;
    gl::NamedVertexArrayObject vao;
    std::recursive_mutex mutex;
    ~ThisPrivate(){
        gl::deleteAny(texture,vao,program);

    }
    void initializeGL(){
        gl::createVertexArrays(1,&vao);
        texture = gl::createTexture2D(":/image/testImage.jpg",GL_TEXTURE_RECTANGLE);
        static constexpr char vertex_shader_source[] = R"(
#version 450
uniform mat4 vertices=mat4(
 -1,    1,         0,    1.0000,//first column
 -1,   -1,         0,    1.0000,//second column
  1,    1,         0,    1.0000,//third column
  1,   -1,         0,    1.0000 //fourth column
);
out vec2 textureIndex;
void main(void){
    gl_Position = vertices[gl_VertexID];
    textureIndex = gl_Position.xy/2+0.5;
}

)";
        static constexpr char fragment_shader_source[] = R"(
#version 450
layout(binding=0) uniform sampler2DRect rectangleImageSampler   ;
in vec2 textureIndex;
out vec4 color;
void main(void){
    ivec2 tsize = textureSize(rectangleImageSampler );
    color = texelFetch(
                rectangleImageSampler   ,
                ivec2(tsize*textureIndex)
                );
}
)";
    program = gl::VFProgramLoadSources(
            vertex_shader_source,fragment_shader_source
            );
    glEnable(GL_DEPTH_TEST);
    }

    void paintGL(){
        gl::clearAll();
        if(texture){
            auto locker = program.use(&mutex);
            program.bindVertexArray(vao);
            program.bindTexture(texture, 0 ,GL_TEXTURE_RECTANGLE );
            gl::drawArrays(gl::DrawArraysMode::TRIANGLE_STRIP,0,4);
            (void) locker;
        }

    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleImageShow::SimpleImageShow(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleImageShow::~SimpleImageShow(){
    delete thisp;
}

void SimpleImageShow::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleImageShow::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleImageShow *);
std::unique_ptr<SimpleImageShow, PaintStateDeleteFunction>
paintState(this, [](SimpleImageShow * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleImageShow::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}

void SimpleImageShow::showImage(const QString & imagePath){
    QString path = imagePath;
    if(path.startsWith("file:///")){
        path=path.mid(8);
    }
    auto imageTexture2D = gl::createTexture2D(path,GL_TEXTURE_RECTANGLE );
    if(imageTexture2D){
        gl::deleteAny( thisp->texture );
        thisp->texture = imageTexture2D;
        this->updateGL();
    }
}

