/*utf8 with bom*/
#include "SimpleGeometryViewportIndex.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleGeometryViewportIndex widget;
    widget.setWindowTitle("SimpleGeometryViewportIndex");
	widget.show();

    return app.exec();
}

