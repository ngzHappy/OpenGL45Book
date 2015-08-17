/*utf8 with bom*/
#include "SimpleTextureArray.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleTextureArray widget;
    widget.setWindowTitle("SimpleTextureArray");
	widget.show();

    return app.exec();
}

