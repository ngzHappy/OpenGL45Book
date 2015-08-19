/*utf8 with bom*/
#include "TessellatedLine.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    TessellatedLine widget;
    widget.setWindowTitle("TessellatedLine");
	widget.show();

    return app.exec();
}

