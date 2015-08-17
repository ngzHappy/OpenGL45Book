/*utf8 with bom*/
#include "SingleCube.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char ** argv  ){
	QApplication app(argc,argv);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SingleCube widget;
    widget.setWindowTitle("SingleCube");
	widget.show();

    return app.exec();
}

