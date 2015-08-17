
#include "SimpleBuffer.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);
    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );
    SimpleBuffer widget;
	widget.show();

    return app.exec();
}

