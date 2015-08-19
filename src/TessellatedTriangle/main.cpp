/*utf8 with bom*/
#include "TessellatedTriangle.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    TessellatedTriangle widget;
    widget.setWindowTitle("TessellatedTriangle");
	widget.show();

    return app.exec();
}

