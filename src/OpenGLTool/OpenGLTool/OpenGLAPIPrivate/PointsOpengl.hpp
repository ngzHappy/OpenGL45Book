#ifndef __points__opengl______OPENGL__API__PRIVATE__0x00
#define __points__opengl______OPENGL__API__PRIVATE__0x00

#include "BaseType.hpp"
namespace gl {
//void glPointSize(	GLfloat size);
//void glPointParameterf(	GLenum pname,GLfloat param);
//glenable GL_PROGRAM_POINT_SIZE

inline void pointSize(Float size){
    glPointSize(size);
}

//GL_UPPER_LEFT
//GL_LOWER_LEFT
enum PointCoordOrigin : GLint{
	UPPER_LEFT=GL_UPPER_LEFT,
	LOWER_LEFT=GL_LOWER_LEFT
};
inline void pointCoordOrigin(PointCoordOrigin p) {
	glPointParameteri(
		GL_POINT_SPRITE_COORD_ORIGIN,
		GLint(p)
		);
}

}


#endif

