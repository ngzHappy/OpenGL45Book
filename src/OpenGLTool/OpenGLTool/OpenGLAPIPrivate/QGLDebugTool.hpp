#ifndef __DEBUG__TOOLS__Q__H__0x00
#define __DEBUG__TOOLS__Q__H__0x00

#ifdef QT_CORE_LIB



#include "BaseType.hpp"
#include <QGLWidget>
#include <QDebug>
#include <iostream>
#include <string>


struct QGLDebugTool
{
    /*   */


    //----------------------------
    struct SimpleCallBack
    {
        template<typename T>
        struct Print
        {
            static void print(const std::string & name,T value)
            {

                qDebug()<<QString( name.c_str() )\
                     << hex<<value<<","
                     << dec<<value ;
            }
        };

		static void GLAPIENTRY callback(
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* /*userParam*/
                )
        {
            Print<GLenum>::print("source:",source);
            Print<GLenum>::print("type:",type);
            Print<GLuint>::print("id:",id);
            Print<GLenum>::print("severity:",severity);
            std::string mes(message,length);
            qDebug()<<"message: "<<QString(mes.c_str()) ;
        }

    };
    //----------------------------
    static void setSimpleCallbackFunction(bool e=true)
    {
        if(e==false){return;}

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageControl(GL_DONT_CARE,
                              GL_DONT_CARE,
                              GL_DONT_CARE,
                              0,
                              0,
                              true);
        glDebugMessageCallback(
                    &(SimpleCallBack::callback),
                    0);

        GLint v = 0x01;
        glGetIntegerv( GL_CONTEXT_FLAGS, &v );
        if(GL_CONTEXT_FLAG_DEBUG_BIT&v)
        {
            std::cout<<"simple debug function set!"<<std::endl;
        }
        else
        {
            qDebug()<<"debug function set failed!";
        }
    }
    //----------------------------
    static void test()
    {
        glDebugMessageInsert(
                    GL_DEBUG_SOURCE_APPLICATION,
                    GL_DEBUG_TYPE_ERROR,
                    10000 ,
                    GL_DEBUG_SEVERITY_HIGH,
                    -1,
                    "Warning: My Application Generated a test Warning!");
    }

};

#endif
#endif
