/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleMultiSampleFBO.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleMultiSampleFBO::ThisPrivate{
public:
    SimpleMultiSampleFBO * super ;
    ThisPrivate(SimpleMultiSampleFBO * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
/**************************************/
	gl::DefaultMultiSampleFrameBufferObject dFBO;
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::MultiSampleTextureRender renderRectangle;
	~ThisPrivate() {
		gl::deleteAny(program, vao);
	}
	void initializeGL() {
		super->setMinimumWidth(512);
		super->setMinimumHeight(512);
		gl::createVertexArrays(1, &vao);
		dFBO = gl::createDefaultFrameBuffer(512, 512,8);
		constexpr static char vs[] = R"(#version 450
uniform mat4 points = mat4(
0,0.5,0,1,
-0.5,-0.5,0,1,
0.5,-0.5f,0,1,
0,0,0,1);
out vec4 color ;
void main(){
gl_Position = points[ gl_VertexID ];
color = gl_Position/2+0.5;
}
)";
		constexpr static char fs[] = R"(#version 450
in vec4 color ;
out vec4 fcolor ;
void main(){
fcolor = color;
}
)";
		program = gl::VFProgramLoadSources(vs, fs);
	}
	void paintGL() {


		program.use();
		program.bindFrameBuffer(dFBO.frameBuffer() );
		program.bindVertexArray(vao);
		glViewport(0, 0, 512, 512);
		glClearColor(0.5f, 0.1f, 0.1f, 1);
		gl::clearAll();
		gl::drawArrays(gl::DrawArraysMode::TRIANGLES, 0, 3);
		program.bindFrameBuffer();

		glViewport(0, 0, super->width(), super->height());
		glClearColor(0.1f, 0.1f, 0.5f, 1);
		gl::clearAll();
		glViewport(
			(super->width() - 512) / 2,
			(super->height() - 512) / 2,
			512, 512);
		renderRectangle.render(dFBO.renderBuffer(),8);
	}
/**************************************/
    void resizeGL(int  ,int   ){
       
    }
};

SimpleMultiSampleFBO::SimpleMultiSampleFBO(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(600,600);
    this->setMinimumHeight(512);
    this->setMinimumWidth(512);
}


SimpleMultiSampleFBO::~SimpleMultiSampleFBO(){
    delete thisp;
}

void SimpleMultiSampleFBO::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleMultiSampleFBO::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleMultiSampleFBO *);
std::unique_ptr<SimpleMultiSampleFBO, PaintStateDeleteFunction>
paintState(this, [](SimpleMultiSampleFBO * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleMultiSampleFBO::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


