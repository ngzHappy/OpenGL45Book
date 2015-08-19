/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleComputeShader2D.hpp"
#include <memory>
#include <cmath>

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif

#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif

class SimpleComputeShader2D::ThisPrivate{
public:
    SimpleComputeShader2D * super ;
    ThisPrivate(SimpleComputeShader2D * s):super(s){
}
/****************************************************/
/****************************************************/
    gl::Program program ;
    gl::NamedTexture imageTexture ;
	gl::TextureRenderRectangle render;
	bool hasEvaled = false;
    ~ThisPrivate(){
		gl::deleteAny(program,imageTexture);
	}
    void initializeGL(){

    #ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
    #endif

constexpr const static char cs[] = R"(#version 450
layout (
local_size_x = 1,
local_size_y = 1) in;
layout ( binding = 0,r32f ) uniform image2D image_;

void main(){
ivec2 pos_ = ivec2(gl_WorkGroupID.xy);
float value_ = imageLoad(image_, pos_).x;
imageStore(image_, pos_ ,vec4(1-value_,1,1,1) );
}

)";
program = gl::CProgramLoadSources(cs);

static bool dataInit = false;
enum {width=512,height=512};
static float data_temp[width*height];
if(false==dataInit){
	dataInit = true;
	float * data_ = data_temp;
	
	for (int i = 0; i < height;++i) {
		float value__ = 0;
		for (int j = 0; j < width;++j) {
			*data_ = std::abs( std::sin(value__) *0.85f+0.05f );
			value__ += 0.01f;
			constexpr const float pi2__ = 2 * 3.141592654f;
			if (value__ > pi2__) { value__ -= pi2__; }
			++data_;
		}
	}

}

imageTexture = gl::createTexture2D(width, height, data_temp);


 }
    void paintGL(){
		if(false== hasEvaled){
			hasEvaled = true;
			using namespace gl::DisPatchCompute;
			Pack pack(512,512);
			pack.useProgram(program);
			pack.bindImageTexture(0, imageTexture);
			gl::disPatch(pack);
		}
		
		render.render(imageTexture);

    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleComputeShader2D::SimpleComputeShader2D(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleComputeShader2D::~SimpleComputeShader2D(){
    delete thisp;
}

void SimpleComputeShader2D::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void SimpleComputeShader2D::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleComputeShader2D *);
std::unique_ptr<SimpleComputeShader2D, PaintStateDeleteFunction>
paintState(this, [](SimpleComputeShader2D * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleComputeShader2D::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


