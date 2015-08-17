/*utf8 with bom*/
#include "MainWindow.hpp"
#include <QApplication>
#include <QTextCodec>
#include "SimpleImageShow.hpp"
int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    MainWindow mainWindow;
    mainWindow.setWindowTitle("SimpleImageShow");
    mainWindow.show();

    return app.exec();
}

