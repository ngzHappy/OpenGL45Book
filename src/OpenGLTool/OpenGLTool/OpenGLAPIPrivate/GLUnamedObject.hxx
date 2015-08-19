
#ifndef __HXX____GL__UN__NAMED__OBJECT__0x00__
#define __HXX____GL__UN__NAMED__OBJECT__0x00__

#include "BaseType.hpp"
#include "VertexArrayType.hpp"
#include "TexttureOpenglTool.hpp"
#include "FBOTypeGL.hpp"
#include "SamplerObject.hpp"
#include <array>
#include <memory>

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
        GLenum target 
        ) {
        v.bind(location,target);
    }

	static inline void bindTexture(
		GLuint location /* 0 1 2 3 4 5 ...*/,
		const NamedTexture & v
		) {
		v.bind( location );
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

/*
format::
GL_RGBA32F
GL_RGBA16F
GL_RG32F
GL_RG16F
GL_R11F_G11F_B10F
GL_R32F
GL_R16F
GL_RGBA32UI
GL_RGBA16UI
GL_RGB10_A2UI
GL_RGBA8UI
GL_RG32UI
GL_RG16UI
GL_RG8UI
GL_R32UI
GL_R16UI
GL_R8UI
GL_RGBA32I
GL_RGBA16I
GL_RGBA8I
GL_RG32I
GL_RG16I
GL_RG8I
GL_R32I
GL_R16I
GL_R8I
GL_RGBA16
GL_RGB10_A2
GL_RGBA8
GL_RG16
GL_RG8
GL_R16
GL_R8
GL_RGBA16_SNORM
GL_RGBA8_SNORM
GL_RG16_SNORM
GL_RG8_SNORM
GL_R16_SNORM
GL_R8_SNORM
*/
	static inline void bindImageTexture(
		GLuint binding_,
		NamedTexture texture,
		GLenum access= GL_READ_WRITE,
		GLenum format = GL_R32F,
		GLint level = 0,
		GLboolean layered = false,
		GLint layer =0
		) {
		glBindImageTexture(
			binding_,(GLuint)texture,
			level,layered,layer,
			access,format);
	}

	void bindSampler(GLuint location, const NamedSamplerObject & nso_) {
		nso_.bind(location);
	}

/*
细分着色器
*/
	static inline void patchVertices(GLint value = 3) {
		glPatchParameteri(GL_PATCH_VERTICES, value);
	}
/*
细分着色器
*/
	class PatchLevels {
	public:
		PatchLevels(
			const std::array<gl::Float, 4> & outer,
			const std::array<gl::Float, 4> & inner
			) :outer_level_array(outer),
			inner_level_array(inner){}

		PatchLevels(
			const std::array<gl::Float, 4> & outer
			) :outer_level_array(outer),
			inner_level_array(outer) {}

		PatchLevels(
			const std::array<gl::Float, 3> & outer,
			const gl::Float  & inner
			) :outer_level_array({ outer[0], outer[1], outer[2], outer[2] }),
			inner_level_array({ inner ,inner ,inner ,inner  }) {}

		union {
			gl::Float outer_levels[4];
			std::array<gl::Float, 4> outer_level_array;
			struct {
				gl::Float outer_level_0;
				gl::Float outer_level_1;
				gl::Float outer_level_2;
				gl::Float outer_level_3;
			};
		};
		union {
			gl::Float inner_levels[4];
			std::array<gl::Float, 4> inner_level_array;
			struct {
				gl::Float inner_level_0;
				gl::Float inner_level_1;
				gl::Float inner_level_2;
				gl::Float inner_level_3;
			};
		};
		
		PatchLevels() :PatchLevels({ 2,2,2,2 }, {2,2,2,2}){
		}
		 
	};



	static inline void patchLevels( const PatchLevels & levels ) {
		glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, levels.outer_levels);
		glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, levels.inner_levels);
	}
};

typedef __UnNamedObject::PatchLevels PatchLevels;

}
#endif


