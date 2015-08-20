/*utf8 with bom*/
#include "SimpleSamplerWrap.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleSamplerWrap widget;
    widget.setWindowTitle("SimpleSamplerWrap");
	widget.show();

    return app.exec();
}

