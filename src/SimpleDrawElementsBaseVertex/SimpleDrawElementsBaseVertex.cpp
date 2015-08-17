/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleDrawElementsBaseVertex.hpp"
#include <memory>
#include <QTimer>
namespace {
	constexpr float operator""_d2r(long double value_) {
		return value_*3.141592654 / 180;
	}
}

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleDrawElementsBaseVertex::ThisPrivate{
public:
    SimpleDrawElementsBaseVertex * super ;
    ThisPrivate(SimpleDrawElementsBaseVertex * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
	gl::NamedBuffer pointsBuffer;
	gl::NamedBuffer pointsIndexBuffer;
	gl::NamedVertexArrayObject vao;
	gl::Program program;
	int baseIndex = 0;
	QTimer * timer;
	~ThisPrivate() {
		timer->stop();
		gl::deleteAny(pointsBuffer, pointsIndexBuffer, vao, program);
		timer->deleteLater();
	}
    void initializeGL(){
		timer = new QTimer;
		glClearColor(0.2f, 0.2f, 0.2f, 1);
		const static gl::Float points[] = {
		/* 0*/std::cos(360.0_d2r),                std::sin(360.0_d2r),0,1,
		/* 1*/std::cos(360.0_d2r - 72.0_d2r),     std::sin(360.0_d2r - 72.0_d2r),0,1,
		/* 2*/std::cos(360.0_d2r - 2.0f*72.0_d2r),std::sin(360.0_d2r - 2.0f*72.0_d2r),0,1,
		/* 3*/std::cos(360.0_d2r - 3.0f*72.0_d2r),std::sin(360.0_d2r - 3.0f*72.0_d2r),0,1,
		/* 4*/std::cos(360.0_d2r - 4.0f*72.0_d2r),std::sin(360.0_d2r - 4.0f*72.0_d2r),0,1,
		/* 5*/std::cos(345.6_d2r),                std::sin(345.6_d2r),0,1.2f,
		/* 6*/std::cos(345.6_d2r - 72.0_d2r),     std::sin(345.6_d2r - 72.0_d2r),0,1.2f,
		/* 7*/std::cos(345.6_d2r - 2.0f*72.0_d2r),std::sin(345.6_d2r - 2.0f*72.0_d2r),0,1.2f,
		/* 8*/std::cos(345.6_d2r - 3.0f*72.0_d2r),std::sin(345.6_d2r - 3.0f*72.0_d2r),0,1.2f,
		/* 9*/std::cos(345.6_d2r - 4.0f*72.0_d2r),std::sin(345.6_d2r - 4.0f*72.0_d2r),0,1.2f,
		/*10*/std::cos(331.2_d2r),                std::sin(331.2_d2r),0,1.4f,
		/*11*/std::cos(331.2_d2r - 72.0_d2r),     std::sin(331.2_d2r - 72.0_d2r),0,1.4f,
		/*12*/std::cos(331.2_d2r - 2.0f*72.0_d2r),std::sin(331.2_d2r - 2.0f*72.0_d2r),0,1.4f,
		/*13*/std::cos(331.2_d2r - 3.0f*72.0_d2r),std::sin(331.2_d2r - 3.0f*72.0_d2r),0,1.4f,
		/*14*/std::cos(331.2_d2r - 4.0f*72.0_d2r),std::sin(331.2_d2r - 4.0f*72.0_d2r),0,1.4f,
		/*15*/std::cos(316.8_d2r),                std::sin(316.8_d2r),0,1.6f,
		/*16*/std::cos(316.8_d2r - 72.0_d2r),     std::sin(316.8_d2r - 72.0_d2r),0,1.6f,
		/*17*/std::cos(316.8_d2r - 2.0f*72.0_d2r),std::sin(316.8_d2r - 2.0f*72.0_d2r),0,1.6f,
		/*18*/std::cos(316.8_d2r - 3.0f*72.0_d2r),std::sin(316.8_d2r - 3.0f*72.0_d2r),0,1.6f,
		/*19*/std::cos(316.8_d2r - 4.0f*72.0_d2r),std::sin(316.8_d2r - 4.0f*72.0_d2r),0,1.6f,
		/*20*/std::cos(302.4_d2r),                std::sin(302.4_d2r),0,1.8f,
		/*21*/std::cos(302.4_d2r - 72.0_d2r),     std::sin(302.4_d2r - 72.0_d2r),0,1.8f,
		/*22*/std::cos(302.4_d2r - 2.0f*72.0_d2r),std::sin(302.4_d2r - 2.0f*72.0_d2r),0,1.8f,
		/*23*/std::cos(302.4_d2r - 3.0f*72.0_d2r),std::sin(302.4_d2r - 3.0f*72.0_d2r),0,1.8f,
		/*24*/std::cos(302.4_d2r - 4.0f*72.0_d2r),std::sin(302.4_d2r - 4.0f*72.0_d2r),0,1.8f,
		};
		constexpr static gl::UnsignedShort pointsIndex[] = {
			1,4,4,2,2,0,0,3,3,1,
		};

		gl::createBuffers(1, &pointsIndexBuffer);
		gl::createBuffers(1, &pointsBuffer);

		gl::bufferData(pointsBuffer, sizeof(points), points);
		gl::bufferData(pointsIndexBuffer, sizeof(pointsIndex), pointsIndex);

		gl::createVertexArrays(1, &vao);

		vao.bindBuffer(0, pointsBuffer, 0);
		vao.bindElementBuffer(pointsIndexBuffer);

		static constexpr char vertex_shader_source[] = R"(
#version 450
layout(location=0) in vec4 ipositon;

void main(void){
    gl_Position = ipositon ;
	
}

)";
		static constexpr char fragment_shader_source[] = R"(
#version 450
out vec4 finalColor;
void main(void){
    finalColor = vec4(1,0.6,0.1,1);
}
)";

		program = gl::VFProgramLoadSources(vertex_shader_source, fragment_shader_source);

		typedef void(QTimer::*TT)();
		timer->connect(timer, TT(&QTimer::timeout), [this]() {
			++baseIndex;
			if (baseIndex > 4) { baseIndex = 0; }
			super->updateGL();
		});
		timer->start(666);
	}
    void paintGL(){
		gl::clearAll();
		program.use();
		program.bindVertexArray(vao);
		using namespace gl::DrawElementsBaseVertex;
		gl::drawElementsBaseVertex(
			Mode::LINES,
			10 ,
			Type::UNSIGNED_SHORT,
			0,
			baseIndex*5
			);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleDrawElementsBaseVertex::SimpleDrawElementsBaseVertex(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleDrawElementsBaseVertex::~SimpleDrawElementsBaseVertex(){
    delete thisp;
}

void SimpleDrawElementsBaseVertex::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleDrawElementsBaseVertex::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleDrawElementsBaseVertex *);
std::unique_ptr<SimpleDrawElementsBaseVertex, PaintStateDeleteFunction>
paintState(this, [](SimpleDrawElementsBaseVertex * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleDrawElementsBaseVertex::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


