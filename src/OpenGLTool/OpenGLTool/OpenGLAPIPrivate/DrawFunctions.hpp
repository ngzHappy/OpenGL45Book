#ifndef __functiondraw____OPENGL__API__PRIVATE__0x00
#define __functiondraw____OPENGL__API__PRIVATE__0x00
/*
 * glDrawArrays
 * glDrawElements GL_ELEMENT_ARRAY_BUFFER
 * glDrawElementsBaseVertex
 * glMultiDrawArrays
 * glDrawArraysIndirect glVertexAttribDivisor
*/
#include "GLUnamedObject.hpp"
#include "BaseType.hpp"
namespace gl {

	enum class DrawArraysMode :GLenum {
		POINTS = GL_POINTS,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP,
		LINES = GL_LINES,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY = GL_LINES_ADJACENCY,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		PATCHES = GL_PATCHES
};
/*
void glDrawArrays(	GLenum mode,
    GLint first,
    GLsizei count);
mode:GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP,
GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY,
GL_TRIANGLES_ADJACENCY and GL_PATCHES
*/
inline void drawArrays( DrawArraysMode mode , Integer first ,SizeInteger count ){
    glDrawArrays((GLenum)mode,first,count);
}

enum class DrawElementsMode :GLenum{
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
enum class DrawElementsType :GLenum{
	UNSIGNED_BYTE=GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT=GL_UNSIGNED_SHORT,
	UNSIGNED_INT=GL_UNSIGNED_INT
};
/*
void glDrawElements(	GLenum mode,
GLsizei count,
GLenum type,
const GLvoid * indices);

type GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
*/
inline void drawElements(
	DrawElementsMode mode,
	SizeInteger count,
	DrawElementsType type,
	const Void * indices = 0/* 偏置 */
	){
	glDrawElements((GLenum)mode, count, (GLenum)type, indices);
}

enum class DrawArraysInstancedMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
/*
GL_POINTS, 
GL_LINE_STRIP, 
GL_LINE_LOOP, 
GL_LINES, 
GL_TRIANGLE_STRIP, 
GL_TRIANGLE_FAN, 
GL_TRIANGLES 
GL_LINES_ADJACENCY, 
GL_LINE_STRIP_ADJACENCY, 
GL_TRIANGLES_ADJACENCY, 
GL_TRIANGLE_STRIP_ADJACENCY  
GL_PATCHES  
*/
inline void drawArraysInstanced(
	DrawArraysInstancedMode mode,
	Integer first,
	GLsizei count,
	GLsizei primcount) {
	glDrawArraysInstanced(GLenum(mode),first,count,primcount);
}

/*
Specific vertex attributes may be classified as instanced through the use of 
glVertexAttribDivisor. Instanced vertex attributes supply per-instance vertex data 
to the vertex shader. The index of the vertex fetched from the enabled instanced 
vertex attribute arrays is calculated as: [gl_InstanceID/divisor]+baseInstance. 
Note that baseinstance does not affect the shader-visible value of gl_InstanceID.
*/
enum class DrawArraysInstancedBaseInstanceMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
inline void drawArraysInstancedBaseInstance(
	DrawArraysInstancedBaseInstanceMode mode,
	GLint first,
	GLsizei count,
	GLsizei primcount,
	GLuint baseinstance =0) {
	glDrawArraysInstancedBaseInstance(
		GLenum(mode),first,count,primcount, baseinstance
		);
}

enum class DrawElementsBaseVertexMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
enum class DrawElementsBaseVertexType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};

inline void drawElementsBaseVertex(
	DrawElementsBaseVertexMode mode,
	GLsizei count,
	DrawElementsBaseVertexType 
	type= DrawElementsBaseVertexType::UNSIGNED_SHORT,
	GLvoid * indices =0  ,
	GLint basevertex = 0) {
	glDrawElementsBaseVertex(
		(GLenum)mode,
		count, 
		(GLenum)type, 
		indices,
		basevertex
		);
}

enum class DrawElementsInstancedType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
enum class DrawElementsInstancedMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
inline void drawElementsInstanced(
	DrawElementsInstancedMode mode,
	GLsizei count                  ,
	DrawElementsInstancedType type ,
	const void * indices           =0,
	GLsizei primcount              =0) {
	glDrawElementsInstanced(
		GLenum(mode),count,
		GLenum(type),indices,
		primcount
		);
}


enum class DrawElementsInstancedBaseInstanceType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
enum class DrawElementsInstancedBaseInstanceMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
inline void drawElementsInstancedBaseInstance(
	DrawElementsInstancedBaseInstanceMode mode ,
	GLsizei count                               ,
	DrawElementsInstancedBaseInstanceType type  ,
	const void * indices   =0,
	GLsizei primcount      =1,
	GLuint  baseinstance   =0) {
	glDrawElementsInstancedBaseInstance(
		GLenum(mode),
		GLsizei(count),
		GLenum(type),
		indices,
		primcount,
		baseinstance
		);
}

enum class DrawElementsInstancedBaseVertexType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
enum class DrawElementsInstancedBaseVertexMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
inline void drawElementsInstancedBaseVertex(
	DrawElementsInstancedBaseVertexMode mode,
	GLsizei count,
	DrawElementsInstancedBaseVertexType type,
	GLvoid *indices,
	GLsizei primcount,
	GLint basevertex) {
	glDrawElementsInstancedBaseVertex(
		GLenum(mode),
		GLsizei(count),
		GLenum(type),
		(GLvoid*)(indices),
		GLsizei(primcount),
		GLint(basevertex));
}


enum class DrawElementsInstancedBaseVertexBaseInstanceType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
enum class DrawElementsInstancedBaseVertexBaseInstanceMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
inline void drawElementsInstancedBaseVertexBaseInstance(
	DrawElementsInstancedBaseVertexBaseInstanceMode mode,
	GLsizei count,
	DrawElementsInstancedBaseVertexBaseInstanceType type,
	GLvoid *indices,
	GLsizei primcount,
	GLint basevertex,
	GLuint baseinstance) {
	glDrawElementsInstancedBaseVertexBaseInstance(
		GLenum(mode),
		GLsizei(count),
		GLenum(type),
		(GLvoid*)(indices),
		GLsizei(primcount),
		GLint(basevertex),
		GLuint(baseinstance));
}

enum class DrawRangeElementsMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
enum class DrawRangeElementsType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
inline void drawRangeElements(
	DrawRangeElementsMode mode,
	GLuint start,
	GLuint end,
	GLsizei count,
	DrawRangeElementsType type,
	const GLvoid * indices) {
glDrawRangeElements(GLenum(mode),
		start,
		end,
		count,
		GLenum(type),
	    indices);
}

enum class DrawRangeElementsBaseVertexMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
enum class DrawRangeElementsBaseVertexType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
inline void drawRangeElementsBaseVertex(
	DrawRangeElementsBaseVertexMode mode,
	GLuint start,
	GLuint end,
	GLsizei count,
	DrawRangeElementsBaseVertexType type,
	GLvoid *indices,
	GLint basevertex) {
glDrawRangeElementsBaseVertex(
	GLenum(mode),
	start,end,count,
	GLenum(type),indices,basevertex
);
}


enum class MultiDrawArraysMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
inline void multiDrawArrays(
	MultiDrawArraysMode  mode     ,
	const GLint *        first    ,
	const GLsizei *      count    ,
	GLsizei              drawcount) {
	glMultiDrawArrays(GLenum(mode),first,count,drawcount);
}

enum class MultiDrawElementsMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
enum class MultiDrawElementsType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};
inline void multiDrawElements(
	MultiDrawElementsMode mode,
	const GLsizei * count,
	MultiDrawElementsType type,
	const GLvoid * const * indices,
	GLsizei drawcount) {
	glMultiDrawElements(
		GLenum(mode),
		count,
		GLenum(type),
		indices,
		drawcount);
}

