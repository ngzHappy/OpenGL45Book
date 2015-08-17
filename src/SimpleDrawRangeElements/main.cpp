/*utf8 with bom*/
#include "SimpleDrawRangeElements.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawRangeElements widget;
    widget.setWindowTitle("SimpleDrawRangeElements");
	widget.show();

    return app.exec();
}

