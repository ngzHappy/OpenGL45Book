/*utf8 with bom*/
#include "SimpleDrawElementsInstancedBaseInstance.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawElementsInstancedBaseInstance widget;
    widget.setWindowTitle("SimpleDrawElementsInstancedBaseInstance");
	widget.show();

    return app.exec();
}

