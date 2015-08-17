/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <QTimer>
#include "SimpleDrawRangeElements.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDrawRangeElements::ThisPrivate{
public:
    SimpleDrawRangeElements * super ;
    ThisPrivate(SimpleDrawRangeElements * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
/******************************************************/
/******************************************************/
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer pointsBuffer, indexBuffer, colorsBuffer;
	QTimer timer;
	bool drawModel=false;
	~ThisPrivate(){
		timer.stop();
		gl::deleteAny(vao,program,
			pointsBuffer,indexBuffer,colorsBuffer);
	}
    void initializeGL(){
		constexpr static char vs[] = R"(#version 450
layout(location=0) in vec4  color;
layout(location=1) in vec4  position;
flat out vec4 fcolor ;
void main(){
gl_Position = position;
fcolor = color;
} 
)";
		constexpr static char fs[] = R"(#version 450
flat  in vec4 fcolor;
out vec4 color;
void main(){
color = fcolor;
}
			)";
		program = gl::VFProgramLoadSources(vs,fs);
		gl::createBuffers(1,&pointsBuffer);
		gl::createBuffers(1,&colorsBuffer);
		gl::createBuffers(1,&indexBuffer);
		constexpr static gl::Float points[]{
			0,0.5f,0,1,
			-0.5f,-0.5f,0,1,
			0.5f,-0.5f,0,1,
			0.5f,0.5f,0,1,
			-0.5f,-0.5f,0,1,
			0.5f,-0.5f,0,1,
			0.8f,0.5f,0,1,
			-0.5f,-0.5f,0,1,
			0.5f,-0.5f,0,1,
		};
		gl::bufferData(pointsBuffer, sizeof(points), points);
		constexpr static gl::Float colors[]{
			1,0,0,1,
			0,1,0,1,
			0,0,1,0,
			1,0,0,1,
			0,1,0,1,
			0,0,1,0,
			1,0,0,1,
			0,1,0,1,
			0,0,1,0,
		};
		gl::bufferData(colorsBuffer,sizeof(colors),colors);
		constexpr static gl::UnsignedInteger index[]{0,1,2,3,4,5,6,7,8};
		gl::bufferData(indexBuffer, sizeof(index), index);
		gl::createVertexArrays(1,&vao);
		vao.bindElementBuffer(indexBuffer);
		vao.bindBuffer(0,colorsBuffer);
		vao.bindBuffer(1, pointsBuffer);
		{
			typedef void(QTimer::*TT)();
			timer.connect(&timer, TT(&QTimer::timeout), [this]() {
				drawModel = !drawModel;
				super->updateGL();
			});
		}
		timer.start(666);
	}
    void paintGL(){
		gl::clearAll();
		program.use();
		program.bindVertexArray(vao);
		if (drawModel) {
			glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
		}
		else {
			glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
		}
		{
			using namespace gl::DrawRangeElements;
			Pack pack(Mode::TRIANGLES, 0, 5, 6, Type::UNSIGNED_INT, 0);
			gl::draw(pack);
		}
    }
/******************************************************/
/******************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawRangeElements::SimpleDrawRangeElements(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawRangeElements::~SimpleDrawRangeElements(){
    delete thisp;
}

void SimpleDrawRangeElements::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawRangeElements::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawRangeElements *);
std::unique_ptr<SimpleDrawRangeElements, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawRangeElements * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawRangeElements::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


