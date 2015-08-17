
#include "SimpleClear.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleClear widget;
    widget.setWindowTitle("SimpleClear");
	widget.show();

    return app.exec();
}

