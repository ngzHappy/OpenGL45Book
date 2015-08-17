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
#include <vector>
#include <map>
#include <QTimer>
#include <QFileInfo>
#include <QImage>
#include <QDir>
#include "ModelView.hpp"

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif

namespace {

	template<typename T>
	class UniqueGLObject :public std::unique_ptr<T, void(*)(T*)> {
	public:
		UniqueGLObject(T * d) :std::unique_ptr<T, void(*)(T*)>(
			d, [](T * _d) {
			if (0 == _d) { return; }
			gl::deleteAny(*_d);
			delete _d;
		}
			) {}
		UniqueGLObject() :std::unique_ptr<T, void(*)(T*)>(
			new T,
			[](T * _d) {
			if (0 == _d) { return; }
			gl::deleteAny(*_d);
			delete _d; }
			) {}
	};

}

class ModelView::ThisPrivate{
public:
    ModelView * super ;
    ThisPrivate(ModelView * s):super(s){
}
	/****************************************************/
	/****************************************************/
	gl::Program program3, program2, program1, program0;
	std::map<int, UniqueGLObject<gl::NamedVertexArrayObject>   > vao;
	std::map<int, UniqueGLObject<gl::NamedTexture>             > texture;
	std::map<int, UniqueGLObject<gl::NamedBuffer>              > PNTBuffer;
	std::map<int, UniqueGLObject<gl::NamedBuffer>              > IPNTBuffer;
	std::map<int, int>                                           IPNTSize;
	QTimer timer;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 translateMatrix;
	float rotateValue;

	~ThisPrivate() {
		timer.stop();
		gl::deleteAny(program1);
		gl::deleteAny(program2);
		gl::deleteAny(program3);
		gl::deleteAny(program0);
	}
	void initializeGL() {
		rotateValue = 0;
		glClearDepth(1);
		glClearColor(0, 0, 0, 0);
#ifdef _DEBUG_OPENGL_QT_
		QGLDebugTool::setSimpleCallbackFunction();
		QGLDebugTool::test();
#endif
		
			{
				const static QString vs0 = R"(#version 450
layout(location=0) in vec3 ip_;
layout(location=1) in vec3 in_;
layout(location=2) in vec2 it_;
layout(location=0) uniform mat4 rotateMatrix ;
smooth out vec2 tuv ;
void main(){
tuv = vec2( it_.x , it_.y ) ;
gl_Position =  vec4(ip_,1)  ;
gl_Position = rotateMatrix * gl_Position ;
} 
)";
				const static QString vs1 = R"(#version 450
layout(location=0) in vec3 ip_;
layout(location=1) in vec3 in_;
layout(location=2) in vec2 it_;
layout(location=0) uniform mat4 rotateMatrix ;
smooth out vec2 tuv ;
void main(){
tuv = vec2( it_.x , 1-it_.y ) ;
gl_Position =  vec4(ip_,1)  ;
gl_Position = rotateMatrix * gl_Position ;
} 
)";
				const static QString vs2 = R"(#version 450
layout(location=0) in vec3 ip_;
layout(location=1) in vec3 in_;
layout(location=2) in vec2 it_;
layout(location=0) uniform mat4 rotateMatrix ;
smooth out vec2 tuv ;
void main(){
tuv = vec2( it_.x , it_.y ) ;
gl_Position =  vec4(ip_.x,ip_.y,-ip_.z,1)  ;
gl_Position = rotateMatrix * gl_Position ;
} 
)";
				const static QString vs3 = R"(#version 450
