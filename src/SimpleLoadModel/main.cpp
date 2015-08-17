/*utf8 with bom*/

#include "SimpleLoadModel.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char ** argv) {
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_NAME));


    SimpleLoadModel widget;
    widget.setWindowTitle("SimpleLoadModel");
	widget.show();

    return app.exec();
}

