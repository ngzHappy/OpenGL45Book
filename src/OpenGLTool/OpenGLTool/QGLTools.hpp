#ifndef __QGLTOOLS_H_p_p__0x00
#define __QGLTOOLS_H_p_p__0x00

//#ifndef GLEW_STATIC
//#define GLEW_STATIC
//#endif
#include <GLEWGL/glew.h>

#ifdef QT_CORE_LIB

#include <QGLWidget>
#include <QGLFormat>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <QImage>
#include <QString>
#include <cstddef>
#include <cstdint>
#include <cstdbool>
#include <ciso646>
#include <memory>


#endif

#ifdef QT_DEBUG
#include<iostream>
#include <QDebug>
#endif

struct QGLTools
{
#ifdef QT_CORE_LIB

    static inline bool QGLWidgetInitializeGlew(
            QGLWidget * const ptr
            )
    {
        ptr->makeCurrent();
        glewExperimental = GL_TRUE;
        int glewErr = glewInit();
        if( glewErr != GLEW_OK )
        {
            QMessageBox box;
            box.setText("opengl/glew init error!");
            box.exec();
            return false;
        }//
        return true;
    }

    enum
    {
        SampleSize = 8
    };

    static inline QGLFormat AutoQGLFormat(
            const int  major__=4,
            const int  minor__=5
            )
    {

        QGLFormat format(
                    QGL::DoubleBuffer|/**/
                    QGL::DepthBuffer|/**/
                    QGL::Rgba|/**/
                    QGL::StencilBuffer|/**/
                    QGL::SampleBuffers|/**/
                    QGL::AccumBuffer
                    );

        format.setVersion(major__, minor__);
        format.setProfile( QGLFormat::CoreProfile );
        format.setSampleBuffers(true);
        format.setSamples(SampleSize);
        format.setDoubleBuffer(true);
        format.setDepth(true);

        return format;
    }

#ifdef QT_DEBUG
    static inline bool CheckFormat()
    {
        GLint buf;
        glGetIntegerv(GL_SAMPLE_BUFFERS,&buf);
        qDebug()<<"GL_SAMPLE_BUFFERS "<<buf ;
        if(buf==0){return false;}
        glGetIntegerv(GL_SAMPLES,&buf);
        qDebug()<<"GL_SAMPLES "<<buf ;
        if(buf!=SampleSize){return false;}
        return true;
    }
#else
    static inline bool CheckFormat(){return true;}/**/
#endif

    static inline QImage project(const QImage & source_){
        typedef std::uint32_t image_item_type;
        const QImage source = source_.convertToFormat( QImage::Format_RGBA8888 );
        const auto size = source.size();
        if((size.width()<=0)||(size.height()<=0)){return QImage();}
        QImage ans(size,QImage::Format_RGBA8888);
        int linecount = ans.bytesPerLine()/sizeof(image_item_type);
        const auto height = size.height();
        const auto width = size.width();
        image_item_type * source__ = (image_item_type *)source.bits();
        image_item_type * ans__ = (image_item_type *)ans.scanLine(height-1);
        for(int _i = 0;_i<height;++_i){
            {
                image_item_type * s = source__;
                image_item_type * a = ans__;
                for(int _j=0;_j<width;++_j){
                    *a = *s;++a;++s;
                }
            }
            ans__-=linecount;
            source__+=linecount;
        }
        return std::move(ans);
    }

#endif
};


#endif // QGLTOOLS_H
