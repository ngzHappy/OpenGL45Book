/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawElementsInstancedBaseInstance.hpp"
#include <memory>
#include <QTimer>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDrawElementsInstancedBaseInstance::ThisPrivate{
public:
    SimpleDrawElementsInstancedBaseInstance * super ;
    ThisPrivate(SimpleDrawElementsInstancedBaseInstance * s):super(s){
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
	gl::NamedBuffer positionBuffer;
	gl::NamedBuffer colorBuffer;
	gl::NamedBuffer indexBuffer;
	int baseIndex = 0;
	QTimer timer;
	~ThisPrivate() {
		timer.stop();
		gl::deleteAny(vao, program,
			positionBuffer, colorBuffer, indexBuffer);
	}
	void initializeGL() {
		gl::createVertexArrays(1, &vao);
		gl::createBuffers(1, &positionBuffer);
		gl::createBuffers(1, &colorBuffer);
		gl::createBuffers(1, &indexBuffer);
		vao.bindElementBuffer(indexBuffer);
		constexpr static gl::Float colors[] = {
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
		};
#define POS0 -0.5f, 0.5f,0,1,
#define POS1 -0.5f,-0.5f,0,1,
#define POS2  0.5f,-0.5f,0,1,
#define POS3  0.5f, 0.5f,0,1,
		constexpr static gl::Float positions[] = {
			POS0
			POS1
			POS2
			POS3
			POS1
			POS2
			POS3
			POS0
			POS2
			POS3
			POS0
			POS1
			POS3
			POS0
			POS1
			POS2
		};
		gl::bufferData(positionBuffer, sizeof(positions), positions);
		gl::bufferData(colorBuffer, sizeof(colors), colors);
		constexpr static gl::UnsignedInteger index[] = { 0 };
		gl::bufferData(indexBuffer, sizeof(index), index);
		vao.bindBuffer(0, positionBuffer);
		vao.bindBuffer(1, colorBuffer);
		vao.bindDivisor(0, 1);
		vao.bindDivisor(1, 1);
		constexpr static char vs[] = R"(#version 450
layout(location=0) in vec4 iposition;
layout(location=1) in vec4 icolor;
out vec4 color;
void main(){
gl_Position = iposition;
gl_PointSize = 36+15*gl_InstanceID;
color = icolor;
}
)";
		constexpr static char fs[] = R"(#version 450
in vec4 color;
out vec4 fcolor;
void main(){
fcolor = vec4( gl_PointCoord.xy  ,color.x, 1);
}
)";
		program = gl::VFProgramLoadSources(vs, fs);
		{
			typedef void(QTimer::*TT)();
			timer.connect(&timer,TT(&QTimer::timeout),
				[this]() {
				++baseIndex;
				if (baseIndex > 3) { baseIndex = 0; }
				super->updateGL();
			}
				);
			timer.start(666);
		}
	}
	void paintGL() {
		gl::clearAll();
		program.use();
		glEnable(GL_PROGRAM_POINT_SIZE);
		program.bindVertexArray(vao);
		if (baseIndex&1) {
			gl::pointCoordOrigin(
				gl::PointCoordOrigin::LOWER_LEFT
				);
		}
		else {
			gl::pointCoordOrigin(
				gl::PointCoordOrigin::UPPER_LEFT
				);
		}
		using namespace gl::DrawElementsInstancedBaseInstance;
		gl::drawElementsInstancedBaseInstance(
			Mode::POINTS,
			1,
			Type::UNSIGNED_INT,
			0,
			4,
			4*baseIndex
			);
		glDisable(GL_PROGRAM_POINT_SIZE);
	}
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawElementsInstancedBaseInstance::SimpleDrawElementsInstancedBaseInstance(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawElementsInstancedBaseInstance::~SimpleDrawElementsInstancedBaseInstance(){
    delete thisp;
}

void SimpleDrawElementsInstancedBaseInstance::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawElementsInstancedBaseInstance::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawElementsInstancedBaseInstance *);
std::unique_ptr<SimpleDrawElementsInstancedBaseInstance, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawElementsInstancedBaseInstance * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawElementsInstancedBaseInstance::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


