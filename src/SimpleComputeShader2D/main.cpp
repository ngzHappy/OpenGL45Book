/*utf8 with bom*/
#include "SimpleComputeShader2D.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleComputeShader2D widget;
    widget.setWindowTitle("SimpleComputeShader2D");
	widget.show();

    return app.exec();
}

