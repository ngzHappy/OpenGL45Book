/*utf8 with bom*/
#include "SimpleDrawElements.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawElements widget;
    widget.setWindowTitle("SimpleDrawElements");
	widget.show();

    return app.exec();
}