enum class MultiDrawElementsBaseVertexMode :GLenum {
	POINTS = GL_POINTS,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	LINES = GL_LINES,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	PATCHES = GL_PATCHES,
};
enum class MultiDrawElementsBaseVertexType :GLenum {
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT
};

inline  void multiDrawElementsBaseVertex(
	MultiDrawElementsBaseVertexMode mode,
	const GLsizei *count,
	MultiDrawElementsBaseVertexType type,
	const GLvoid * const *indices,
	GLsizei drawcount,
	const GLint *basevertex) {
	glMultiDrawElementsBaseVertex(
		GLenum(mode),
		count,
		GLenum(type),
		indices,
		drawcount,
		basevertex);
}

namespace  MultiDrawElementsBaseVertex {
	typedef MultiDrawElementsBaseVertexType Type;
	typedef MultiDrawElementsBaseVertexMode Mode;

    class Pack : public UnNamedDrawObject{
	public:
		Mode mode;
		const GLsizei *count;
		Type type;
		const GLvoid * const *indices;
		GLsizei drawcount;
		const GLint *basevertex;
		Pack():mode(Mode::LINES),count(0),type(Type::UNSIGNED_INT),
		indices(0),drawcount(0),basevertex(0){}
		Pack(Mode mode_,const GLsizei *count_,Type type_,
		const GLvoid * const *indices_,GLsizei drawcount_,
		const GLint *basevertex_) :mode(mode_), count(count_), 
			type(type_),indices(indices_), 
			drawcount(drawcount_), basevertex(basevertex_) {}
	};

