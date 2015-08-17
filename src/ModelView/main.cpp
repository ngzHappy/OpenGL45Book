/*utf8 with bom*/
#include "ModelView.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    ModelView widget;
    widget.setWindowTitle("ModelView");
	widget.show();

    return app.exec();
}

