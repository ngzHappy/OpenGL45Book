
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDebug.hpp"
#include <memory>
 
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
 
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDebug::ThisPrivate{
public:
    SimpleDebug * super ;
    ThisPrivate(SimpleDebug * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
}
    ~ThisPrivate(){}

    void paintGL(){
        //write your code here
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDebug::SimpleDebug(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDebug::~SimpleDebug(){
    delete thisp;
}

void SimpleDebug::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDebug::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDebug *);
std::unique_ptr<SimpleDebug, PaintStateDeleteFunction>
paintState(this, [](SimpleDebug * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDebug::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


