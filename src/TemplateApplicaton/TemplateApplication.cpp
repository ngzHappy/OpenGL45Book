#include "TemplateApplication.hpp"
#include <OpenGLTool/OpenGLTemplateString.hpp>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

namespace  {

const QString hppFile= QString::fromUtf8(u8R"(/*utf8 with bom*/
#ifndef _0_${CLASSNAME}__HPP__0x00
#define _0_${CLASSNAME}__HPP__0x00

#include <QGLWidget>

class ${CLASSNAME} :public QGLWidget {
public:
${CLASSNAME}( QWidget * =0 );
~${CLASSNAME}();
private:
class ThisPrivate;
friend class ThisPrivate;
ThisPrivate * thisp = 0;
bool isOpenGLInited = false;
bool isOpenGLPainting = false;
protected:
virtual void paintGL() override;
virtual void initializeGL() override;
virtual void resizeGL(int w, int h)override;
};

#endif

)"

);

const QString cppFile = QString::fromUtf8(u8R"(/*utf8 with bom*/
#include <OpenGLTool/OpenGLAPI.hpp>
#include <OpenGLTool/QGLTools.hpp>
#include <memory>
#include "${CLASSNAME}.hpp"

#ifdef QT_DEBUG
#ifndef _DEBUG_OPENGL_QT_
#define _DEBUG_OPENGL_QT_
#endif
#endif
#ifdef _DEBUG_OPENGL_QT_
#include <GL/QInitializeDebugContext.hpp>
#endif
class ${CLASSNAME}::ThisPrivate{
public:
    ${CLASSNAME} * super ;
    ThisPrivate(${CLASSNAME} * s):super(s){
}
/****************************************************/
/****************************************************/
    ~ThisPrivate(){}
    void initializeGL(){
glClearDepth(1);
glClearColor(0,0,0,0);
#ifdef _DEBUG_OPENGL_QT_
QGLDebugTool::setSimpleCallbackFunction();
QGLDebugTool::test();
#endif

 }
    void paintGL(){
        //write your code here
    }
/****************************************************/
/****************************************************/
    void resizeGL(int w,int h){
        glViewport(0,0,w,h);
    }
};

${CLASSNAME}::${CLASSNAME}(QWidget * p):
QGLWidget(QGLTools::AutoQGLFormat(4,5), p){
#ifdef _DEBUG_OPENGL_QT_
    qInitializeDebugContext(this);
#endif
    this->resize(500,500);
    this->setMinimumHeight(64);
    this->setMinimumWidth(64);
}


${CLASSNAME}::~${CLASSNAME}(){
    delete thisp;
}

void ${CLASSNAME}::initializeGL(){
    if(isOpenGLInited){return;}
    isOpenGLInited=true;
    bool isGLEWInit = QGLTools::QGLWidgetInitializeGlew(this);
    if(isGLEWInit && (0== thisp)){
        thisp = new ThisPrivate(this);
        thisp->initializeGL();
    }
}

void ${CLASSNAME}::paintGL(){
if(0==thisp){return;}
if (isOpenGLPainting) { return; }
typedef void(*PaintStateDeleteFunction)(${CLASSNAME} *);
std::unique_ptr<${CLASSNAME}, PaintStateDeleteFunction>
paintState(this, [](${CLASSNAME} * this__) {this__->isOpenGLPainting = false; });
isOpenGLPainting = true;
{
    thisp->paintGL();
}
}
void ${CLASSNAME}::resizeGL(int w,int h){
    thisp->resizeGL(w,h);
}


)"

);

const QString mcppFile  = QString::fromUtf8(
u8R"(/*utf8 with bom*/
#include "${CLASSNAME}.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    ${CLASSNAME} widget;
    widget.setWindowTitle("${CLASSNAME}");
	widget.show();

    return app.exec();
}

)"
	);


const QString proFile = QString::fromUtf8(u8R"(
include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)


TEMPLATE = app

QT+=core
QT+=widgets
QT+=gui
QT+=opengl

SOURCES+= \
    main.cpp \
    ${CLASSNAME}.cpp
HEADERS+= \
    ${CLASSNAME}.hpp



INCLUDEPATH+=$$PWD/../OpenGLTool


win32-msvc*:{
CONFIG *= console
}

CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
LIBS += -L$$OUT__DIR__BASE__/bind -lQLOpenGLTool
LIBS += -L$$OUT__DIR__BASE__/bind -lQLAssimp
}else{
DESTDIR = $$OUT__DIR__BASE__/bin
LIBS += -L$$OUT__DIR__BASE__/bin -lQLOpenGLTool
LIBS += -L$$OUT__DIR__BASE__/bin -lQLAssimp
}



include($$PWD/../openglBaseLibs.pri)



)"
);

}

int getOpenGLApplicaton(
        const QString & dirName,
        const QString & ApplicationName
        ){

    {
        QDir dir;
        if(dir.cd(dirName)==false){
			dir.mkpath(dirName);
			if (dir.cd(dirName) == false) { return -90; }
		}
        
    }

    {
        gl::TemplateString<QString> hpp(hppFile);
        QFile file( dirName+"/"+ApplicationName+".hpp" );
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        stream << bom ;
        stream << hpp("CLASSNAME",ApplicationName);
    }

	{
		gl::TemplateString<QString> cpp(cppFile);
		QFile file(dirName + "/" + ApplicationName + ".cpp");
		file.open(QIODevice::WriteOnly);
		QTextStream stream(&file);
		stream.setCodec(QTextCodec::codecForName("UTF-8"));
		stream << bom;
		stream << cpp("CLASSNAME", ApplicationName);
	}

	{
		gl::TemplateString<QString> mcpp (mcppFile );
		QFile file(dirName + "/" +   "main.cpp");
		file.open(QIODevice::WriteOnly);
		QTextStream stream(&file);
		stream.setCodec(QTextCodec::codecForName("UTF-8"));
		stream << bom;
		stream << mcpp("CLASSNAME", ApplicationName);
	}

	{
		gl::TemplateString<QString> pro(proFile);
		QFile file(dirName + "/"+ ApplicationName + ".pro");
		file.open(QIODevice::WriteOnly);
		QTextStream stream(&file);
		stream.setCodec(QTextCodec::codecForName("UTF-8"));
		stream << pro("CLASSNAME", ApplicationName);
	}

    return 0;
}
