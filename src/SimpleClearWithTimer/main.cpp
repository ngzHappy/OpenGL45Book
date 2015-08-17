/*utf8 with bom*/
#include "SimpleClearWithTimer.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleClearWithTimer widget;
    widget.setWindowTitle("SimpleClearWithTimer");
	widget.show();

    return app.exec();
}