layout(location=0) in vec3 ip_;
layout(location=1) in vec3 in_;
layout(location=2) in vec2 it_;
layout(location=0) uniform mat4 rotateMatrix ;
smooth out vec2 tuv ;
void main(){
tuv = vec2( it_.x , 1-it_.y ) ;
gl_Position =  vec4(ip_.x,ip_.y,-ip_.z,1)  ;
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
				program0 = gl::VFProgramLoadSources(vs0, fs);
				program1 = gl::VFProgramLoadSources(vs1, fs);
				program2 = gl::VFProgramLoadSources(vs2, fs);
				program3 = gl::VFProgramLoadSources(vs3, fs);
			}

			{
				super->isOpenGLInited = false;
				QString fileName__ = QApplication::applicationDirPath();
				fileName__ += "/../models/spider.obj";
				this->loadModel( fileName__ );
				super->isOpenGLInited = true;
			}

		{
			typedef void(QTimer::* TT)();
			timer.connect(&timer, TT(&QTimer::timeout),
				[this]() {rotate();}
			);
		}

		timer.start(666);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void rotate() {
		if (rotateValue>3.141592654f * 2) {
			rotateValue -= 3.141592654f * 2;
		}
		rotateMatrix = 
			glm::rotate(rotateValue, glm::vec3(0, 1, 0))*\
			scaleMatrix*translateMatrix;
		super->updateGL();
		rotateValue += 0.211f;
	}

	void loadModel( const QString & modelName__  ) {
		class ThisLocker {
			ThisPrivate * __this;
		public:
			ThisLocker(ThisPrivate * _):__this(_) {
				__this->timer.stop();
				__this->super->isOpenGLInited = false;
			}
			~ThisLocker() {
				__this->timer.start(666);
				__this->super->isOpenGLInited = true;
			}
		}_(this);

		{
			gl::VertexTextureNormalElementCallBack callBack;

			callBack.begin();
			if (gl::modelLoader(
				modelName__.toLocal8Bit().toStdString(),
				&callBack
				) == false) {
				return  ;
			}
			callBack.end();

			vao.clear();
			texture.clear();
			PNTBuffer.clear();
			IPNTBuffer.clear();
			IPNTSize.clear();

			const double scale__ = (std::max)({
				double(callBack.xMax) - callBack.xMin ,
				double(callBack.yMax) - callBack.yMin,
				double(callBack.zMax) - callBack.zMin
			});

			translateMatrix = glm::translate( glm::vec3(
				-float(callBack.xMax*0.5+ callBack.xMin*0.5),
				-float(callBack.yMax*0.5+ callBack.yMin*0.5),
				-float(callBack.zMax*0.5+ callBack.zMin*0.5))
				);

			scaleMatrix = glm::scale(glm::vec3(
				float( 1.10 / scale__),
				float( 1.10 / scale__),
				float(-1.10 / scale__)
				));

			{
				QFileInfo info(modelName__);
				const QString path__ = info.absolutePath();
				for (const auto & i:callBack.textures) {
					QString fileName__ = QString::fromLocal8Bit(i.second.data());
					QDir dir__(path__);
					fileName__ = dir__.filePath(fileName__);
					fileName__ = dir__.cleanPath( fileName__ );
					QImage texture__( fileName__ );
					callBack.texturesImage[i.first] = texture__;
				}
			}

			for (const auto & i : callBack.triangles) {

				UniqueGLObject<gl::NamedVertexArrayObject> _vao;
				UniqueGLObject<gl::NamedTexture> _texture;
				UniqueGLObject<gl::NamedBuffer> _PNTBuffer;
				UniqueGLObject<gl::NamedBuffer> _IPNTBuffer;
				gl::createBuffers(1, _PNTBuffer.get());
				gl::createBuffers(1, _IPNTBuffer.get());
				gl::createVertexArrays(1, _vao.get());
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
					0, gl::NamedVertexArrayObject::Size::Three
					);
				_vao->bindBuffer(1, *_PNTBuffer,
					0, sizeof(pnt[0]),
					sizeof(gl::Float) * 3, gl::NamedVertexArrayObject::Size::Three
					);
				_vao->bindBuffer(2, *_PNTBuffer,
					0, sizeof(pnt[0]),
					sizeof(gl::Float) * 6, gl::NamedVertexArrayObject::Size::Two
					);

				vao[i.first] = std::move(_vao);
				texture[i.first] = std::move(_texture);
				PNTBuffer[i.first] = std::move(_PNTBuffer);
				IPNTBuffer[i.first] = std::move(_IPNTBuffer);
				IPNTSize[i.first] = ipnt.size() * 3;

			}
		}

		super->updateGL();
	}

	void paintGL() {
		gl::NamedFrameBufferObject root;
		constexpr float clearColor[] = { 0.3f,0.3f,0.3f,1 };
		root.clearColor(clearColor);
		root.clearDepth(1);
		auto drawFunction = [this,root](gl::Program program_){
			program_.use();
			program_.bindFrameBuffer(root);
			program_.setUniformMatrix4fv(0, 1, false, &(rotateMatrix[0][0]));
			//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			for (const auto & i : IPNTSize) {
				program_.bindVertexArray(*(vao[i.first]));
				program_.bindTexture(*(texture[i.first]), 0, GL_TEXTURE_2D);

				using namespace gl::DrawElements;
				Pack pack(
					Mode::TRIANGLES,
					i.second,
					Type::UNSIGNED_INT,
					nullptr);
				gl::draw(pack);
			}
		};

		const auto width = super->width()/2;
		const auto height = super->height()/2;
		
		glViewport(0,height ,width ,height );
		drawFunction(program0);
	    glViewport(width, height, width, height);
		drawFunction(program1);
		glViewport(0, 0, width, height);
		drawFunction(program2);
		glViewport(width, 0, width, height);
		drawFunction(program3);
		
	}
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

ModelView::ModelView(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


ModelView::~ModelView(){
    delete thisp;
}

void ModelView::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void ModelView::paintGL(){
if(0==thisp){return;}
if (isOpenGLInited == false) { return; }
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(ModelView *);
std::unique_ptr<ModelView, PaintStateDeleteFunction>
paintState(this, [](ModelView * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void ModelView::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}

void ModelView::loadModel(const QString & n) {
	thisp->loadModel(n);
}

/*

*/

