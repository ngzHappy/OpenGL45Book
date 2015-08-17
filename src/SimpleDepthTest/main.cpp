/*utf8 with bom*/
#include "SimpleDepthTest.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDepthTest widget;
    widget.setWindowTitle("SimpleDepthTest");
	widget.show();

    return app.exec();
}

