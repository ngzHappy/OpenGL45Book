/*utf8 with bom*/
#include "SingleTriangleWithTimer.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SingleTriangleWithTimer widget;
    widget.setWindowTitle("SingleTriangleWithTimer");
	widget.show();

    return app.exec();
}

