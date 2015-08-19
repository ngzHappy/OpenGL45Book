/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "TessellatedCube.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class TessellatedCube::ThisPrivate{
public:
    TessellatedCube * super ;
    ThisPrivate(TessellatedCube * s):super(s){
}
/****************************************************/
/****************************************************/
    ~ThisPrivate(){}
    void initializeGL(){

        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif

 }
    void paintGL(){
        //write your code here
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

TessellatedCube::TessellatedCube(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


TessellatedCube::~TessellatedCube(){
    delete thisp;
}

void TessellatedCube::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void TessellatedCube::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(TessellatedCube *);
std::unique_ptr<TessellatedCube, PaintStateDeleteFunction>
paintState(this, [](TessellatedCube * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void TessellatedCube::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


