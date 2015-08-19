#ifndef __TEXTURE__opengltool__type__0x00
#define __TEXTURE__opengltool__type__0x00

#include "BaseType.hpp"

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

    };


}

#endif
