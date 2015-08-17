/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawArrays.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <memory>
#include <mutex>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDrawArrays::ThisPrivate{
public:
    SimpleDrawArrays * super ;
    ThisPrivate(SimpleDrawArrays * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
	gl::Program program;
	gl::NamedVertexArrayObject vao;
 
    ~ThisPrivate(){
		gl::deleteAny(program,vao);
	}
    void initializeGL(){
		static constexpr char vertex_shader_source[] = R"(
#version 450
uniform mat4 vertices=mat4(
 -1,    1,         0.5,    2.0000,//first column
 -1,   -1,         0.6,    2.0000,//second column
  1,    1,         0.7,    2.0000,//third column
  1,   -1,         0.8,    2.0000 //fourth column
);
out vec4 color;
void main(void){
    gl_Position = vertices[gl_VertexID]/2 ;
	color = vec4( gl_Position.x/3+0.5,gl_Position.y/3+0.5,gl_Position.z,1 );
}

)";
		static constexpr char fragment_shader_source[] = R"(
#version 450
in vec4 color;
out vec4 finalColor;
void main(void){
    finalColor = color;
}
)";
		program = gl::VFProgramLoadSources(
			vertex_shader_source,
			fragment_shader_source
			);
		gl::createVertexArrays(1,&vao);
	}
    void paintGL(){
		gl::clearAll();
		{
			auto locker = program.use(QGLApplication::atomicFunction());
			program.bindVertexArray(vao);
			gl::pointSize(32);
			gl::drawArrays(gl::DrawArraysMode::POINTS, 0, 4);
			(void)locker;
		}
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawArrays::SimpleDrawArrays(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawArrays::~SimpleDrawArrays(){
    delete thisp;
}

void SimpleDrawArrays::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawArrays::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawArrays *);
std::unique_ptr<SimpleDrawArrays, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawArrays * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawArrays::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


