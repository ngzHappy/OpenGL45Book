#include "QInitializeDebugContext.hpp"
#include <QGLWidget>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QDebug>




namespace  {

static void initialization( QGLWidget * glWidget ){
    if(0==glWidget){return;}
    QOpenGLContext * ch = glWidget->context()->contextHandle() ;
    if(ch){
        QSurfaceFormat format =ch->format() ;
        format.setOption( QSurfaceFormat::DebugContext );
        ch->setFormat(format);
        if(ch->create()){return;}
        else{
            qDebug()<<"error create opengl debug";
        }
    }else{
        qDebug()<<"error init opengl debug";
    }
}

}


void qInitializeDebugContext(QGLWidget *glWidget){
    initialization(glWidget);
}



