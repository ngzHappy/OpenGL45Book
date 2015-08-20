/*utf8 with bom*/
#include "SimpleSamplerWrapRectangle.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleSamplerWrapRectangle widget;
    widget.setWindowTitle("SimpleSamplerWrapRectangle");
	widget.show();

    return app.exec();
}

