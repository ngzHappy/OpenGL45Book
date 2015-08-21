#ifndef __TEXTURE__opengltool__type__0x00
#define __TEXTURE__opengltool__type__0x00

#include "BaseType.hpp"
#include "BufferType.hpp"

namespace gl{

/*
Texture Target	                Sampler Type
GL_TEXTURE_1D	                sampler1D
GL_TEXTURE_2D	                sampler2D
GL_TEXTURE_3D	                sampler3D
GL_TEXTURE_RECTANGLE	        sampler2DRect
GL_TEXTURE_1D_ARRAY	            sampler1DArray
GL_TEXTURE_2D_ARRAY	            sampler2DArray
GL_TEXTURE_CUBE_MAP	            samplerCube
GL_TEXTURE_CUBE_MAP_ARRAY       samplerCubeArray
GL_TEXTURE_BUFFER	            samplerBuffer
GL_TEXTURE_2D_MULTISAMPLE       sampler2DMS
GL_TEXTURE_2D_MULTISAMPLE_ARRAY	sampler2DMSArray

vec4 texelFetch(sampler1D s, int P, int lod);
vec4 texelFetch(sampler2D s, ivec2 P, int lod);
ivec4 texelFetch(isampler2D s, ivec2 P, int lod);
uvec4 texelFetch(usampler3D s, ivec3 P, int lod);

vec4 texture(sampler1D s, float P);
vec4 texture(sampler2D s, vec2 P);
ivec4 texture(isampler2D s, vec2 P);
uvec4 texture(usampler3D s, vec3 P);

image1D 1D image
image2D 2D image
image3D 3D image
imageCube Cube map image
imageCubeArray Cube map array image
imageRect Rectangle image
image1DArray 1D array image
image2DArray 2D array image
imageBuffer Buffer image
image2DMS 2D multi-sample image
image2DMSArray 2D multi-sample array image

ivec4 imageLoad(readonly iimage2D image, ivec2 P);
void imageStore(iimage2D image, ivec2 P, ivec4 data);
uvec4 imageLoad(readonly uimage2D image, ivec2 P);
void imageStore(uimage2D image, ivec2 P, uvec4 data);

gsampler1D​ 	GL_TEXTURE_1D 	1D texture
gsampler2D​ 	GL_TEXTURE_2D 	2D texture
gsampler3D​ 	GL_TEXTURE_3D 	3D texture
gsamplerCube​ 	GL_TEXTURE_CUBE_MAP 	Cubemap Texture
gsampler2DRect​ 	GL_TEXTURE_RECTANGLE 	Rectangle Texture
gsampler1DArray​ 	GL_TEXTURE_1D_ARRAY 	1D Array Texture
gsampler2DArray​ 	GL_TEXTURE_2D_ARRAY 	2D Array Texture
gsamplerCubeArray​ 	GL_TEXTURE_CUBE_MAP_ARRAY 	Cubemap Array Texture
(requires GL 4.0 or ARB_texture_cube_map_array)
gsamplerBuffer​ 	GL_TEXTURE_BUFFER 	Buffer Texture
gsampler2DMS​ 	GL_TEXTURE_2D_MULTISAMPLE 	Multisample Texture
gsampler2DMSArray​ 	GL_TEXTURE_2D_MULTISAMPLE_ARRAY 	Multisample Array Texture

*/
	class  Texture {
    protected:
		union{
			UnsignedInteger texture_;
			UnsignedInteger value_;
		};
	public:
		Texture() :value_(0){}
		Texture(const Texture & v) :value_(v.value_){}

		typedef Texture ThisType;
		friend bool operator<(const Texture & l, const Texture & r){
			return l.value_ <r.value_;
		}
		friend bool operator>(const Texture & l, const Texture & r){
			return l.value_ >r.value_;
		}
		friend bool operator>=(const Texture & l, const Texture & r){
			return l.value_ >= r.value_;
		}
		friend bool operator<=(const Texture & l, const Texture & r){
			return l.value_ <= r.value_;
		}
		friend bool operator==(const Texture & l, const Texture & r){
			return l.value_ == r.value_;
		}
		friend bool operator!=(const Texture & l, const Texture & r){
			return l.value_ != r.value_;
		}

