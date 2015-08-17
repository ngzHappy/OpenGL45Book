
#ifndef __GLOBAL__ogl__0x00__FUNCITION______OPENGL__API__PRIVATE__0x00
#define __GLOBAL__ogl__0x00__FUNCITION______OPENGL__API__PRIVATE__0x00


#include "BaseType.hpp"

namespace gl {

/*
void glClear(	GLbitfield mask);
GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, and GL_STENCIL_BUFFER_BIT.
*/
static inline void clear( Bitfield mask ){
glClear(mask);
}

template<Bitfield Clears0>void clear(){
    glClear(Clears0);
}
template<Bitfield Clears0,Bitfield Clears1>
void clear(){
    glClear(Clears0|Clears1);
}
template<Bitfield Clears0,Bitfield Clears1,Bitfield Clears2>
void clear(){
    glClear(Clears0|Clears1|Clears2);
}
static inline void clearAll(){
    clear<GL_COLOR_BUFFER_BIT,GL_DEPTH_BUFFER_BIT,GL_STENCIL_BUFFER_BIT>();
}
static inline void clearColorAndDepth(){
    clear<GL_COLOR_BUFFER_BIT,GL_DEPTH_BUFFER_BIT >();
}

/*

void glViewport(	GLint x,
    GLint y,
    GLsizei width,
    GLsizei height);
*/
static inline void viewport(
        Integer x, Integer y,
        SizeInteger width,SizeInteger height
        ){
    glViewport(x,y,width,height);
}

/*depth********************************************/
inline void enableDepthTest() {glEnable(GL_DEPTH_TEST);}
inline void disableDepthTest() { glDisable(GL_DEPTH_TEST); }
enum class  DepthFunction:GLenum {
	NEVER=GL_NEVER,
	LESS=GL_LESS,
	EQUAL=GL_EQUAL,
	LEQUAL=GL_LEQUAL,
	GREATER=GL_GREATER,
	NOTEQUAL=GL_NOTEQUAL,
	GEQUAL=GL_GEQUAL,
	ALWAYS=GL_ALWAYS,
};
inline void depthFunction(DepthFunction func = DepthFunction::LEQUAL ) {
	glDepthFunc(GLenum(func));
}
inline void depthMask(bool flag = false) {glDepthMask(flag);}
/**************************************************/

}//~namespace gl


#endif
