/*utf8 with bom*/
#include "SimpleDrawElementsBaseVertex.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawElementsBaseVertex widget;
    widget.setWindowTitle("SimpleDrawElementsBaseVertex");
	widget.show();

    return app.exec();
}

