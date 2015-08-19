/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <memory>
#include "TessellatedTriangle.hpp"

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif

#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif

class TessellatedTriangle::ThisPrivate{
public:
    TessellatedTriangle * super ;
    ThisPrivate(TessellatedTriangle * s):super(s){
}
/****************************************************/
/****************************************************/
	gl::Program program;
	gl::NamedVertexArrayObject vao;
	gl::NamedBuffer pointsBuffer;
    ~ThisPrivate(){
		gl::deleteAny( pointsBuffer, vao);
		gl::deleteAny(program);
	}
    void initializeGL(){
glClearDepth(1);
glClearColor(0,0,0,0);
#ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
#endif
gl::createVertexArrays(1,&vao);
gl::createBuffers(1,&pointsBuffer);
constexpr static const gl::Float points[] = {
	    0, 0.5f,0,1,
	-0.5f,-0.5f,0,1,
	 0.5f,-0.5f,0,1
};
gl::bufferData(pointsBuffer, sizeof(points), points);
vao.bindBuffer(0, pointsBuffer);

constexpr static const char vs[] = R"(#version 450 core 
 
layout(location=0) in vec4 iposition ;
out vec4 color_0_;
 void main(){ 
 gl_Position = iposition ;
 color_0_ = (gl_Position+1)/2;
}
)";

constexpr static const char tcs[] = R"(#version 450 core 
layout(vertices=3) out ;
in  vec4 color_0_[];
out vec4 color_1_[];
void main(){
if (gl_InvocationID == 0){
gl_TessLevelInner[0] = 5.0;
gl_TessLevelOuter[0] = 6.0;
gl_TessLevelOuter[1] = 7.0;
gl_TessLevelOuter[2] = 8.0;
}
gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;
color_1_[gl_InvocationID]= color_0_[gl_InvocationID];
}
)";

constexpr static const char tes[] = R"(#version 450 core 
in  vec4 color_1_[];
out vec4 color_2_  ;
layout (triangles, equal_spacing, cw) in;
void main(){
gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
gl_TessCoord.y * gl_in[1].gl_Position +
gl_TessCoord.z * gl_in[2].gl_Position);

color_2_ =gl_TessCoord.x*color_1_[0]+
gl_TessCoord.y*color_1_[1]+
gl_TessCoord.z*color_1_[2];

}

)";

constexpr static const char fs[] = R"(#version 450 core 
out vec4 fcolor ;
in  vec4 color_2_;
void main(){
fcolor = color_2_;
}
)";

program = gl::VTCTEFProgramLoadSources(vs,tcs,tes,fs);

glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

 }
    void paintGL(){
		{
			using namespace gl::DrawArrays;
			Pack pack(Mode::PATCHES, 0, 3);
			pack.useProgram(program);
			pack.bindVertexArray(vao);
			pack.patchVertices(3);
			gl::draw(pack);
		}
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }

};

TessellatedTriangle::TessellatedTriangle(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


TessellatedTriangle::~TessellatedTriangle(){
    delete thisp;
}

void TessellatedTriangle::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void TessellatedTriangle::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(TessellatedTriangle *);
std::unique_ptr<TessellatedTriangle, PaintStateDeleteFunction>
paintState(this, [](TessellatedTriangle * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}

void TessellatedTriangle::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


