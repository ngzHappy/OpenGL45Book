﻿/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include "SimpleDepthTest.hpp"
#include <memory>
#include <iostream>
#include <glm/gtx/io.hpp>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDepthTest::ThisPrivate{
public:
    SimpleDepthTest * super ;
    ThisPrivate(SimpleDepthTest * s):super(s){
}

/////////////////////////////////////////////////////
	gl::Program                program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer            pointsBuffer;
	gl::NamedBuffer            colorBuffer;
	glm::mat4                  pMatrix;
	~ThisPrivate(){
		gl::deleteAny(program,pointsBuffer,vao, colorBuffer, colorBuffer);
	}

    void initializeGL(){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif

		gl::createBuffers(1, &pointsBuffer);
		gl::createBuffers(1, &colorBuffer);
		gl::createVertexArrays(1,&vao);

		constexpr gl::Float points[] = {
			-0.0f,+0.5f, -0.1f,1,
			-0.5f,-0.5f, -0.1f,1,
			+0.5f,-0.5f, -0.1f,1,
			+0.2f,+0.5f, -0.5f,1,
			-0.3f,-0.5f, -0.5f,1,
			+0.7f,-0.5f, -0.5f,1,
		};

		constexpr gl::Float colors[] = {
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,0,1,
			0,1,1,1,
			1,0,1,1,
		};

		gl::bufferData(pointsBuffer,sizeof(points),points);
		gl::bufferData(colorBuffer,sizeof(colors), colors);
		vao.bindBuffer(0, pointsBuffer);
		vao.bindBuffer(1, colorBuffer);

		constexpr char vs[] = R"(#version 450
layout(location=0) in vec4 ipos;
layout(location=1) in vec4 icol;
layout(location=2) uniform mat4 pMatrix;
out vec4 color;
void main(){
gl_Position = pMatrix*ipos;
color = icol;
}
)";
		constexpr char fs[] = R"(#version 450
in vec4 color;
out vec4 fcolor;
void main(){
fcolor = color;
}
)";
		program = gl::VFProgramLoadSources(vs,fs);
		pMatrix = glm::lookAt(
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
			); 
		pMatrix = 
			glm::ortho<float>(-1, 1, -1, 1, 0, 2)*pMatrix;
		
		std::cout << pMatrix << std::endl;
		program.setUniformMatrix4fv(2, 1, false,&(pMatrix[0][0]));
		gl::enableDepthTest();
	}
    void paintGL(){
		gl::clearAll();
		using namespace gl::DrawArrays;
		program.use();
		program.bindVertexArray(vao);
		gl::drawArrays( Mode::TRIANGLES,0,6 );
    }
/////////////////////////////////////////////////////
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDepthTest::SimpleDepthTest(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDepthTest::~SimpleDepthTest(){
    delete thisp;
}

void SimpleDepthTest::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void SimpleDepthTest::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
if(false==isOpenGLInited){return;}
typedef void(*PaintStateDeleteFunction)(SimpleDepthTest *);
std::unique_ptr<SimpleDepthTest, PaintStateDeleteFunction>
paintState(this, [](SimpleDepthTest * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDepthTest::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


