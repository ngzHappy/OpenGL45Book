/*utf8 with bom*/
#include "SingleTriangle.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SingleTriangle widget;
    widget.setWindowTitle("SingleTriangle");
	widget.show();

    return app.exec();
}