	inline void draw(const Pack & pack) {
		multiDrawElementsBaseVertex(
			pack.mode,pack.count,pack.type,
			pack.indices,pack.drawcount,pack.basevertex
			);
	}

}

namespace MultiDrawElements {
	typedef MultiDrawElementsType Type;
	typedef MultiDrawElementsMode Mode;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode;
		const GLsizei * count;
		Type type;
		const GLvoid * const * indices;
		GLsizei drawcount;
		Pack() :mode(Mode::LINES),count(0),
			type(Type::UNSIGNED_INT),indices(0),drawcount(0){}
		Pack(Mode mode_, const GLsizei * count_,
			Type type_, const GLvoid * const * indices_,
			GLsizei drawcount_
			) :mode(mode_),count(count_),type(type_),
			indices(indices_),drawcount(drawcount_){}
	};
	inline void draw(const Pack & pack) {
		multiDrawElements(pack.mode,pack.count,
			pack.type,pack.indices,pack.drawcount);
	}
}

namespace MultiDrawArrays {
	typedef MultiDrawArraysMode Mode;
    class Pack : public UnNamedDrawObject{
	public:
		Mode            mode     ;
		const GLint *   first    ;
		const GLsizei * count    ;
		GLsizei         drawcount;
		Pack():mode(Mode::LINES),first(0),count(0),drawcount(0) {}
		Pack(Mode            mode_,
			 const GLint *   first_,
			 const GLsizei * count_,
			 GLsizei         drawcount_
			) :mode(mode_),first(first_),
			count(count_),drawcount(drawcount_){}
	};
	inline void draw(const Pack & pack) {
		multiDrawArrays(pack.mode,pack.first,pack.count,pack.drawcount);
	}
}

namespace DrawArrays {
	typedef DrawArraysMode Mode;
    class Pack : public UnNamedDrawObject {
	public:
		Mode mode;
		Integer first;
		SizeInteger count;
		Pack() :mode(Mode::LINES),first(0),count(0){}
		Pack(Mode mode_, Integer first_, SizeInteger count_) :
			mode(mode_), first(first_), count(count_) {}
	};
	inline void draw(const Pack & pack) {
		drawArrays(pack.mode, pack.first, pack.count);
	}
}

namespace DrawElements {	
	typedef DrawElementsMode Mode;
	typedef DrawElementsType Type;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode;
		SizeInteger count;
		Type type;
		Void * indices;
		Pack() :mode(Mode::LINES),count(0),
			type(Type::UNSIGNED_INT),indices(0){}
		Pack(Mode mode_, SizeInteger count_,
			Type type_, Void * indices_
			) :mode(mode_),count(count_),
			type(type_),indices(indices_){}
	};
	inline void draw(const Pack & pack ) {
		drawElements(pack.mode,pack.count,pack.type,pack.indices);
	}
}

namespace DrawArraysInstanced {

	typedef DrawArraysInstancedMode Mode;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode;
		Integer first;
		GLsizei count;
		GLsizei primcount;
		Pack() :mode(Mode::LINES),first(0),count(0),primcount(0){}
		Pack(Mode mode_, Integer first_,
			GLsizei count_, GLsizei primcount_) :
			mode(mode_),first(first_),
			count(count_),primcount(primcount_){}
	};
	inline void draw(const Pack & pack) {
		drawArraysInstanced(
			pack.mode,
			pack.first,
			pack.count,
			pack.primcount
			);
	}
}

namespace DrawArraysInstancedBaseInstance {
	 
	typedef DrawArraysInstancedBaseInstanceMode Mode;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode         ;
		GLint first         ;
		GLsizei count       ;
		GLsizei primcount   ;
		GLuint baseinstance	;
		Pack() :mode(Mode::LINES),
			first(0),count(0),
			primcount(0),baseinstance(0){}
		Pack( Mode mode_,
			GLint first_,
			GLsizei count_,
			GLsizei primcount_,
			GLuint baseinstance_) :mode(mode_),
			first(first_), count(count_),
			primcount(primcount_), baseinstance(baseinstance_) {}
	};
	inline void draw(const Pack & pack) {
		drawArraysInstancedBaseInstance(
			pack.mode,
			pack.first,
			pack.count,
			pack.primcount,
			pack.baseinstance
			);
	}
}

