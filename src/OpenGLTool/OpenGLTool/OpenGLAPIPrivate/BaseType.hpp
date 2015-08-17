
#ifndef __BASETYPE____OPENGL__API__PRIVATE__0x00
#define __BASETYPE____OPENGL__API__PRIVATE__0x00

#include <cstdbool>
#include "OpenGLBase.hpp"

namespace gl {

/*
 * 基本OpenGL数据类型
*/

typedef GLenum       Enum;
typedef GLbitfield   Bitfield;
typedef GLuint       UnsignedInteger;
typedef GLint        Integer;
typedef GLsizei      SizeInteger;
#ifdef __cplusplus
typedef bool         Boolean; 
#else
typedef GLboolean    Boolean;
#endif
typedef GLbyte       Byte;
typedef GLshort      Short;
typedef GLubyte      UnsignedByte;
typedef GLushort     UnsignedShort;
typedef GLulong      UnsignedLong;
typedef GLfloat      Float;
typedef GLclampf     ClampFloat;
typedef GLdouble     Double;
typedef GLclampd     ClampDouble;
typedef GLvoid       Void;
typedef GLint64      Integer64;
typedef GLuint64     UnsignedInteger64;
typedef GLsync       Sync;
typedef GLchar       Char;
typedef GLintptr     IntegerPtr;
typedef GLsizeiptr   SizeIntegerPtr;

enum class SizeIntegerValue :GLint {
One=1,Two=2,Three=3,Four=4,
};

}

#include "BaseType.hxx"


#endif



