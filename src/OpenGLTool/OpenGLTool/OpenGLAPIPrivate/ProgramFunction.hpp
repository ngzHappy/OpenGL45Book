
#ifndef __functionPROGRAMTYPE____OPENGL__API__PRIVATE__0x00
#define __functionPROGRAMTYPE____OPENGL__API__PRIVATE__0x00

#include "ProgramType.hpp"

namespace gl {//namespace gl

/*
GLuint glCreateProgram(	void);
创建一个程序
*/
inline Program createProgram(){
    return Program(glCreateProgram());
}


/*
void glDeleteProgram( GLuint program);
删除程序
*/
inline void deleteProgram(Program program){
    glDeleteProgram( UnsignedInteger(program) );
}


/*
void glLinkProgram( GLuint program);
连接程序
*/
inline void linkProgram(Program program){
    glLinkProgram( UnsignedInteger(program) );
}


/*
void glUseProgram(	GLuint program);
使用程序
*/
inline void useProgram(Program program){
    glUseProgram( UnsignedInteger(program) );
}


}//~namespace gl


/* 
easy use function 
易用API接口
*/
#include "PrivateComputeSourceLoader.hpp"

#include "PrivateVFSourceLoader.hpp"
#include "PrivateTCTES.hpp"
#include "PrivateTES.hpp"

#include "PrivateVGFSourceLoader.hpp"
#include "PrivateTCTEGS.hpp"
#include "PrivateTEGS.hpp"



#endif

