/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <OpenGLTool/QGLApplication.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include <memory>
#include <OpenGLTool/ModelLoader.hpp>
#include <OpenGLTool/ModelLoaderCallbacks.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include <QDebug>
#include "Spider.hpp"
#include <vector>
#include <map>
#include <QTimer>

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif

namespace  {

template<typename T>
class UniqueGLObject :public std::unique_ptr<T,void(*)(T*)> {
public:
    UniqueGLObject( T * d  ):std::unique_ptr<T,void(*)(T*)>(
      d,[](T * _d){
		if (0 == _d) { return; }
		gl::deleteAny(*_d);
		delete _d;
	}
		){}
	UniqueGLObject() :std::unique_ptr<T, void(*)(T*)>(
		new T,
		[](T * _d) {
		if (0 == _d) { return; }
		gl::deleteAny(*_d);
		delete _d;}
		){}
};

}

class Spider::ThisPrivate{
public:
    Spider * super ;
    ThisPrivate(Spider * s):super(s){
}
/****************************************************/
/****************************************************/
    gl::Program program ;
	std::map<int, UniqueGLObject<gl::NamedVertexArrayObject>   > vao;
	std::map<int, UniqueGLObject<gl::NamedTexture>             > texture;
	std::map<int, UniqueGLObject<gl::NamedBuffer>              > PNTBuffer;
	std::map<int, UniqueGLObject<gl::NamedBuffer>              > IPNTBuffer;
	std::map<int, int>                                           IPNTSize;
	QTimer timer;
	glm::mat4 rotateMatrix;
	float rotateValue;
    ~ThisPrivate(){
		timer.stop();
        gl::deleteAny(program);
    }
    void initializeGL(){
		rotateValue = 0;
glClearDepth(1);
glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
    #endif
{
	 
	gl::VertexTextureNormalElementCallBack callBack;
    callBack.loadFile(R"(:/spider.zip)");
	for (const auto & i:callBack.triangles) {

		UniqueGLObject<gl::NamedVertexArrayObject> _vao ;
		UniqueGLObject<gl::NamedTexture> _texture;
		UniqueGLObject<gl::NamedBuffer> _PNTBuffer;
		UniqueGLObject<gl::NamedBuffer> _IPNTBuffer;
		gl::createBuffers(1, _PNTBuffer.get());
		gl::createBuffers(1, _IPNTBuffer.get());
		gl::createVertexArrays(1,_vao.get());
		*_texture = gl::createTexture2D(
			callBack.texturesImage[i.first]
			);
	 
		const auto & pnt = callBack.pointNormalTexture[i.first];
		const auto & ipnt = callBack.triangles[i.first];
		gl::bufferData(*_PNTBuffer,
			pnt.size()*sizeof(pnt[0]),
			&(pnt[0])
			);
		gl::bufferData(*_IPNTBuffer,
			ipnt.size()*sizeof(ipnt[0]),
			&(ipnt[0])
			);
		_vao->bindElementBuffer(*_IPNTBuffer);
		_vao->bindBuffer(0, *_PNTBuffer,
			0, sizeof(pnt[0]), 
			0,gl::NamedVertexArrayObject::Size::Three
			);
		_vao->bindBuffer(1, *_PNTBuffer, 
			0, sizeof(pnt[0]), 
			sizeof(gl::Float)*3,gl::NamedVertexArrayObject::Size::Three
			);
		_vao->bindBuffer(2, *_PNTBuffer,
			0, sizeof(pnt[0]), 
			sizeof(gl::Float)*6,gl::NamedVertexArrayObject::Size::Two
			);

		vao[i.first] = std::move(_vao);
		texture[i.first] = std::move(_texture);
		PNTBuffer[i.first] = std::move(_PNTBuffer);
		IPNTBuffer[i.first] = std::move(_IPNTBuffer);
		IPNTSize[i.first] = ipnt.size() * 3;

	}

	{
		const static QString vs = R"(#version 450
layout(location=0) in vec3 ip_;
layout(location=1) in vec3 in_;
layout(location=2) in vec2 it_;
layout(location=0) uniform mat4 rotateMatrix ;
smooth out vec2 tuv ;
void main(){
tuv = vec2( it_.x , 1-it_.y ) ;
gl_Position =  vec4(ip_,1) *vec4(0.01,0.01,-0.01,1);
gl_Position = rotateMatrix * gl_Position ;
} 
)";
		const static QString fs = R"(#version 450
smooth in vec2 tuv ;
out vec4 fcolor ;
layout(binding=0) uniform sampler2D  texture_1_; 
void main(){
fcolor = texture(texture_1_,tuv);
}
)";
		program = gl::VFProgramLoadSources(vs,fs);
	}

}
{
	typedef void(QTimer::* TT)();
	timer.connect(&timer,TT(&QTimer::timeout),
		[this]() {
		if (rotateValue>3.141592654f*2) {
			rotateValue -= 3.141592654f * 2;
		}
		rotateMatrix = glm::rotate(rotateValue,glm::vec3(0,1,0) );
		super->updateGL();
		rotateValue += 0.211f;
	}
		);
}
timer.start(666);
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
 }
    void paintGL(){
		constexpr float clearColor[] = {0.3f,0.3f,0.3f,1};
		gl::NamedFrameBufferObject root;
		program.use();
		program.bindFrameBuffer(root);
		root.clearColor(clearColor);
		root.clearDepth(1);
		program.setUniformMatrix4fv(0,1,false,&(rotateMatrix[0][0]));
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		for ( const auto & i:IPNTSize ) {
			program.bindVertexArray(*(vao[i.first]));
			program.bindTexture(*(texture[i.first]),0, GL_TEXTURE_2D);
		 
			using namespace gl::DrawElements;
			Pack pack( 
				Mode::TRIANGLES,
				i.second,
				Type::UNSIGNED_INT,
				nullptr );
			gl::draw(pack);
		}
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

Spider::Spider(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


Spider::~Spider(){
    delete thisp;
}

void Spider::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void Spider::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(Spider *);
std::unique_ptr<Spider, PaintStateDeleteFunction>
paintState(this, [](Spider * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void Spider::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


