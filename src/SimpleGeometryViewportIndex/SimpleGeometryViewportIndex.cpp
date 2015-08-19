/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <memory>
#include "SimpleGeometryViewportIndex.hpp"

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleGeometryViewportIndex::ThisPrivate{
public:
    SimpleGeometryViewportIndex * super ;
    ThisPrivate(SimpleGeometryViewportIndex * s):super(s){
}
/****************************************************/
/****************************************************/
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer pointsBuffer;
	~ThisPrivate() {
		gl::deleteAny(program);
		gl::deleteAny(vao);
		gl::deleteAny(pointsBuffer);
	}

	void initializeGL() {
		glClearDepth(1);
		glClearColor(0, 0, 0, 0);
#ifdef _DEBUG_OPENGL_QT_
		QGLDebugTool::setSimpleCallbackFunction();
		QGLDebugTool::test();
#endif
		{

			constexpr static const char vs[] = R"v(#version 450
layout(location=0) in vec4 iposition ;
out vec4 color_0_ ;
void main(){
gl_Position = iposition;
color_0_ = (iposition+1)/2;
}
)v";
			constexpr static const char gs[] = R"g(#version 450
in  vec4 color_0_[];
out vec4 color_1_  ;
layout(triangles) in;
layout(invocations = 4) in;
layout(triangle_strip) out;
layout(max_vertices=3) out;
void main(){
gl_Position = gl_in[0].gl_Position;
color_1_ = color_0_[0];
gl_ViewportIndex = gl_InvocationID;
EmitVertex() ;
gl_Position = gl_in[1].gl_Position;
color_1_ = color_0_[1];
gl_ViewportIndex = gl_InvocationID;
EmitVertex() ;
gl_Position = gl_in[2].gl_Position;
color_1_ = color_0_[2];
gl_ViewportIndex = gl_InvocationID;
EmitVertex() ;
EndPrimitive();
}

)g";
			constexpr static const char fs[] = R"f(#version 450
in vec4 color_1_;
out vec4 fcolor ;
void main(){
fcolor = color_1_;
}
)f";

			program = gl::VGFProgramLoadSources(vs, gs, fs);
		}

		gl::createBuffers(1, &pointsBuffer);
		gl::createVertexArrays(1, &vao);
		{
			constexpr const static gl::Float points[]{
				0.0f, 0.5f,0,1,
				-0.5f,-0.5f,0,1,
				0.5f,-0.5f,0,1,
			};
			gl::bufferData(pointsBuffer, sizeof(points), points);
		}
		vao.bindBuffer(0, pointsBuffer);
	}

	void paintGL() {
		gl::NamedFrameBufferObject root;
		root.clearColor(0.1f, 0.1f, 0.1f, 1);
		root.clearDepth(1);
		float width  = super->width();
		float height = super->height();
		width /= 2;
		height /= 2;
		{
			using namespace gl::DrawArrays;
			Pack pack(Mode::TRIANGLES, 0, 3);
			pack.useProgram(program);
			pack.bindFrameBuffer(root);
			pack.bindVertexArray(vao);
			glViewportIndexedf(0, width, height, width, height);
			glViewportIndexedf(1,     0, height, width, height);
			glViewportIndexedf(2, width,      0, width, height);
			glViewportIndexedf(3,     0,      0, width, height);
			gl::draw(pack);
		}
	}
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleGeometryViewportIndex::SimpleGeometryViewportIndex(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleGeometryViewportIndex::~SimpleGeometryViewportIndex(){
    delete thisp;
}

void SimpleGeometryViewportIndex::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void SimpleGeometryViewportIndex::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleGeometryViewportIndex *);
std::unique_ptr<SimpleGeometryViewportIndex, PaintStateDeleteFunction>
paintState(this, [](SimpleGeometryViewportIndex * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleGeometryViewportIndex::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


