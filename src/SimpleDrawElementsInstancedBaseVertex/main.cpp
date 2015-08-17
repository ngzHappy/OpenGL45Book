/*utf8 with bom*/
#include "SimpleDrawElementsInstancedBaseVertex.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawElementsInstancedBaseVertex widget;
    widget.setWindowTitle("SimpleDrawElementsInstancedBaseVertex");
	widget.show();

    return app.exec();
}

