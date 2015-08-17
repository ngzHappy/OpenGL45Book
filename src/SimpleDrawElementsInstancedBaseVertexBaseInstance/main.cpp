/*utf8 with bom*/
#include "SimpleDrawElementsInstancedBaseVertexBaseInstance.hpp"
#include <OpenGLTool/QGLApplication.hpp>
#include <QTextCodec>

int main(int argc,char ** argv  ){
    QApplication app(argc,argv);
    QGLApplication glapp(&app);

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );

    SimpleDrawElementsInstancedBaseVertexBaseInstance widget;
    widget.setWindowTitle("SimpleDrawElementsInstancedBaseVertexBaseInstance");
	widget.show();

    return app.exec();
}

