/*utf8 with bom*/

#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>
#include "MainWindow.hpp"

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

	MainWindow widget;
    widget.setWindowTitle("ModelView");
	widget.show();

    return app.exec();
}

