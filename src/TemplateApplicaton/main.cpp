#include "TemplateApplication.hpp"
#include <QDebug>
#include <QTextCodec>

int main(int argc ,char ** argv){
    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_NAME) );
    if(argc<2){
		qDebug() << " error input! ";
		return -1;
	}

    if(argc==2){
        return getOpenGLApplicaton(
                QString::fromLocal8Bit( argv[1] ),
                QString::fromLocal8Bit( argv[1] )
                    );
    }

    return getOpenGLApplicaton(
            QString::fromLocal8Bit( argv[1] ),
            QString::fromLocal8Bit( argv[2] )
                );

}
