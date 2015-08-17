/*utf8 with bom*/
#include "SimpleMultiSampleFBO.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleMultiSampleFBO widget;
    widget.setWindowTitle("SimpleMultiSampleFBO");
	widget.show();

    return app.exec();
}

