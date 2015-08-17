/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <OpenGLTool/QGLApplication.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include "NormalSphere.hpp"
#include <memory>
#include <OpenGLTool/ModelLoader.hpp>
#include <OpenGLTool/ModelLoaderCallbacks.hpp>
#include <QDebug>
#include <algorithm>
#include <utility>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class NormalSphere::ThisPrivate{
public:
    NormalSphere * super ;
    ThisPrivate(NormalSphere * s):super(s){
}
/****************************************************/
/****************************************************/
	gl::NamedVertexArrayObject vao ;
	gl::NamedBuffer  pointsNormalBuffer ; 
	gl::NamedBuffer  indexBuffer ;
	gl::Program      program;
	glm::mat4        modelScale;
	gl::UnsignedInteger indexCount;
    ~ThisPrivate(){
		gl::deleteAny(program, indexBuffer, pointsNormalBuffer,vao);
	}
    void initializeGL(){
{
	constexpr static char vs[] = R"(#version 450
layout(location=0) in vec4 iposition;
layout(location=1) in vec4 inormal  ;
layout(location=1) uniform mat4 MVP ;
layout(location=2) uniform vec4 light_pos = vec4(1,1,-1,1);
out vec4 color ;
void main(){
gl_Position = MVP * iposition;
vec3 light = light_pos.xyz - gl_Position.xyz ;
light = normalize( light );
float v = smoothstep(0,1, dot(light , 
normalize( vec3( inormal.x,inormal.y,-inormal.z )) ));
v*=0.85;
v+=0.05;
color = vec4(v,v,v,1) ;
}
)";
	constexpr static char fs[] = R"(#version 450
out vec4 fcolor ;
in vec4 color ;
void main(){
fcolor = color ;
}
)";
	program = gl::VFProgramLoadSources(vs,fs);
}
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
        glClearDepth(1);
        glClearColor(0,0,0,0);
#ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
#endif
gl::createBuffers(1, &pointsNormalBuffer);
gl::createBuffers(1,&indexBuffer);

{
	gl::VertexNormalElementCallBack callBack ;

	callBack.loadFile(
        ":/model.zip"
		);

	gl::bufferData(indexBuffer, 
callBack.triangles.size()*sizeof(callBack.triangles[0]),
&callBack.triangles[0]
);
	
	gl::bufferData(pointsNormalBuffer,
callBack.pointNormal.size()*sizeof(callBack.pointNormal[0]),
&callBack.pointNormal[0]);

	const double scale__ = (std::max)({ 
		double(callBack.xMax) - callBack.xMin ,
		double(callBack.yMax) - callBack.yMin,
		double(callBack.zMax) - callBack.zMin
	});

	modelScale = glm::scale(glm::vec3(
		float( 1.50 / scale__),
		float( 1.50 / scale__),
		float(-1.50 / scale__)
		));
	indexCount = 3 * callBack.triangles.size() ;
}

gl::createVertexArrays(1,&vao);
vao.bindBuffer(0, pointsNormalBuffer, 0,
	sizeof(gl::Float) * 6, 0,
	gl::NamedVertexArrayObject::Size::Three);
vao.bindBuffer(1, pointsNormalBuffer, 0,
	sizeof(gl::Float) * 6, sizeof(gl::Float) * 3,
	gl::NamedVertexArrayObject::Size::Three);
vao.bindElementBuffer(indexBuffer);

 }
    void paintGL(){
		constexpr static float clearColor[] = \
			{0.5f,0.3f,0.3f,1};
		gl::NamedFrameBufferObject root;
		root.clearColor(clearColor);
		root.clearDepth(1);
		program.use();
		program.bindFrameBuffer(root);
		program.bindVertexArray(vao);
		program.setUniformMatrix4fv(
			1, 1, false, &(modelScale[0][0]));
		using namespace gl::DrawElements;
		Pack pack(
			Mode::TRIANGLES,
			indexCount,
			Type::UNSIGNED_INT,
			nullptr);
		gl::draw(pack);
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

NormalSphere::NormalSphere(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


NormalSphere::~NormalSphere(){
    delete thisp;
}

void NormalSphere::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void NormalSphere::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(NormalSphere *);
std::unique_ptr<NormalSphere, PaintStateDeleteFunction>
paintState(this, [](NormalSphere * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void NormalSphere::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


