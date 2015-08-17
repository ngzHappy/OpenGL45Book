/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawElements.hpp"
#include <memory>
#include <cmath>

namespace {
	constexpr float operator""_d2r(long double value_) {
		return value_*3.141592654 / 180;
	}
}

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDrawElements::ThisPrivate{
public:
    SimpleDrawElements * super ;
    ThisPrivate(SimpleDrawElements * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
	gl::NamedBuffer pointsBuffer ;
	gl::NamedBuffer pointsIndexBuffer;
	gl::NamedVertexArrayObject vao;
	gl::Program program;
    ~ThisPrivate(){
		gl::deleteAny(pointsBuffer, pointsIndexBuffer,vao, program);
	}
    void initializeGL(){
		glClearColor(0.2f, 0.2f, 0.2f, 1);
		const static gl::Float points[] = {
			/*0*/std::cos(90.0_d2r),std::sin(90.0_d2r),0,1,
			/*1*/std::cos(90.0_d2r-72.0_d2r),std::sin(90.0_d2r - 72.0_d2r),0,1,
			/*2*/std::cos(90.0_d2r-2.0f*72.0_d2r),std::sin(90.0_d2r-2.0f*72.0_d2r),0,1,
			/*3*/std::cos(90.0_d2r-3.0f*72.0_d2r),std::sin(90.0_d2r-3.0f*72.0_d2r),0,1,
			/*4*/std::cos(90.0_d2r-4.0f*72.0_d2r),std::sin(90.0_d2r-4.0f*72.0_d2r),0,1,
		};
		constexpr static gl::UnsignedShort pointsIndex[] = {
			1,4,4,2,2,0,0,3,3,1,
		};

		gl::createBuffers(1,&pointsIndexBuffer);
		gl::createBuffers(1,&pointsBuffer);

		gl::bufferData(pointsBuffer, sizeof(points), points);
		gl::bufferData(pointsIndexBuffer,sizeof(pointsIndex), pointsIndex);

		gl::createVertexArrays(1,&vao);

		vao.bindBuffer(0, pointsBuffer, 0);
		vao.bindElementBuffer(pointsIndexBuffer);

		static constexpr char vertex_shader_source[] = R"(
#version 450
layout(location=0) in vec4 ipositon;

void main(void){
    gl_Position = ipositon ;
	
}

)";
		static constexpr char fragment_shader_source[] = R"(
#version 450
out vec4 finalColor;
void main(void){
    finalColor = vec4(1,0.6,0.1,1);
}
)";

		program = gl::VFProgramLoadSources(vertex_shader_source, fragment_shader_source);

	}
    void paintGL(){
		gl::clearAll();
		program.use();
		program.bindVertexArray(vao);
		gl::drawElements(
			gl::DrawElementsMode::LINES, 
			10, gl::DrawElementsType::UNSIGNED_SHORT);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawElements::SimpleDrawElements(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawElements::~SimpleDrawElements(){
    delete thisp;
}

void SimpleDrawElements::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawElements::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawElements *);
std::unique_ptr<SimpleDrawElements, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawElements * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawElements::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


