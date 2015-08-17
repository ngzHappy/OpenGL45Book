
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleClear.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleClear::ThisPrivate{
public:
    SimpleClear * super ;
    ThisPrivate(SimpleClear * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
}
    ~ThisPrivate(){}

    void paintGL(){
		gl::NamedFrameBufferObject root;
        static constexpr float clearColor[]={0.5f,0.6f,0.7f,1.0f};
		root.clearColor(clearColor);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleClear::SimpleClear(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleClear::~SimpleClear(){
    delete thisp;
}

void SimpleClear::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleClear::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleClear *);
std::unique_ptr<SimpleClear, PaintStateDeleteFunction>
paintState(this, [](SimpleClear * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleClear::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


