/*utf8 with bom*/
#include "SimpleDrawArraysInstancedBaseInstance.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawArraysInstancedBaseInstance widget;
    widget.setWindowTitle("SimpleDrawArraysInstancedBaseInstance");
	widget.show();

    return app.exec();
}

