/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include "SingleCube.hpp"
#include <memory>
#include <cmath>
#include <QTimer>
#include <array>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SingleCube::ThisPrivate{
public:
    SingleCube * super ;
    ThisPrivate(SingleCube * s):super(s){
        glClearDepth(1);
        glClearColor(0.5f,0.6f,0.7f,1);
		super->setMinimumHeight(500);
		super->setMinimumWidth(500);

    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
	glm::vec3 currentPosition;
    gl::NamedBuffer pointsBuffer ;
    gl::NamedBuffer indexBuffer ;
    gl::NamedVertexArrayObject cubeVAO ;
    gl::Program cubeProgram ;
	glm::mat4 MVMatrix;
	QTimer * timer = 0;
    ~ThisPrivate(){
		timer->stop();
		timer->deleteLater();
        gl::deleteAny(pointsBuffer,indexBuffer,cubeVAO,cubeProgram);
    }
    void initializeGL(){
		MVMatrix = glm::scale(glm::vec3(0.125f, 0.125f, 0.125f));

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);

		timer = new QTimer;
        static constexpr gl::UnsignedShort index[]={
            0,4,1,1,4,5,
            1,5,2,2,5,6,
            2,6,3,3,6,7,
            3,7,0,0,7,4,
            3,0,2,2,0,1,
            6,5,7,7,5,4,
        };
        static constexpr gl::Float points[]={
            -1, 1, 1,/*0*/
             1, 1, 1,/*1*/
             1, 1,-1,/*2*/
            -1, 1,-1,/*3*/
            -1,-1, 1,/*4*/
             1,-1, 1,/*5*/
             1,-1,-1,/*6*/
            -1,-1,-1,/*7*/
        };
		static constexpr char vs[] = R"(
#version 450
layout(location=0)in vec3 position;
layout(location=1)uniform mat4 mvMatrix=mat4(1);
out vec4 color;

void main(void) {

gl_Position = mvMatrix*vec4( position  ,1);
color = vec4( (position+1)/2,1 );

}

)";
		static constexpr char fs[] = R"(
#version 450

in vec4 color;  
out vec4 finalColor;

void main(void){
finalColor = color;
}

)";
        gl::createBuffers(1,&pointsBuffer);
        gl::createBuffers(1,&indexBuffer);
        gl::createVertexArrays(1,&cubeVAO);
        cubeProgram = gl::VFProgramLoadSources(vs,fs);
        gl::bufferData(indexBuffer,sizeof(index),index);
        gl::bufferData(pointsBuffer,sizeof(points),points);
        cubeVAO.bindElementBuffer(indexBuffer);
        cubeVAO.bindBuffer(0,pointsBuffer,
                           0,3*sizeof(gl::Float),
                           0,gl::NamedVertexArrayObject::Size::Three);

		typedef void(QTimer::*TT)();
		timer->connect(timer, TT(&QTimer::timeout), [this]() {
			rotateFunction();
        });

		timer->start( 200 );

    }
    void paintGL(){

        gl::clearAll();
        cubeProgram.use();
        cubeProgram.bindVertexArray(cubeVAO);
		cubeProgram.setUniformMatrix4fv(1, 1, false, &MVMatrix[0][0]);
        gl::drawElements(
                    gl::DrawElementsMode::TRIANGLES,
                    36,gl::DrawElementsType::UNSIGNED_SHORT
                    );

    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }

	void rotateFunction() {
        auto rand_value = []()->float {return float(rand() % 15678) / 15678; };
		auto rand_pos = [rand_value]()->glm::vec3 {
			glm::vec3 rpos;
			float & x = rpos[0];
			float & y = rpos[1];
			float & z = rpos[2];

			do {
				x = rand_value();
			} while ((x<=0.2f)||(x>=0.8f));

			do {
				z = rand_value();
			} while ((z <= 0.2f) || (z >= 0.8f));

			float ty =  1 - x*x  ;
			
			y = std::sqrt(ty*z);
			z = std::sqrt(ty*(1-z));

			x *= rand_value() > 0.5f ? 1 : -1;
			y *= rand_value() > 0.5f ? 1 : -1;
			z *= rand_value() > 0.5f ? 1 : -1;

			return rpos;
		};
		std::array<gl::Float,4> axisAndRotateValue{0,0,0,0};

		do {
			axisAndRotateValue = {
				rand_value() - 0.5f,
				rand_value() - 0.5f,
				rand_value() - 0.5f,
				rand_value()
			};
		} while (
			(axisAndRotateValue[0] == 0)&& 
			(axisAndRotateValue[1] == 0)&& 
			(axisAndRotateValue[2] == 0));
		currentPosition += rand_pos()/11.1f ;

		auto limit_11=[](float & value) {
			if (value > 1) { value -= 1; }
			if (value < -1) { value += 1; }
		};

		limit_11( currentPosition.x );
		limit_11( currentPosition.y );
		limit_11( currentPosition.z );

		MVMatrix = glm::rotate(
			glm::translate(currentPosition),
			axisAndRotateValue[3],
			*((glm::vec3*)(&axisAndRotateValue))
			);

		MVMatrix *= glm::scale(glm::vec3(0.125f, 0.125f, 0.125f));

		super->updateGL();
	}

};

SingleCube::SingleCube(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SingleCube::~SingleCube(){
    delete thisp;
}

void SingleCube::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SingleCube::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SingleCube *);
std::unique_ptr<SingleCube, PaintStateDeleteFunction>
paintState(this, [](SingleCube * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SingleCube::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


