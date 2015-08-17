/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SinglePoint.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SinglePoint::ThisPrivate{
public:
    SinglePoint * super ;
    ThisPrivate(SinglePoint * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
        QGLDebugTool::setSimpleCallbackFunction();
        QGLDebugTool::test();
    #endif
        initializeGL();
}
    ~ThisPrivate(){
        gl::deleteAny(program,vao);
    }

    gl::Program program;
    gl::NamedVertexArrayObject vao;
    void initializeGL(){
        static constexpr char vertex_shader_source[]=R"(
                #version 450
                void main(void){
                    gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
                }
                                  )";
        static constexpr char fragment_shader_source[]=R"(
                #version 450
                out vec4 color;
                void main(void){
                     color = vec4(0.0, 0.8, 1.0, 1.0);
                }
                                  )";
        program = gl::VFProgramLoadSources(
                    vertex_shader_source,fragment_shader_source
                    );
        gl::createVertexArrays(1,&vao);
    }
    void paintGL(){
        gl::clearAll();
        gl::pointSize(32);
        gl::useProgram(program);
        gl::bindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, 1);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SinglePoint::SinglePoint(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SinglePoint::~SinglePoint(){
    delete thisp;
}

void SinglePoint::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SinglePoint::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SinglePoint *);
std::unique_ptr<SinglePoint, PaintStateDeleteFunction>
paintState(this, [](SinglePoint * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SinglePoint::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


