/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <QTimer>
#include "SimpleDrawElementsInstancedBaseVertexBaseInstance.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDrawElementsInstancedBaseVertexBaseInstance::ThisPrivate{
public:
    SimpleDrawElementsInstancedBaseVertexBaseInstance * super ;
    ThisPrivate(SimpleDrawElementsInstancedBaseVertexBaseInstance * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int baseIndex  = 0;
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer positionBuffer, colorBuffer, indexBuffer;
	QTimer timer;
    ~ThisPrivate(){
		timer.stop();
		gl::deleteAny(program, vao, 
			positionBuffer, colorBuffer, indexBuffer);
	}
    void initializeGL(){
		glDisable(GL_BLEND);
		gl::enableDepthTest();
		glEnable( GL_CULL_FACE );
		gl::depthFunction();

		constexpr static char vs[] = R"(#version 450
layout(location=0) in vec4 icolor;
layout(location=1) in vec4 iposition;

uniform mat4 offsetValue=mat4(
0.0,0.0,0,1,     /*r*/
-0.05,0.2,0.5,1, /*g*/
-0.1,0.4,-0.5,1, /*b*/
0.6,0.6,0,1
);

out vec4 color;
void main(){
color=icolor;
gl_Position = vec4(
iposition.xy+offsetValue[gl_InstanceID].xy , 
offsetValue[gl_InstanceID].z,
1);

}

)";
		constexpr static char fs[] = R"(#version 450
in vec4 color;
out vec4 fcolor;
void main(){
fcolor = color;
}

)";
		program = gl::VFProgramLoadSources(vs,fs);
		gl::createBuffers(1,&positionBuffer);
		gl::createBuffers(1,&colorBuffer);
		gl::createBuffers(1, &indexBuffer);
		constexpr static gl::UnsignedInteger index[] = {0,1,2};
		constexpr static gl::Float position[] = {
			0.9f,-0.7f, 0,1,
			-0.2f, 0.3f,0,1,
			-0.9f,-0.7f,0,1,
			
			0.9f,-0.6f, 0,1,
			0.2f,0.5f,  0,1,
			-0.9f,-0.5f,0,1,

			0.9f,-0.6f, 0,1,
			0.5f,0.4f,  0,1,
			-0.9f,-0.5f,0,1,
		};

		constexpr static gl::Float color[] = {
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,0.2f,0,1,
			0,1,0,1,
			0,0,1,1,
			1,0.6f,0,1,
			0,1,0,1,
			0,0,1,1,
		};
		gl::createVertexArrays(1,&vao);
		gl::bufferData(indexBuffer, sizeof(index), index);
		gl::bufferData(positionBuffer, sizeof(position), position);
		gl::bufferData(colorBuffer,sizeof(color),color);
		vao.bindBuffer(1,positionBuffer );
		vao.bindBuffer(0,colorBuffer);
		vao.bindDivisor(0, 1);
		vao.bindElementBuffer(indexBuffer);
		{
			typedef void(QTimer::*TT)();
			timer.connect(&timer,TT(&QTimer::timeout),
				[this]() {
				++baseIndex;
				if (baseIndex > 2) { baseIndex = 0; }
				super->updateGL();
			}
				);
		}
		timer.start(666);
	}
    void paintGL(){
		gl::clearAll();
		{
			program.use();
			program.bindVertexArray(vao);
			using namespace gl::DrawElementsInstancedBaseVertexBaseInstance; 
			Pack pack(
				Mode::TRIANGLES,
				3,Type::UNSIGNED_INT,nullptr,
				3, 3*baseIndex, 3*baseIndex);
			gl::draw(pack);
		}
    }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawElementsInstancedBaseVertexBaseInstance::SimpleDrawElementsInstancedBaseVertexBaseInstance(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawElementsInstancedBaseVertexBaseInstance::~SimpleDrawElementsInstancedBaseVertexBaseInstance(){
    delete thisp;
}

void SimpleDrawElementsInstancedBaseVertexBaseInstance::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawElementsInstancedBaseVertexBaseInstance::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawElementsInstancedBaseVertexBaseInstance *);
std::unique_ptr<SimpleDrawElementsInstancedBaseVertexBaseInstance, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawElementsInstancedBaseVertexBaseInstance * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawElementsInstancedBaseVertexBaseInstance::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


