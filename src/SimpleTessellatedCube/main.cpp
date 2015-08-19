/*utf8 with bom*/
#include "SimpleTessellatedCube.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleTessellatedCube widget;
    widget.setWindowTitle("SimpleTessellatedCube");
	widget.show();

    return app.exec();
}

