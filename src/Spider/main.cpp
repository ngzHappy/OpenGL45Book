/*utf8 with bom*/
#include "Spider.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    Spider widget;
    widget.setWindowTitle("Spider");
	widget.show();

    return app.exec();
}

