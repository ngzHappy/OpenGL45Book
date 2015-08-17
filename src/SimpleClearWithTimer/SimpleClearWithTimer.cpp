/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleClearWithTimer.hpp"
#include <memory>
#include <cstdlib>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
#include <QTimer>
class SimpleClearWithTimer::ThisPrivate{
public:
    SimpleClearWithTimer * super ;
    QTimer * timer =0;
    float clearColor[4]{0.1f,0.3f,0.5f,1.0f};
    ThisPrivate(SimpleClearWithTimer * s):super(s){
        timer = new QTimer ;
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        typedef void(QTimer::*TT)();
        timer->connect(timer,TT(&QTimer::timeout),[this](){
            auto rand0_1 = []()->float{return float(rand()%1000)/1000;};
            clearColor[0]=rand0_1();
            clearColor[1]=rand0_1();
            clearColor[2]=rand0_1();
            super->updateGL();
        });
        timer->start(1000);
}
    ~ThisPrivate(){
        timer->stop();
        timer->deleteLater();
    }

    void paintGL(){
		gl::NamedFrameBufferObject root;
		root.clearColor(clearColor);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleClearWithTimer::SimpleClearWithTimer(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleClearWithTimer::~SimpleClearWithTimer(){
    delete thisp;
}

void SimpleClearWithTimer::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleClearWithTimer::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleClearWithTimer *);
std::unique_ptr<SimpleClearWithTimer, PaintStateDeleteFunction>
paintState(this, [](SimpleClearWithTimer * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleClearWithTimer::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


