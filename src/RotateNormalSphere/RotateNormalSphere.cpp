/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <OpenGLTool/QGLApplication.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include <memory>
#include <OpenGLTool/ModelLoader.hpp>
#include <OpenGLTool/ModelLoaderCallbacks.hpp>
#include <QDebug>
#include "RotateNormalSphere.hpp"
#include <QTimer>

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class RotateNormalSphere::ThisPrivate{
public:
    RotateNormalSphere * super ;
    ThisPrivate(RotateNormalSphere * s):super(s){
}
/****************************************************/
/****************************************************/
        gl::NamedVertexArrayObject vao ;
        gl::NamedBuffer  pointsNormalBuffer ;
        gl::NamedBuffer  indexBuffer ;
        gl::Program      program;
        glm::mat4        modelScale;
		glm::mat4        modelScaleBase;
		glm::mat4        normalMatrix ;
        gl::UnsignedInteger indexCount;
		QTimer timer;
		float rotate_value;
        ~ThisPrivate(){
			gl::deleteAny(program, indexBuffer, pointsNormalBuffer, vao);
		}
        void initializeGL(){
    {
		rotate_value = 0;
		constexpr static char vs[] = R"(#version 450
    layout(location=0) in vec4 iposition;
    layout(location=1) in vec4 inormal_  ;
    layout(location=1) uniform mat4 MVP ;
    layout(location=3) uniform mat4 NMVP ;
    layout(location=2) uniform vec4 light_pos = vec4(1,1,-1,1);
    out vec4 color ;
    void main(){
    gl_Position = MVP * iposition  ;
    vec4 inormal = NMVP * inormal_ ;
    vec3 light = light_pos.xyz - gl_Position.xyz ;
    light = normalize( light );
    float v = smoothstep(0,1, dot(light ,
    normalize( inormal.xyz ) ));
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

		modelScaleBase = glm::scale(glm::vec3(
            float( 1.50 / (callBack.xMax-callBack.xMin) ),
            float( 1.50 / (callBack.yMax-callBack.yMin)),
            float(-1.50 / (callBack.zMax-callBack.zMin))
            ));

		modelScale = modelScaleBase;
		normalMatrix = glm::mat4( 
			1,0, 0,0,
			0,1, 0,0,
			0,0,-1,0,
			0,0, 0,1
			);
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
	{
		typedef void(QTimer::*TT)();
		timer.connect( &timer,TT(&QTimer::timeout),
			[this]() {
			rotate();
			super->updateGL();
		}
			);
	}
	timer.start(666);
     }
	void rotate() {
		rotate_value += 0.29165789f;
#define __DPI__  (2*3.141592654f)
		if (rotate_value > __DPI__) { rotate_value -= __DPI__ ; }
		modelScale = glm::rotate(rotate_value,glm::vec3(0,1,0))  ;
		normalMatrix = glm::transpose( glm::inverse(modelScale) ) ;
		modelScale = modelScale*modelScaleBase;
		normalMatrix = normalMatrix*glm::mat4(
			1, 0,  0, 0,
			0, 1,  0, 0,
			0, 0, -1, 0,
			0, 0,  0, 1
			);
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
			program.setUniformMatrix4fv(
				3, 1, false, &(normalMatrix[0][0]));
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

RotateNormalSphere::RotateNormalSphere(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


RotateNormalSphere::~RotateNormalSphere(){
    delete thisp;
}

void RotateNormalSphere::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void RotateNormalSphere::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(RotateNormalSphere *);
std::unique_ptr<RotateNormalSphere, PaintStateDeleteFunction>
paintState(this, [](RotateNormalSphere * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void RotateNormalSphere::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


