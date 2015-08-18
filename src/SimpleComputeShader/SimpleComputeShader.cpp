/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleComputeShader.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleComputeShader::ThisPrivate{
public:
    SimpleComputeShader * super ;
    ThisPrivate(SimpleComputeShader * s):super(s){
}
/****************************************************/
/****************************************************/
	gl::Program program;
	gl::NamedBuffer dataBuffer;
    ~ThisPrivate(){
		gl::deleteAny(program,dataBuffer);
	}
    void initializeGL(){

    #ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
    #endif
constexpr const static char cs[] = R"(#version 450
layout (
local_size_x = 3, 
local_size_y = 1) in;
layout (binding = 0, std430) coherent buffer SOME_NAME{
float data[3];
};

void main(){
data[gl_LocalInvocationIndex ] =(gl_LocalInvocationIndex +1)/4.0 ;
}
)";
program = gl::CProgramLoadSources(cs);
gl::createBuffers(1,&dataBuffer);
gl::bufferData(
	dataBuffer, 
	sizeof(float) * 3, 0,
	gl::BufferDataUsage::DYNAMIC_DRAW);

 }
    void paintGL(){
		float clearColor[]{0,0,0,1};
		gl::NamedFrameBufferObject root;
		{
			using namespace gl::DisPatchCompute;
			Pack pack;
			pack.useProgram(program);
			pack.bindShaderStorageBuffer(0, dataBuffer);
			gl::disPatch(pack);
		}
		 
		auto * data_ = dataBuffer.map<float>();
		clearColor[0] = data_[0];
		clearColor[1] = data_[1];
		clearColor[2] = data_[2];
		dataBuffer.unmap();

		root.clearColor(clearColor);

    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleComputeShader::SimpleComputeShader(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleComputeShader::~SimpleComputeShader(){
    delete thisp;
}

void SimpleComputeShader::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void SimpleComputeShader::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleComputeShader *);
std::unique_ptr<SimpleComputeShader, PaintStateDeleteFunction>
paintState(this, [](SimpleComputeShader * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleComputeShader::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


