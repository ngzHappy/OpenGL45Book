
#ifndef __HXX____GL__UN__NAMED__OBJECT__0x00__
#define __HXX____GL__UN__NAMED__OBJECT__0x00__

#include "BaseType.hpp"
#include "VertexArrayType.hpp"
#include "TexttureOpenglTool.hpp"
#include "FBOTypeGL.hpp"

namespace gl {


class __UnNamedObject  {
public:

    static inline void bindVertexArray(
            const NamedVertexArrayObject & v
            ) {
        /* layout(location = 0) in vec3 vPositon; */
        v.bind();
    }

    /*
    layout (binding = 0) uniform sampler2DMS input_image;
    GL_TEXTURE_1D
    GL_TEXTURE_2D
    GL_TEXTURE_3D
    GL_TEXTURE_1D_ARRAY
    GL_TEXTURE_2D_ARRAY
    GL_TEXTURE_RECTANGLE
    GL_TEXTURE_CUBE_MAP
    GL_TEXTURE_CUBE_MAP_ARRAY
    GL_TEXTURE_BUFFER
    GL_TEXTURE_2D_MULTISAMPLE
    GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    */
    static inline void bindTexture(
        const NamedTexture & v,
        GLuint location /* 0 1 2 3 4 5 ...*/,
        GLenum target = GL_TEXTURE_RECTANGLE
        ) {
        v.bind(location,target);
    }

    static inline void bindFrameBuffer() {
            glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
    static inline void bindFrameBuffer( gl::NamedFrameBufferObject obj ) {
        glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)obj);
    }

	static inline void bindShaderStorageBuffer(
		GLuint index,
		const gl::Buffer & buffer
		) {
		//GL_ATOMIC_COUNTER_BUFFER
		//GL_TRANSFORM_FEEDBACK_BUFFER
		//GL_UNIFORM_BUFFER
		//GL_SHADER_STORAGE_BUFFER. 
		//void glBindBufferBase(
		//	GLenum target,
		//	GLuint index,
		//	GLuint buffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER,index, GLuint(buffer));
	}

};

}
#endif