		explicit operator const UnsignedInteger&()const{ return value_; }
		explicit Texture(const UnsignedInteger v) :value_(v){}
		explicit operator bool()const{ return value_ != 0; }

        enum class InternalFormat : GLenum{
            R8      =GL_R8       ,
            R16     =GL_R16      ,
            R16F    =GL_R16F     ,
            R32F    =GL_R32F     ,
            R8I     =GL_R8I      ,
            R16I    =GL_R16I     ,
            R32I    =GL_R32I     ,
            R8UI    =GL_R8UI     ,
            R16UI   =GL_R16UI    ,
            R32UI   =GL_R32UI    ,
            RG8     =GL_RG8      ,
            RG16    =GL_RG16     ,
            RG16F   =GL_RG16F    ,
            RG32F   =GL_RG32F    ,
            RG8I    =GL_RG8I     ,
            RG16I   =GL_RG16I    ,
            RG32I   =GL_RG32I    ,
            RG8UI   =GL_RG8UI    ,
            RG16UI  =GL_RG16UI   ,
            RG32UI  =GL_RG32UI   ,
            RGB32F  =GL_RGB32F   ,
            RGB32I  =GL_RGB32I   ,
            RGB32UI =GL_RGB32UI  ,
            RGBA8   =GL_RGBA8    ,
            RGBA16  =GL_RGBA16   ,
            RGBA16F =GL_RGBA16F  ,
            RGBA32F =GL_RGBA32F  ,
            RGBA8I  =GL_RGBA8I   ,
            RGBA16I =GL_RGBA16I  ,
            RGBA32I =GL_RGBA32I  ,
            RGBA8UI =GL_RGBA8UI  ,
            RGBA16UI=GL_RGBA16UI ,
            RGBA32UI=GL_RGBA32UI ,
        };

	};

    class NamedTexture :public Texture {
        NamedTexture( const Texture & v ):Texture(v){
            /* can not convert */
        }
    public:
		explicit operator const UnsignedInteger&()const{ return value_; }
		explicit operator bool()const{ return value_ != 0; }
        NamedTexture(){}
        explicit NamedTexture(const UnsignedInteger v):
            Texture(v)
        {}
            int width()const{
                if(0==value_){return -1;}
                int ans;
                glGetTextureLevelParameteriv(texture_,0,GL_TEXTURE_WIDTH,&ans);
                return ans;
            }
            int height()const{
                if(0==value_){return -1;}
                int ans;
                glGetTextureLevelParameteriv(texture_,0,GL_TEXTURE_HEIGHT,&ans);
                return ans;
            }

			/*
			GL_TEXTURE_1D, 
			GL_TEXTURE_2D, 
			GL_TEXTURE_3D, 
			GL_TEXTURE_1D_ARRAY, 
			GL_TEXTURE_2D_ARRAY, 
			GL_TEXTURE_RECTANGLE, 
			GL_TEXTURE_CUBE_MAP, 
			GL_TEXTURE_CUBE_MAP_ARRAY, 
			GL_TEXTURE_BUFFER, 
			GL_TEXTURE_2D_MULTISAMPLE or 
			GL_TEXTURE_2D_MULTISAMPLE_ARRAY
			*/
			void bind( GLuint i,GLenum target )const {
				glActiveTexture(GL_TEXTURE0+i);
				glBindTexture(target, texture_);
			}

			void bind(GLuint i) const{
				glBindTextureUnit(i, texture_);
			}


            void bind(
                    InternalFormat  internalformat,
                    gl::NamedBuffer buffer
                      ){
                glTextureBuffer(
                            texture_,
                            GLenum(internalformat),
                            GLuint(buffer)
                            );
            }
    };


}

#endif
