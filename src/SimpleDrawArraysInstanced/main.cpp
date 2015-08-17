/*utf8 with bom*/
#include "SimpleDrawArraysInstanced.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawArraysInstanced widget;
    widget.setWindowTitle("SimpleDrawArraysInstanced");
	widget.show();

    return app.exec();
}