namespace DrawElementsBaseVertex {

	typedef DrawElementsBaseVertexMode Mode;
	typedef DrawElementsBaseVertexType Type;
    class Pack : public UnNamedDrawObject{
	public:
		DrawElementsBaseVertexMode mode;
		GLsizei count                    ;
		Type type                        ;
		GLvoid * indices                 ;
		GLint basevertex                 ;
		Pack() :mode(Mode::LINES),count(0),type(Type::UNSIGNED_INT),
			indices(0),basevertex(0){}
		Pack(
			Mode mode_, GLsizei count_,Type type_, 
			GLvoid * indices_,GLint basevertex_) :mode(mode_),
			count(count_),
			type(type_),indices(indices_),
			basevertex(basevertex_){}
	};
	inline void draw(const Pack & pack) {
		drawElementsBaseVertex(pack.mode,
			pack.count,
			pack.type,
			pack.indices,
			pack.basevertex);
	}
}

namespace DrawElementsInstanced {
	
	typedef DrawElementsInstancedMode Mode;
	typedef DrawElementsInstancedType Type;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode  ;
		GLsizei count  ;
		Type type  ;
		const void * indices  ;
		GLsizei primcount  ;
		Pack() :mode(Mode::LINES), count(0),
			type(Type::UNSIGNED_INT),indices(0),
			primcount(0){}
		Pack(
			Mode mode_ ,
			GLsizei count_ ,
			Type type_ ,
			const void * indices_ = 0,
			GLsizei primcount_ = 0
			):mode(mode_),count(count_),type(type_),
			indices(indices_),primcount(primcount_){}
	};
	void draw(const Pack & pack) {
		drawElementsInstanced(pack.mode,pack.count,pack.type,
			pack.indices,pack.primcount);
	}
}

namespace DrawElementsInstancedBaseInstance {
	 
	typedef DrawElementsInstancedBaseInstanceMode Mode;
	typedef DrawElementsInstancedBaseInstanceType Type;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode                                 ;
		GLsizei count                             ;
		Type type                                 ;
		const void * indices                      ;
		GLsizei primcount                         ;
		GLuint  baseinstance                      ;
		Pack() :mode(Mode::LINES),count(0),type(Type::UNSIGNED_INT),
		indices(0),primcount(0),baseinstance(0){}
		Pack(Mode mode_,SizeInteger count_,Type type_,
			const void * indices_,SizeInteger primcount_,
			UnsignedInteger baseinstance_
			) :mode(mode_),count(count_),type(type_),
			indices(indices_),primcount(primcount_),
			baseinstance(baseinstance_){}
	};
	inline void draw(const Pack & pack) {
		drawElementsInstancedBaseInstance(
			pack.mode,pack.count,pack.type,
			pack.indices,pack.primcount,pack.baseinstance
			);
	}
}

namespace DrawElementsInstancedBaseVertex {
	 
	typedef DrawElementsInstancedBaseVertexMode Mode;
	typedef DrawElementsInstancedBaseVertexType Type;
    class Pack: public UnNamedDrawObject {
	public:
		Mode mode         ;
		GLsizei count     ;
		Type type         ;
		GLvoid *indices   ;
		GLsizei primcount ;
		GLint basevertex  ;
		Pack():mode(Mode::LINES ),count(0),type(Type::UNSIGNED_INT),
			primcount(0),basevertex(0){}
		Pack(Mode mode_,GLsizei count_,Type type_,
			GLvoid *indices_,GLsizei primcount_,GLint basevertex_
			) :mode(mode_),count(count_),type(type_),
			indices(indices_),primcount(primcount_),
			basevertex(basevertex_){}
	};
	inline void draw(const Pack & pack) {
		drawElementsInstancedBaseVertex(pack.mode,pack.count,pack.type,
			pack.indices,pack.primcount,pack.basevertex);
	}
}

namespace DrawElementsInstancedBaseVertexBaseInstance {
	 
	typedef DrawElementsInstancedBaseVertexBaseInstanceMode Mode;
	typedef DrawElementsInstancedBaseVertexBaseInstanceType Type;
    class Pack : public UnNamedDrawObject{
	public:
		Mode       mode         ;
		GLsizei    count        ;
		Type       type         ;
		GLvoid *   indices      ;
		GLsizei    primcount    ;
		GLint      basevertex   ;
		GLuint     baseinstance ;
		Pack() :mode(Mode::LINES),count(0),type(Type::UNSIGNED_INT),indices(0),
			primcount(0),basevertex(0),baseinstance(0){}
		Pack(Mode mode_,SizeInteger count_,
			Type type_, void * indices_,SizeInteger primcount_,
			GLint basevertex_, GLuint baseinstance_) :
			mode(mode_), count(count_), type(type_), indices(indices_),
			primcount(primcount_), basevertex(basevertex_), 
			baseinstance(baseinstance_) {}
	};
	inline void draw(const Pack & pack) {
		drawElementsInstancedBaseVertexBaseInstance(
			pack.mode,pack.count,pack.type,pack.indices,
			pack.primcount,pack.basevertex,pack.baseinstance
			);
	}
}

