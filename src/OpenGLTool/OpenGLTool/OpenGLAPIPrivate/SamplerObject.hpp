#ifndef __SAMPLE__OBJECT__H__0x00__
#define __SAMPLE__OBJECT__H__0x00__

#include "GLUnamedObject.hxx"

namespace gl {

/*  */
class SamplerObject{
protected:
    union{
        UnsignedInteger sampler_;
        UnsignedInteger value_;
    };
public:

    typedef SamplerObject ThisType;
    friend bool operator<(const ThisType & l, const ThisType & r){
        return l.value_ <r.value_;
    }
    friend bool operator>(const ThisType & l, const ThisType & r){
        return l.value_ >r.value_;
    }
    friend bool operator>=(const ThisType & l, const ThisType & r){
        return l.value_ >= r.value_;
    }
    friend bool operator<=(const ThisType & l, const ThisType & r){
        return l.value_ <= r.value_;
    }
    friend bool operator==(const ThisType & l, const ThisType & r){
        return l.value_ == r.value_;
    }
    friend bool operator!=(const ThisType & l, const ThisType & r){
        return l.value_ != r.value_;
    }

    explicit operator const UnsignedInteger&()const{ return value_; }
    explicit SamplerObject(const UnsignedInteger v) :value_(v){}
    explicit operator bool()const{ return value_ != 0; }

    SamplerObject() :sampler_(0){}
    SamplerObject(const SamplerObject & v) :value_(v.value_){}

};

class NamedSamplerObject : public SamplerObject {
    NamedSamplerObject(const SamplerObject & v):SamplerObject(v){
    }
    NamedSamplerObject(SamplerObject && v):SamplerObject(std::move(v)){
    }
 
public:

    explicit operator const UnsignedInteger&()const{ return value_; }
    explicit operator bool()const{ return value_ != 0; }
    NamedSamplerObject(){}
    NamedSamplerObject(const UnsignedInteger v):SamplerObject(v){
    }

    void bind(GLuint location)const{
		glBindSampler(location, value_);
    }
 
	enum  class FilterType : GLenum{
		NEAREST=GL_NEAREST,
		LINEAR=GL_LINEAR,
		NEAREST_MIPMAP_NEAREST=GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST=GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR=GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR=GL_LINEAR_MIPMAP_LINEAR,
	};
	void setMinFilter(FilterType type= FilterType::NEAREST) {
		glSamplerParameteri(sampler_, GL_TEXTURE_MIN_FILTER, GLenum(type));
	}
	void setMagFilter(FilterType type= FilterType::NEAREST) {
		glSamplerParameteri(sampler_, GL_TEXTURE_MAG_FILTER, GLenum(type));
	}

	void setMinLod(GLint i=-1000){
		glSamplerParameteri(sampler_, GL_TEXTURE_MIN_LOD, i);
	}
	void setMaxLod(GLint i= 1000) {
		glSamplerParameteri(sampler_, GL_TEXTURE_MAX_LOD, i);
	}

	enum class WrapType : GLenum {
		CLAMP_TO_BORDER=GL_CLAMP_TO_BORDER,
		CLAMP_TO_EDGE=GL_CLAMP_TO_EDGE,
		MIRRORED_REPEAT=GL_MIRRORED_REPEAT,
		REPEAT=GL_REPEAT,
		MIRROR_CLAMP_TO_EDGE=GL_MIRROR_CLAMP_TO_EDGE,
	};
	void setWrapS(WrapType type = WrapType::REPEAT) {
		glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_S, GLenum(type));
	}
	void setWrapT(WrapType type = WrapType::REPEAT) {
		glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_T, GLenum(type));
	}
	void setWrapR(WrapType type = WrapType::REPEAT) {
		glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_R, GLenum(type));
	}

	void setBorderColor(float r=0,float g=0,float b=0,float a=0) {
		const float v__[]{r,g,b,a};
		glSamplerParameterfv(sampler_, GL_TEXTURE_BORDER_COLOR,v__);
	}

	enum class CompareFunction : GLenum {
		LEQUAL=GL_LEQUAL,
		GEQUAL=GL_GEQUAL,
		LESS=GL_LESS,
		GREATER=GL_GREATER,
		EQUAL=GL_EQUAL,
		NOTEQUAL=GL_NOTEQUAL,
		ALWAYS=GL_ALWAYS,
		NEVER=GL_NEVER,
	};
	void setCompareFunction(CompareFunction type = CompareFunction::LEQUAL) {
		glSamplerParameteri(sampler_, GL_TEXTURE_COMPARE_FUNC, GLenum(type));
	}

	enum class CompareMode:GLenum {
		TEXTURE_COMPARE_MODE=GL_TEXTURE_COMPARE_MODE,
		NONE = GL_NONE
	};
	void setCompareMode(CompareMode type = CompareMode::TEXTURE_COMPARE_MODE) {
		glSamplerParameteri(sampler_, GL_TEXTURE_COMPARE_MODE, GLenum(type));
	}
};

}




#endif



