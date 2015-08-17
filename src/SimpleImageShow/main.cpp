/*utf8 with bom*/
#include <OpenGLTool/QGLApplication.hpp>
#include "MainWindow.hpp"
#include <QApplication>
#include <QTextCodec>
#include "SimpleImageShow.hpp"
int main(int argc,char ** argv  ){
	QApplication app(argc,argv);
    QGLApplication gapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    MainWindow mainWindow;
    mainWindow.setWindowTitle("SimpleImageShow");
    mainWindow.show();

    return app.exec();
}

