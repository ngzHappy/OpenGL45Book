/*utf8 with bom*/
#include "SinglePoint.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SinglePoint widget;
    widget.setWindowTitle("SinglePoint");
	widget.show();

    return app.exec();
}

