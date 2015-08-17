/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SingleTriangle.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SingleTriangle::ThisPrivate{
public:
    SingleTriangle * super ;
    ThisPrivate(SingleTriangle * s):super(s){
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
 -0.5000,   -0.5000,         0,    1.0000,//first column
  0.5000,   -0.5000,         0,    1.0000,//second column
       0,    0.5000,         0,    1.0000,//third column
  1.0000,    1.0000,    1.0000,    1.0000 //fourth column
);
void main(void){
	gl_Position = vertices[gl_VertexID];
}

)";
		static constexpr char fragment_shader_source[] = R"(
#version 450
out vec4 color;
void main(void){
	color = vec4(0.0, 0.8, 1.0, 1.0);
}
)";
program = gl::VFProgramLoadSources(
            vertex_shader_source,fragment_shader_source
            );
gl::createVertexArrays(1,&vao);
	}
    void paintGL(){
        gl::clearAll();
        gl::useProgram(program);
        gl::bindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SingleTriangle::SingleTriangle(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SingleTriangle::~SingleTriangle(){
    delete thisp;
}

void SingleTriangle::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SingleTriangle::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SingleTriangle *);
std::unique_ptr<SingleTriangle, PaintStateDeleteFunction>
paintState(this, [](SingleTriangle * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SingleTriangle::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


