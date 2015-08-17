/*utf8 with bom*/
#include "SimpleComputeShader.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleComputeShader widget;
    widget.setWindowTitle("SimpleComputeShader");
	widget.show();

    return app.exec();
}

