/*utf8 with bom*/
#include "TessellatedCube.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    TessellatedCube widget;
    widget.setWindowTitle("TessellatedCube");
	widget.show();

    return app.exec();
}

