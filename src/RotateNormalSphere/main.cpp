﻿/*utf8 with bom*/
#include "RotateNormalSphere.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    RotateNormalSphere widget;
    widget.setWindowTitle("RotateNormalSphere");
	widget.show();

    return app.exec();
}

