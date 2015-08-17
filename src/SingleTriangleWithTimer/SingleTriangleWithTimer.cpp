/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SingleTriangleWithTimer.hpp"
#include <memory>
#include <QTimer>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SingleTriangleWithTimer::ThisPrivate{
public:
    SingleTriangleWithTimer * super ;
    ThisPrivate(SingleTriangleWithTimer * s):super(s){
        timer = new QTimer ;
        glClearDepth(1);
        glClearColor(0,0,0,0);
#ifdef _DEBUG_OPENGL_QT_
        QGLDebugTool::setSimpleCallbackFunction();
        QGLDebugTool::test();
#endif
        initializeGL();
    }
    QTimer * timer =0;
    gl::Program program;
    gl::NamedVertexArrayObject vao;
    ~ThisPrivate(){
        timer->stop();
        timer->deleteLater();
        gl::deleteAny(program,vao);
    }
    void initializeGL(){
		static constexpr char vertex_shader_source[] = R"(
        #version 450
        uniform mat4 vertices=mat4(
            -0.5000,   -0.5000,         0,    1.0000,//first column 
             0.5000,   -0.5000,         0,    1.0000,//second column 
                  0,    0.5000,         0,    1.0000,//third column 
             1.0000,    1.0000,    1.0000,    1.0000 //fourth column 
            );
		layout(location=1) uniform vec4 offsetValue = vec4(0,0,0,0);
        void main(void){
            gl_Position = vertices[gl_VertexID]+offsetValue;
        }

        )";
        static constexpr char fragment_shader_source[] = R"(
        #version 450
                out vec4 color;
        void main(void){
            color = vec4(0.0, 0.8, 1.0, 1.0);
        }
        )";
        program = gl::VFProgramLoadSources(
                    vertex_shader_source,fragment_shader_source
                    );
        gl::createVertexArrays(1,&vao);

        typedef void(QTimer::*TT)();
        timer->connect(timer,TT(&QTimer::timeout),[this](){
            auto rand_value = []()->float{return (float(rand()%1000)/1000-0.5f);};
            gl::Float offset[4]={rand_value(),rand_value(),0,0};
            program.setUniform4fv(1,1,offset);
            super->updateGL();
        });
        timer->start(1000);

    }
    void paintGL(){
        gl::clearAll();
        gl::useProgram(program);
        gl::bindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SingleTriangleWithTimer::SingleTriangleWithTimer(QWidget * p):
    QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SingleTriangleWithTimer::~SingleTriangleWithTimer(){
    delete thisp;
}

void SingleTriangleWithTimer::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SingleTriangleWithTimer::paintGL(){
    if(0==thisp){return;}
    if (isOpenGLPainting) { return; }
    typedef void(*PaintStateDeleteFunction)(SingleTriangleWithTimer *);
    std::unique_ptr<SingleTriangleWithTimer, PaintStateDeleteFunction>
            paintState(this, [](SingleTriangleWithTimer * this__) {this__->isOpenGLPainting = false; });
    isOpenGLPainting = true;
    {
        thisp->paintGL();
    }
}
void SingleTriangleWithTimer::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


