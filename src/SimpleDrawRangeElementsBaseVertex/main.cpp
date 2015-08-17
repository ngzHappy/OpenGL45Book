/*utf8 with bom*/
#include "SimpleDrawRangeElementsBaseVertex.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawRangeElementsBaseVertex widget;
    widget.setWindowTitle("SimpleDrawRangeElementsBaseVertex");
	widget.show();

    return app.exec();
}

