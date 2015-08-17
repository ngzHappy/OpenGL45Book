/*utf8 with bom*/
#include "NormalSphere.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    NormalSphere widget;
    widget.setWindowTitle("NormalSphere");
	widget.show();

    return app.exec();
}