namespace DrawRangeElements {
	 
	typedef DrawRangeElementsMode Mode;
	typedef DrawRangeElementsType Type;
    class Pack : public UnNamedDrawObject{
	public:
		Mode mode;
		GLuint start;
		GLuint end;
		GLsizei count;
		Type type;
		const GLvoid * indices;
		Pack() :mode(Mode::LINES),start(0),end(0),count(0),
		type(Type::UNSIGNED_INT),indices(0){}
		Pack(Mode mode_, GLuint start_, 
			GLuint end_,GLsizei count_, 
			Type type_, const GLvoid * indices_) :mode(mode_), start(start_), 
			end(end_), count(count_),
			type(type_), indices(indices_) {}
	};
	inline void draw(const Pack & pack) {
		drawRangeElements(pack.mode,pack.start,pack.end,
			pack.count,pack.type,pack.indices);
	}
}

namespace DrawRangeElementsBaseVertex {
	 
	typedef DrawRangeElementsBaseVertexType Type;
	typedef DrawRangeElementsBaseVertexMode Mode;

    class Pack : public UnNamedDrawObject{
	public:
		Mode mode;
		GLuint start;
		GLuint end;
		GLsizei count;
		Type type;
		GLvoid *indices;
		GLint basevertex;
		Pack() :mode(Mode::LINES),start(0),end(0),count(0),
		type(Type::UNSIGNED_INT),indices(0),basevertex(0){}
		Pack(Mode mode_,GLuint start_,GLuint end_,
		GLsizei count_,Type type_,GLvoid *indices_,
		GLint basevertex_
			) :mode(mode_), start(start_), end(end_), count(count_),
			type(type_), indices(indices_), basevertex(basevertex_) {}
	};
	inline void draw(const Pack & pack) {
		drawRangeElementsBaseVertex(
			pack.mode,pack.start,pack.end,pack.count,
			pack.type,pack.indices,pack.basevertex
			);
	}
}

inline void draw(const gl::DrawArrays::Pack & pack) {
	gl::DrawArrays::draw(pack);
}
inline void draw(const gl::DrawElements::Pack & pack) {
	gl::DrawElements::draw(pack);
}
inline void draw(const gl::DrawArraysInstanced::Pack & pack) {
	gl::DrawArraysInstanced::draw(pack);
}
inline void draw(const gl::DrawArraysInstancedBaseInstance::Pack & pack) {
	gl::DrawArraysInstancedBaseInstance::draw(pack);
}
inline void draw(const gl::DrawElementsBaseVertex::Pack & pack) {
	gl::DrawElementsBaseVertex::draw(pack);
}
inline void draw(const gl::DrawElementsInstanced::Pack & pack) {
	gl::DrawElementsInstanced::draw(pack);
}
inline void draw(const gl::DrawElementsInstancedBaseInstance::Pack & pack) {
	gl::DrawElementsInstancedBaseInstance::draw(pack);
}
inline void draw(const gl::DrawElementsInstancedBaseVertex::Pack & pack) {
	gl::DrawElementsInstancedBaseVertex::draw(pack);
}
inline void draw(const gl::DrawElementsInstancedBaseVertexBaseInstance::Pack & pack) {
	gl::DrawElementsInstancedBaseVertexBaseInstance::draw(pack);
}
inline void draw(const gl::DrawRangeElements::Pack & pack) {
	gl::DrawRangeElements::draw(pack);
}
inline void draw(const gl::DrawRangeElementsBaseVertex::Pack & pack) {
	gl::DrawRangeElementsBaseVertex::draw(pack);
}
inline void draw(const gl::MultiDrawArrays::Pack & pack) {
	gl::MultiDrawArrays::draw(pack);
}
inline void draw(const gl::MultiDrawElements::Pack & pack) {
	gl::MultiDrawElements::draw(pack);
}
inline void draw(const gl::MultiDrawElementsBaseVertex::Pack & pack) {
	gl::MultiDrawElementsBaseVertex::draw(pack);
}
 
}
 

#endif
