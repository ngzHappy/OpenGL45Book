/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawRangeElementsBaseVertex.hpp"
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
class SimpleDrawRangeElementsBaseVertex::ThisPrivate{
public:
    SimpleDrawRangeElementsBaseVertex * super ;
    ThisPrivate(SimpleDrawRangeElementsBaseVertex * s):super(s){
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
	int baseIndex = false;
	~ThisPrivate() {
		timer.stop();
		gl::deleteAny(vao, program,
			pointsBuffer, indexBuffer, colorsBuffer);
	}
	void initializeGL() {
		constexpr static char vs[] = R"(#version 450
layout(location=0) in vec4  color;
layout(location=1) in vec4  position;
smooth out vec4 fcolor ;
void main(){
gl_Position = position;
fcolor = color;
} 
)";
		constexpr static char fs[] = R"(#version 450
smooth  in vec4 fcolor;
out vec4 color;
void main(){
color = fcolor;
}
			)";
		program = gl::VFProgramLoadSources(vs, fs);
		gl::createBuffers(1, &pointsBuffer);
		gl::createBuffers(1, &colorsBuffer);
		gl::createBuffers(1, &indexBuffer);
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
		gl::bufferData(colorsBuffer, sizeof(colors), colors);
		constexpr static gl::UnsignedInteger index[]{ 0,1,2,3,4,5,6,7,8 };
		gl::bufferData(indexBuffer, sizeof(index), index);
		gl::createVertexArrays(1, &vao);
		vao.bindElementBuffer(indexBuffer);
		vao.bindBuffer(0, colorsBuffer);
		vao.bindBuffer(1, pointsBuffer);
		{
			typedef void(QTimer::*TT)();
			timer.connect(&timer, TT(&QTimer::timeout), [this]() {
				++baseIndex;
				if (baseIndex > 1) { baseIndex = 0; }
				super->updateGL();
			});
		}
		timer.start(666);
	}
	void paintGL() {
		gl::clearAll();
		program.use();
		program.bindVertexArray(vao);
	 
		{
			using namespace gl::DrawRangeElementsBaseVertex;
			Pack pack(Mode::TRIANGLES, 0, 5, 
				3, Type::UNSIGNED_INT, nullptr,3*baseIndex);
			gl::draw(pack);
		}
	}
/******************************************************/
/******************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawRangeElementsBaseVertex::SimpleDrawRangeElementsBaseVertex(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawRangeElementsBaseVertex::~SimpleDrawRangeElementsBaseVertex(){
    delete thisp;
}

void SimpleDrawRangeElementsBaseVertex::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawRangeElementsBaseVertex::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawRangeElementsBaseVertex *);
std::unique_ptr<SimpleDrawRangeElementsBaseVertex, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawRangeElementsBaseVertex * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawRangeElementsBaseVertex::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


