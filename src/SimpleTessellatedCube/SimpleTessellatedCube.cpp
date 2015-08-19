/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleTessellatedCube.hpp"
#include <memory>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleTessellatedCube::ThisPrivate{
public:
    SimpleTessellatedCube * super ;
    ThisPrivate(SimpleTessellatedCube * s):super(s){
}
/****************************************************/
/****************************************************/
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer pointsBuffer;
	~ThisPrivate() {
		gl::deleteAny(pointsBuffer, vao);
		gl::deleteAny(program);
	}
	void initializeGL() {
		glClearDepth(1);
		glClearColor(0, 0, 0, 0);
#ifdef _DEBUG_OPENGL_QT_
		QGLDebugTool::setSimpleCallbackFunction();
		QGLDebugTool::test();
#endif
		gl::createVertexArrays(1, &vao);
		gl::createBuffers(1, &pointsBuffer);
		constexpr static const gl::Float points[] = {
			-0.5f,-0.5f,0,1,
			 0.5f,-0.5f,0,1,
		    -0.5f, 0.5f,0,1,
			 0.5f, 0.5f,0,1,
		};
		gl::bufferData(pointsBuffer, sizeof(points), points);
		vao.bindBuffer(0, pointsBuffer);

		constexpr static const char vs[] =
			R"(#version 450 core 
layout(location=0) in vec4 iposition ;
out vec4 color_0_;
void main(){ 
gl_Position = iposition ;
color_0_ = (iposition +1)/2;
}

)";

		constexpr static const char tes[] = R"(#version 450 core 
layout (quads, equal_spacing, cw) in;
in vec4 color_0_[];
out vec4 color_1_;
void main(){

{
vec4 p1 = mix(gl_in[0].gl_Position,
gl_in[1].gl_Position,
gl_TessCoord.x);

vec4 p2 = mix(gl_in[2].gl_Position,
gl_in[3].gl_Position,
gl_TessCoord.x);

gl_Position = mix(p1, p2, gl_TessCoord.y);
}

{
vec4 p1 = mix(color_0_[0] ,
color_0_[1],
gl_TessCoord.x);
vec4 p2 = mix(color_0_[2],
color_0_[3],
gl_TessCoord.x);
color_1_ =   mix(p1, p2, gl_TessCoord.y);
}


}

)";

		constexpr static const char fs[] = R"(#version 450 core 
out vec4 fcolor ; 
in vec4 color_1_;
void main(){
fcolor = color_1_ ;
}
)";

		program = gl::VTEFProgramLoadSources(vs, tes, fs);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}
	void paintGL() {
		gl::NamedFrameBufferObject root;
		root.clearColor(0.2f, 0.1f, 0.1f, 1);
		{
			using namespace gl::DrawArrays;
			Pack pack(Mode::PATCHES, 0, 4);
			pack.bindFrameBuffer(root);
			pack.useProgram(program);
			pack.bindVertexArray(vao);
			pack.patchVertices(4);
			const static gl::PatchLevels levels( { 6,7,8,9 }, { 5,6,7,8 } );
			pack.patchLevels(levels);
			gl::draw(pack);
		}
	}
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleTessellatedCube::SimpleTessellatedCube(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleTessellatedCube::~SimpleTessellatedCube(){
    delete thisp;
}

void SimpleTessellatedCube::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void SimpleTessellatedCube::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleTessellatedCube *);
std::unique_ptr<SimpleTessellatedCube, PaintStateDeleteFunction>
paintState(this, [](SimpleTessellatedCube * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleTessellatedCube::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


