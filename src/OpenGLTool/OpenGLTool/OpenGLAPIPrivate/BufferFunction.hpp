
#ifndef __function__BUFFeR____OPENGL__API__PRIVATE__0x00
#define __function__BUFFeR____OPENGL__API__PRIVATE__0x00

#include "BufferType.hpp"

namespace gl {


/*
void glGenBuffers(	GLsizei n, GLuint * buffers);
*/
static inline void genBuffers( SizeInteger n ,Buffer * buffers ){
    glGenBuffers(n,(GLuint *)(buffers));
}

/*
void glCreateBuffers(	GLsizei n,GLuint *buffers);
*/
static inline void createBuffers(
	SizeInteger n, NamedBuffer * buffers
	){
	glCreateBuffers(n, (GLuint *)buffers);
}

/*

*/
static inline void createBuffers(
	NamedBuffer * buffer, GLsizei size
	) {
	glCreateBuffers(1, (GLuint *)buffer);
	//GLuint buffer, GLsizei size, const void * data, GLbitfield flags
	//GL_DYNAMIC_STORAGE_BIT 
	//GL_MAP_READ_BIT 
	//GL_MAP_WRITE_BIT 
	//GL_MAP_PERSISTENT_BIT 
	//GL_MAP_COHERENT_BIT 
	//GL_CLIENT_STORAGE_BIT 
	glNamedBufferStorage(
		(GLuint  )(*buffer), size,
		0, GL_DYNAMIC_STORAGE_BIT);
}

/*
void glDeleteBuffers(	GLsizei n,const GLuint * buffers);
*/
inline void deleteBuffers( SizeInteger n,const Buffer * buffers ){
glDeleteBuffers(n,(const GLuint *)(buffers));
}

enum class BindBufferTarget : GLenum{
    ARRAY_BUFFER	           =GL_ARRAY_BUFFER	             ,
    ATOMIC_COUNTER_BUFFER	   =GL_ATOMIC_COUNTER_BUFFER	     ,
    COPY_READ_BUFFER	       =GL_COPY_READ_BUFFER	    ,
    COPY_WRITE_BUFFER	       =GL_COPY_WRITE_BUFFER	         ,
    DISPATCH_INDIRECT_BUFFER   =GL_DISPATCH_INDIRECT_BUFFER	 ,
    DRAW_INDIRECT_BUFFER	   =GL_DRAW_INDIRECT_BUFFER	     ,
    ELEMENT_ARRAY_BUFFER	   =GL_ELEMENT_ARRAY_BUFFER	     ,
    PIXEL_PACK_BUFFER	       =GL_PIXEL_PACK_BUFFER	         ,
    PIXEL_UNPACK_BUFFER	       =GL_PIXEL_UNPACK_BUFFER	         ,
    QUERY_BUFFER	           =GL_QUERY_BUFFER	             ,
    SHADER_STORAGE_BUFFER	   =GL_SHADER_STORAGE_BUFFER	     ,
    TEXTURE_BUFFER	           =GL_TEXTURE_BUFFER	             ,
    TRANSFORM_FEEDBACK_BUFFER  =GL_TRANSFORM_FEEDBACK_BUFFER    ,
    UNIFORM_BUFFER	           =GL_UNIFORM_BUFFER	             ,
};
/*
void glBindBuffer(	GLenum target, GLuint buffer);
Buffer Binding Target	        Purpose
GL_ARRAY_BUFFER	                Vertex attributes
GL_ATOMIC_COUNTER_BUFFER	    Atomic counter storage
GL_COPY_READ_BUFFER	            Buffer copy source
GL_COPY_WRITE_BUFFER	        Buffer copy destination
GL_DISPATCH_INDIRECT_BUFFER	    Indirect compute dispatch commands
GL_DRAW_INDIRECT_BUFFER	        Indirect command arguments
GL_ELEMENT_ARRAY_BUFFER	        Vertex array indices
GL_PIXEL_PACK_BUFFER	        Pixel read target
GL_PIXEL_UNPACK_BUFFER	        Texture data source
GL_QUERY_BUFFER	                Query result buffer
GL_SHADER_STORAGE_BUFFER	    Read-write storage for shaders
GL_TEXTURE_BUFFER	            Texture data buffer
GL_TRANSFORM_FEEDBACK_BUFFER	Transform feedback buffer
GL_UNIFORM_BUFFER	            Uniform block storage
*/
static inline void bindBuffer(BindBufferTarget target, Buffer buffer){
glBindBuffer( (GLenum)(target),(GLuint)buffer );
}


/*
简易使用 glBindBuffer(GL_ARRAY_BUFFER,...)
*/
static inline void bindBufferByArray( Buffer buffer) {
	glBindBuffer(GL_ARRAY_BUFFER, (GLuint)buffer);
}

enum class BufferDataTarget:GLenum{
    ARRAY_BUFFER	             =GL_ARRAY_BUFFER	            ,
    ATOMIC_COUNTER_BUFFER	     =GL_ATOMIC_COUNTER_BUFFER	    ,
    COPY_READ_BUFFER	         =GL_COPY_READ_BUFFER	        ,
    COPY_WRITE_BUFFER	         =GL_COPY_WRITE_BUFFER	        ,
    DISPATCH_INDIRECT_BUFFER	 =GL_DISPATCH_INDIRECT_BUFFER	,
    DRAW_INDIRECT_BUFFER	     =GL_DRAW_INDIRECT_BUFFER	    ,
    ELEMENT_ARRAY_BUFFER	     =GL_ELEMENT_ARRAY_BUFFER	    ,
    PIXEL_PACK_BUFFER	         =GL_PIXEL_PACK_BUFFER	        ,
    PIXEL_UNPACK_BUFFER	         =GL_PIXEL_UNPACK_BUFFER	    ,
    QUERY_BUFFER	             =GL_QUERY_BUFFER	            ,
    SHADER_STORAGE_BUFFER	     =GL_SHADER_STORAGE_BUFFER	    ,
    TEXTURE_BUFFER	             =GL_TEXTURE_BUFFER	            ,
    TRANSFORM_FEEDBACK_BUFFER    =GL_TRANSFORM_FEEDBACK_BUFFER  ,
    UNIFORM_BUFFER	             =GL_UNIFORM_BUFFER	            ,
};
enum class BufferDataUsage:GLenum{
    STREAM_DRAW   =GL_STREAM_DRAW,
    STREAM_READ   =GL_STREAM_READ,
    STREAM_COPY   =GL_STREAM_COPY,
    STATIC_DRAW   =GL_STATIC_DRAW,
    STATIC_READ   =GL_STATIC_READ,
    STATIC_COPY   =GL_STATIC_COPY,
    DYNAMIC_DRAW  =GL_DYNAMIC_DRAW,
    DYNAMIC_READ  =GL_DYNAMIC_READ,
    DYNAMIC_COPY  =GL_DYNAMIC_COPY,
};
/*
void glBufferData(	GLenum target,
    GLsizeiptr size,
    const GLvoid * data,
    GLenum usage);

Buffer Binding Target	        Purpose
GL_ARRAY_BUFFER	                Vertex attributes
GL_ATOMIC_COUNTER_BUFFER	    Atomic counter storage
GL_COPY_READ_BUFFER	            Buffer copy source
GL_COPY_WRITE_BUFFER	        Buffer copy destination
GL_DISPATCH_INDIRECT_BUFFER	    Indirect compute dispatch commands
GL_DRAW_INDIRECT_BUFFER	        Indirect command arguments
GL_ELEMENT_ARRAY_BUFFER	        Vertex array indices
GL_PIXEL_PACK_BUFFER	        Pixel read target
GL_PIXEL_UNPACK_BUFFER	        Texture data source
GL_QUERY_BUFFER	                Query result buffer
GL_SHADER_STORAGE_BUFFER	    Read-write storage for shaders
GL_TEXTURE_BUFFER	            Texture data buffer
GL_TRANSFORM_FEEDBACK_BUFFER	Transform feedback buffer
GL_UNIFORM_BUFFER	            Uniform block storage

usage
GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW,
GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
GL_DYNAMIC_READ, GL_DYNAMIC_COPY,
*/
static inline void bufferData(
        BufferDataTarget target,
        SizeIntegerPtr size,
        const Void * data,
        BufferDataUsage usage = BufferDataUsage::STATIC_DRAW
        ){
glBufferData( (GLenum)target,size,data,(GLenum)usage );
}

static inline void bufferData(
	NamedBuffer buffer, SizeIntegerPtr size,
	const Void * data, BufferDataUsage usage = BufferDataUsage::STATIC_DRAW
	){
	glNamedBufferData(GLuint(buffer), size, data, (GLenum)usage);
}

/*
简易使用 glBufferData( GL_ARRAY_BUFFER,size,data,(GLenum)usage );
*/
static inline void bufferDataByArray(
        SizeIntegerPtr size,
        const Void * data,
        BufferDataUsage usage = BufferDataUsage::STATIC_DRAW ){
    glBufferData( GL_ARRAY_BUFFER,size,data,(GLenum)usage );
}

enum class BufferSubDataTarget : GLenum{
	ARRAY_BUFFER = GL_ARRAY_BUFFER,
	ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
	COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
	COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
	DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
	DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
	ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
	PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
	PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
	QUERY_BUFFER = GL_QUERY_BUFFER,
	SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
	UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
};
/*
void glBufferSubData(	GLenum target,
GLintptr offset,
GLsizeiptr size,
const GLvoid * data);

void glNamedBufferSubData(	GLuint buffer,
GLintptr offset,
GLsizei size,
const void *data);
*/
inline void bufferSubData(BufferSubDataTarget target,
	Integer offset ,
	SizeIntegerPtr size ,
	const Void * data
	){
	glBufferSubData( (GLenum)target ,offset , size ,data );
}
inline void bufferSubData(NamedBuffer buffer ,
	Integer offset,
	SizeIntegerPtr size,
	const Void * data
	){
	glNamedBufferSubData( (GLuint)buffer,offset,size,data );
}

}//~namespace gl



#endif
