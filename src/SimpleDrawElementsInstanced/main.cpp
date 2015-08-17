/*utf8 with bom*/
#include "SimpleDrawElementsInstanced.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawElementsInstanced widget;
    widget.setWindowTitle("SimpleDrawElementsInstanced");
	widget.show();

    return app.exec();
}

