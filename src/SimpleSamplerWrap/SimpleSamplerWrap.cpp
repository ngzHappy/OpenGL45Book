/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <memory>
#include <QTimer>
#include <QDebug>
#include "SimpleSamplerWrap.hpp"

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif

#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif

namespace  {
namespace  SamplerTest{


class TextureRenderRectangle {
    class Data{
    public:
        gl::Program program;
        gl::NamedVertexArrayObject vao;
        ~Data(){
            gl::deleteVertexArrays(1, &vao);
            gl::deleteProgram( program);
        }
    };
    std::shared_ptr<Data> data;
    void init(){
        data = std::shared_ptr<Data>(new Data);
        constexpr static char vs[] = R"v(#version 450
uniform mat4 points = mat4(
-1,1,0,1,
-1,-1,0,1,
1,1,0,1,
1,-1,0,1
);

smooth out vec2 tuv;
void main(){
gl_Position = points[gl_VertexID];
tuv = (gl_Position.xy+0.5)  /*[-0.5,1.5]*/ ;
}
)v" ;
        constexpr static char fs[] = R"f(#version 450
smooth in vec2 tuv;
out vec4 color ;
layout(binding=0) uniform sampler2D   stex;
void main(){
color = texture( stex, tuv  );
}
)f" ;
        data->program = gl::VFProgramLoadSources(vs,fs);
        gl::createVertexArrays(1, &(data->vao));
    }
public:
    TextureRenderRectangle(){}
    void render( 
		gl::NamedTexture texture,
		gl::NamedSamplerObject sampler
		){
        if (false == data) { init(); }
        data->program.use();
        data->program.bindVertexArray(data->vao);
        data->program.bindTexture( 0,texture );
		data->program.bindSampler( 0,sampler);
        using namespace gl::DrawArrays;
        Pack pack(Mode::TRIANGLE_STRIP,0,4);
        gl::draw(pack);
    }
};

}//namespace  SamplerTest
}//namespace

class SimpleSamplerWrap::ThisPrivate{
public:
    SimpleSamplerWrap * super ;
    ThisPrivate(SimpleSamplerWrap * s):super(s){
}
/****************************************************/
/****************************************************/
	SamplerTest::TextureRenderRectangle render;
	gl::NamedTexture texture;
	gl::NamedSamplerObject sampler0 ;
	gl::NamedSamplerObject sampler1 ;
	gl::NamedSamplerObject sampler2 ;
	QTimer timer;
	int samplerIndex = 0;
    ~ThisPrivate(){
		timer.stop();
		gl::deleteAny(texture);
		gl::deleteAny(sampler0, sampler2, sampler1);
	}
    void initializeGL(){
glClearDepth(1);
glClearColor(0,0,0,0);
#ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
#endif

gl::createSamplers(1, &sampler2);
gl::createSamplers(1, &sampler0);
gl::createSamplers(1, &sampler1);

{
    texture = gl::createTexture2D(":/image/testImage.jpg", GL_TEXTURE_2D );
}

{
	typedef gl::NamedSamplerObject::WrapType T; 
	sampler0.setWrapS(T::CLAMP_TO_EDGE);
	sampler0.setWrapT(T::CLAMP_TO_EDGE);
	sampler0.setWrapR(T::CLAMP_TO_EDGE);
	sampler0.setBorderColor(0.1f, 0.2f, 0.3f, 1);
}

{
	typedef gl::NamedSamplerObject::WrapType T;
	sampler1.setWrapS(T::REPEAT);
	sampler1.setWrapT(T::REPEAT);
	sampler1.setWrapR(T::REPEAT);
	sampler1.setBorderColor(0.2f, 0.3f, 0.1f, 1);
}

{
	typedef gl::NamedSamplerObject::WrapType T;
	sampler2.setWrapS(T::CLAMP_TO_BORDER);
	sampler2.setWrapT(T::CLAMP_TO_BORDER);
	sampler2.setWrapR(T::CLAMP_TO_BORDER);
	sampler2.setBorderColor(0.3f, 0.1f, 0.1f, 1);
}

{
	typedef void(QTimer::*TT)();
	timer.connect(&timer,TT(&QTimer::timeout),
		[this]() {
		++samplerIndex;
		if (samplerIndex > 2) { samplerIndex = 0; }
		super->updateGL();
	 
	}
		);
}
timer.start(666);

 }
    void paintGL(){
		gl::NamedFrameBufferObject root;
		using namespace gl::DrawArrays;
		Pack::bindFrameBuffer(root);
		root.clearColor(0.1f,0.1f,0.1f,1);
		gl::NamedSamplerObject sampler;
		switch (samplerIndex)
		{
		case 0:sampler = sampler0; break;
		case 1:sampler = sampler1; break;
		case 2:sampler = sampler2; break;
		default:break;
		}
		render.render(texture, sampler);
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleSamplerWrap::SimpleSamplerWrap(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleSamplerWrap::~SimpleSamplerWrap(){
    delete thisp;
}

void SimpleSamplerWrap::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void SimpleSamplerWrap::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleSamplerWrap *);
std::unique_ptr<SimpleSamplerWrap, PaintStateDeleteFunction>
paintState(this, [](SimpleSamplerWrap * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleSamplerWrap::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


