/*utf8 with bom*/
#include "SimpleGeometry.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleGeometry widget;
    widget.setWindowTitle("SimpleGeometry");
	widget.show();

    return app.exec();
}

