/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawElementsInstancedBaseVertex.hpp"
#include <cmath>
#include <memory>
#include <QTimer>
namespace {
	constexpr float operator""_d2r( const long double d) {
		return float(d/180*3.141592654);
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
class SimpleDrawElementsInstancedBaseVertex::ThisPrivate{
public:
    SimpleDrawElementsInstancedBaseVertex * super ;
    ThisPrivate(SimpleDrawElementsInstancedBaseVertex * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
/****************************************************/
/****************************************************/
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer pointsBuffer;
	gl::NamedBuffer indexBuffer;
	QTimer timer;
	int baseIndex = 0;
	~ThisPrivate(){
		timer.stop();
		gl::deleteAny(program,vao,pointsBuffer,indexBuffer);
	}
    void initializeGL(){
#define POINT0 -0.5f,-0.5f,0,1,
#define POINT1 0.5f,-0.5f,0,1,
		const static gl::Float points[] = {
			std::cos(70.0_d2r),std::sin(70.0_d2r),0.8f,1,
			POINT0
			POINT1
			std::cos(50.0_d2r),std::sin(50.0_d2r),0.8f,1,
			POINT0
			POINT1
			std::cos(30.0_d2r),std::sin(30.0_d2r),0.8f,1,
			POINT0
			POINT1
		};
		gl::createBuffers(1,&pointsBuffer);
		gl::createVertexArrays(1, &vao);
		gl::bufferData(pointsBuffer,sizeof(points),points);
		vao.bindBuffer(0,pointsBuffer);
		constexpr static gl::UnsignedInteger index[] = {0,1,2};
		gl::createBuffers(1, &indexBuffer);
		gl::bufferData(indexBuffer,sizeof(index),index );
		vao.bindElementBuffer(indexBuffer);
		constexpr static char vs[] = u8R"(#version 450
layout(location=0) in vec4 iposition;
out vec4 color ;
void main(){

if( gl_InstanceID ){
gl_Position = iposition;
color = vec4(0.9,0.9,0,1);
}else{
gl_Position = vec4(-iposition.x,iposition.y,iposition.z,1);
color = vec4(0,0.9,0.9,1);
}
}
)";
		constexpr static char fs[] = u8R"(#version 450
out vec4 fcolor;
in vec4 color;
void main(){
fcolor=color;
}
)";
		program = gl::VFProgramLoadSources(vs,fs);
		{
			typedef void(QTimer::*TT)();
			timer.connect(&timer,TT(&QTimer::timeout),
				[this]() {
				++baseIndex;
				if (baseIndex > 2) { baseIndex = 0; }
				super->updateGL();
			}
				);
			timer.start(666);
		}
	}
    void paintGL(){
		gl::clearAll();
		program.use();
		program.bindVertexArray(vao);
		using namespace gl::DrawElementsInstancedBaseVertex;
		gl::drawElementsInstancedBaseVertex(
			Mode::TRIANGLES,
			3,
			Type::UNSIGNED_INT,
			0,
			2,
			baseIndex*3
			);
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawElementsInstancedBaseVertex::SimpleDrawElementsInstancedBaseVertex(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawElementsInstancedBaseVertex::~SimpleDrawElementsInstancedBaseVertex(){
    delete thisp;
}

void SimpleDrawElementsInstancedBaseVertex::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawElementsInstancedBaseVertex::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawElementsInstancedBaseVertex *);
std::unique_ptr<SimpleDrawElementsInstancedBaseVertex, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawElementsInstancedBaseVertex * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawElementsInstancedBaseVertex::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


