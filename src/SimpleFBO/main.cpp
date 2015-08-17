﻿/*utf8 with bom*/
#include "SimpleFBO.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleFBO widget;
    widget.setWindowTitle("SimpleFBO");
	widget.show();

    return app.exec();
}

