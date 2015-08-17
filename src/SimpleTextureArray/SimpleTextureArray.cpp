/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleTextureArray.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleTextureArray::ThisPrivate{
public:
    SimpleTextureArray * super ;
    ThisPrivate(SimpleTextureArray * s):super(s){
        glClearDepth(1);
        glClearColor(0.2f,0.2f,0.3f,1);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
/**********************************************/
/**********************************************/
	gl::NamedVertexArrayObject vao;
	gl::Program program;
	gl::NamedTexture texture;
	gl::NamedBuffer offsetValue;
	~ThisPrivate(){
		gl::deleteAny(program,vao,texture, offsetValue);
	}
    void initializeGL(){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		texture = 
			gl::createTexture2DArray( ":/TextureArray/textureArray.zip" );
		constexpr char vs[] = R"(#version 450
uniform mat4 points=mat4(
0,0.25,0,1,       /*0,1*/
0,0,0,1,   /*0,0*/
0.25,0.25,0,1,    /*1,1*/
0.25,0,0,1 /*1,0*/

);

layout(location =0) in vec4 offsetValue;
smooth out vec2 tuv;
flat out int tID;
void main(){
gl_Position = points[ gl_VertexID ];
tuv.x = gl_Position.x*4 ;
tuv.y = gl_Position.y*4 ;
tID = gl_InstanceID;
gl_Position.xy += offsetValue.xy   ;
}
)";
		constexpr char fs[] = R"(#version 450
smooth in vec2 tuv;
flat in int tID;
layout(binding=0) uniform sampler2DArray texture_array_  ;
out vec4 color;
void main(){
color = texture( texture_array_ , vec3(tuv,tID) );
}
)";
		program = gl::VFProgramLoadSources(vs,fs);
		gl::createVertexArrays(1,&vao);
		gl::createBuffers(1,&offsetValue);
		constexpr static gl::Float offsets[] = {
			-1.0f,-1.0f,0.0f,1.0f,
			-1.0f,-0.75f,0.0f,1.0f,
			-1.0f,-0.5f,0.0f,1.0f,
			-1.0f,-0.25f,0.0f,1.0f,
			-1.0f,0.0f,0.0f,1.0f,
			-1.0f,0.25f,0.0f,1.0f,
			-1.0f,0.5f,0.0f,1.0f,
			-1.0f,0.75f,0.0f,1.0f,
			-0.75f,-1.0f,0.0f,1.0f,
			-0.75f,-0.75f,0.0f,1.0f,
			-0.75f,-0.5f,0.0f,1.0f,
			-0.75f,-0.25f,0.0f,1.0f,
			-0.75f,0.0f,0.0f,1.0f,
			-0.75f,0.25f,0.0f,1.0f,
			-0.75f,0.5f,0.0f,1.0f,
			-0.75f,0.75f,0.0f,1.0f,
			-0.5f,-1.0f,0.0f,1.0f,
			-0.5f,-0.75f,0.0f,1.0f,
			-0.5f,-0.5f,0.0f,1.0f,
			-0.5f,-0.25f,0.0f,1.0f,
			-0.5f,0.0f,0.0f,1.0f,
			-0.5f,0.25f,0.0f,1.0f,
			-0.5f,0.5f,0.0f,1.0f,
			-0.5f,0.75f,0.0f,1.0f,
			-0.25f,-1.0f,0.0f,1.0f,
			-0.25f,-0.75f,0.0f,1.0f,
			-0.25f,-0.5f,0.0f,1.0f,
			-0.25f,-0.25f,0.0f,1.0f,
			-0.25f,0.0f,0.0f,1.0f,
			-0.25f,0.25f,0.0f,1.0f,
			-0.25f,0.5f,0.0f,1.0f,
			-0.25f,0.75f,0.0f,1.0f,
			0.0f,-1.0f,0.0f,1.0f,
			0.0f,-0.75f,0.0f,1.0f,
			0.0f,-0.5f,0.0f,1.0f,
			0.0f,-0.25f,0.0f,1.0f,
			0.0f,0.0f,0.0f,1.0f,
			0.0f,0.25f,0.0f,1.0f,
			0.0f,0.5f,0.0f,1.0f,
			0.0f,0.75f,0.0f,1.0f,
			0.25f,-1.0f,0.0f,1.0f,
			0.25f,-0.75f,0.0f,1.0f,
			0.25f,-0.5f,0.0f,1.0f,
			0.25f,-0.25f,0.0f,1.0f,
			0.25f,0.0f,0.0f,1.0f,
			0.25f,0.25f,0.0f,1.0f,
			0.25f,0.5f,0.0f,1.0f,
			0.25f,0.75f,0.0f,1.0f,
			0.5f,-1.0f,0.0f,1.0f,
			0.5f,-0.75f,0.0f,1.0f,
			0.5f,-0.5f,0.0f,1.0f,
			0.5f,-0.25f,0.0f,1.0f,
			0.5f,0.0f,0.0f,1.0f,
			0.5f,0.25f,0.0f,1.0f,
			0.5f,0.5f,0.0f,1.0f,
			0.5f,0.75f,0.0f,1.0f,
			0.75f,-1.0f,0.0f,1.0f,
			0.75f,-0.75f,0.0f,1.0f,
			0.75f,-0.5f,0.0f,1.0f,
			0.75f,-0.25f,0.0f,1.0f,
			0.75f,0.0f,0.0f,1.0f,
			0.75f,0.25f,0.0f,1.0f,
			0.75f,0.5f,0.0f,1.0f,
			0.75f,0.75f,0.0f,1.0f,
		};
		gl::bufferData(offsetValue,sizeof(offsets),offsets);
		vao.bindBuffer(0,offsetValue);
		vao.bindDivisor(0,1);
	}
    void paintGL(){
		gl::clearAll();
		program.use();
		program.bindVertexArray(vao);
		program.bindTexture(texture, 0, GL_TEXTURE_2D_ARRAY);
		{
			using namespace gl::DrawArraysInstanced;
			Pack pack(Mode::TRIANGLE_STRIP, 0, 4, 64);
			gl::draw(pack);
		}
    }
/**********************************************/
/**********************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleTextureArray::SimpleTextureArray(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleTextureArray::~SimpleTextureArray(){
    delete thisp;
}

void SimpleTextureArray::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleTextureArray::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleTextureArray *);
std::unique_ptr<SimpleTextureArray, PaintStateDeleteFunction>
paintState(this, [](SimpleTextureArray * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleTextureArray::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


