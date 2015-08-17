
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleBuffer.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleBuffer::ThisPrivate{
public:
    SimpleBuffer * super ;
    ThisPrivate(SimpleBuffer * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
}
    ~ThisPrivate(){}

    void paintGL(){
        GLuint buffer ;
        glCreateBuffers(1,&buffer);
        {
			const char str[] = "Hellow OpenGL!";
			glNamedBufferData(buffer, sizeof(str), str, GL_STATIC_DRAW);
        }
		qDebug()<<( (char *)glMapNamedBuffer(buffer, GL_READ_ONLY) );
		glUnmapNamedBuffer(buffer);
        glDeleteBuffers(1,&buffer);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleBuffer::SimpleBuffer(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleBuffer::~SimpleBuffer(){
    delete thisp;
}

void SimpleBuffer::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleBuffer::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleBuffer *);
std::unique_ptr<SimpleBuffer, PaintStateDeleteFunction>
paintState(this, [](SimpleBuffer * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleBuffer::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


