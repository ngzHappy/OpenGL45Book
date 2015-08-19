/*utf8 with bom*/
#include "SimpleTessellatedTriangle.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleTessellatedTriangle widget;
    widget.setWindowTitle("SimpleTessellatedTriangle");
	widget.show();

    return app.exec();
}

