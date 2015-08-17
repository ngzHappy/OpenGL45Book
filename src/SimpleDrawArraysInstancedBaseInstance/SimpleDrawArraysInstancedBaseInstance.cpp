/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawArraysInstancedBaseInstance.hpp"
#include <OpenGLTool/QGLApplication.hpp>
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
class SimpleDrawArraysInstancedBaseInstance::ThisPrivate{
public:
    SimpleDrawArraysInstancedBaseInstance * super ;
    ThisPrivate(SimpleDrawArraysInstancedBaseInstance * s):super(s){
		timer = new QTimer;
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
	gl::NamedBuffer pointsBuffer;
	gl::NamedBuffer colorsBuffer;
	int baseIndex =0;
	QTimer * timer;
	
    ~ThisPrivate(){
		timer->stop();
		gl::deleteAny(program, vao, pointsBuffer, colorsBuffer);
		timer->deleteLater();
	}
    void initializeGL(){
		glEnable(GL_DEPTH_TEST);

		static constexpr char vertex_shader_source[] = R"(
#version 450
layout(location=0) in vec4 ipositon;
layout(location=1) in vec4 icolor;
uniform mat4 offsetValue = mat4(
 0.45, 0.45,0,1,
 0.45,-0.45,0,1,
-0.45,-0.45,0,1,
-0.45, 0.45,0,1
);
out vec4 color;
void main(void){
    gl_Position = vec4( ipositon.xyz/1.225 ,0) + offsetValue[gl_InstanceID] ;
	color = icolor ;
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

		constexpr static gl::Float points[] = {
			-0.5f, 0.5f,0,1,
			-0.5f,-0.5f,0,1,
			0.5f, 0.5f,0,1,
			0.5f,-0.5f,0,1,
		};
#define COLOR1 1,0,0,1,
#define COLOR2 0,0,1,1,
#define COLOR3 1,1,0,1,
#define COLOR4 0,1,0,1,
		constexpr static gl::Float colors[] = {
			COLOR1
			COLOR2
			COLOR3
			COLOR4
			COLOR2
			COLOR3
			COLOR4
			COLOR1
			COLOR3
			COLOR4
			COLOR1
			COLOR2
			COLOR4
			COLOR1
			COLOR2
			COLOR3
		};

		gl::createVertexArrays(1, &vao);

		gl::createBuffers(1, &pointsBuffer);
		gl::createBuffers(1, &colorsBuffer);

		gl::bufferData(pointsBuffer, sizeof(points), points);
		gl::bufferData(colorsBuffer, sizeof(colors), colors);

		vao.bindBuffer(0, pointsBuffer, 0);
		vao.bindBuffer(1, colorsBuffer, 0);
		vao.bindDivisor(1, 1);

		typedef void(QTimer::*TT)();
		timer->connect(timer, TT(&QTimer::timeout), [this]() {
			++baseIndex;
			if (baseIndex > 3) { baseIndex = 0; }
			super->updateGL();
		});
		timer->start(666);
	}
    void paintGL(){
		gl::clearAll();
		{
			auto locker = program.use(QGLApplication::atomicFunction());
			program.bindVertexArray(vao);
			using namespace gl::DrawArraysInstancedBaseInstance;
			gl::drawArraysInstancedBaseInstance(
				Mode::TRIANGLE_STRIP,
				0, 4, 4,baseIndex*4
				);
			(void)locker;
		}
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawArraysInstancedBaseInstance::SimpleDrawArraysInstancedBaseInstance(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawArraysInstancedBaseInstance::~SimpleDrawArraysInstancedBaseInstance(){
    delete thisp;
}

void SimpleDrawArraysInstancedBaseInstance::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawArraysInstancedBaseInstance::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawArraysInstancedBaseInstance *);
std::unique_ptr<SimpleDrawArraysInstancedBaseInstance, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawArraysInstancedBaseInstance * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawArraysInstancedBaseInstance::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


