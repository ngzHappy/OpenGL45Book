/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include "SimpleLoadModel.hpp"
#include <OpenGLTool/ModelLoader.hpp>
#include <OpenGLTool/ModelLoaderCallbacks.hpp>
#include <OpenGLTool/QGLApplication.hpp>
#include <OpenGLTool/GLMTool.hpp>
#include <QTimer>
#include <memory>
#include <cstdlib>
#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class SimpleLoadModel::ThisPrivate{
public:
    SimpleLoadModel * super ;
    ThisPrivate(SimpleLoadModel * s):super(s){
        glClearDepth(1);
        glClearColor(0,0,0,0);
    #ifdef _DEBUG_OPENGL_QT_
            QGLDebugTool::setSimpleCallbackFunction();
            QGLDebugTool::test();
    #endif
        initializeGL();
}
    glm::mat4 rotateMatrix;
    gl::Program program;
    gl::NamedVertexArrayObject vao;
    gl::NamedBuffer points,pointsIndex;
    QTimer timer ;
    ~ThisPrivate(){
        timer.stop();
        gl::deleteAny(program,vao,points,pointsIndex);
    }
    void initializeGL(){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        {//初始化数据
        gl::createVertexArrays(1,&vao);
        gl::VertexElementCallBack callBack ;
        callBack.begin();
        {
            QString modelDir = QApplication::applicationDirPath()+"/../models";
            modelDir+="/box.obj";
            gl::modelLoader(modelDir.toLocal8Bit().toStdString(),&callBack);
        }
        callBack.end();
        gl::createBuffers(1,&points);
        gl::createBuffers(1,&pointsIndex);
        gl::bufferData(
                    points,
                    callBack.points.size()*sizeof(callBack.points[0]),
                    &(callBack.points[0])
                    );
        gl::bufferData(
                    pointsIndex,
                    callBack.triangles.size()*sizeof(callBack.triangles[0]),
                    &callBack.triangles[0]
                    );
        vao.bindBuffer(0,points,
                       0,sizeof(callBack.points[0]),
                       0,gl::NamedVertexArrayObject::Size::Three);
        vao.bindElementBuffer(pointsIndex);
        }
        {//初始化program
            static constexpr char vertex_shader_source[] = R"(
    #version 450
    layout(location=0) in vec4 ipositon;
    layout(location=1) uniform mat4 mvp = mat4(1);
    out vec4 color;
    void main(void){
        gl_Position = mvp * ipositon ;
        color = (ipositon+1)/2;
    }

    )";
            static constexpr char fragment_shader_source[] = R"(
    #version 450
    in vec4 color;
    out vec4 finalColor;
    void main(void){
        finalColor = color;
    }
    )";

            program = gl::VFProgramLoadSources(
                        vertex_shader_source,
                        fragment_shader_source
                        );
        }
        {//自动旋转
            typedef void(QTimer::*TT)();
            timer.connect(&timer,TT(&QTimer::timeout),
                          [this](){
                auto rand_=[]()->float{
                        return  (0.1f+float(rand()%2222)/2222);
            };
                rotateMatrix = glm::rotate(rotateMatrix,rand_(),glm::vec3(rand_(),rand_(),rand_()));
                super->updateGL();
            }
                          );
            timer.start(666);
        }
    }
    void paintGL(){
        gl::clearAll();
        program.use();
        program.bindVertexArray(vao);
        program.setUniformMatrix4fv(1,1,false,&(rotateMatrix[0][0]));
        gl::drawElements(
                    gl::DrawElementsMode::TRIANGLES,36,
                    gl::DrawElementsType::UNSIGNED_INT
                    );
    }
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

SimpleLoadModel::SimpleLoadModel(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


SimpleLoadModel::~SimpleLoadModel(){
    delete thisp;
}

void SimpleLoadModel::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
    }
}

void SimpleLoadModel::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(SimpleLoadModel *);
std::unique_ptr<SimpleLoadModel, PaintStateDeleteFunction>
paintState(this, [](SimpleLoadModel * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void SimpleLoadModel::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


