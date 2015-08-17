/*utf8 with bom*/
#include "SimpleDrawArrays.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawArrays widget;
    widget.setWindowTitle("SimpleDrawArrays");
	widget.show();

    return app.exec();
}

