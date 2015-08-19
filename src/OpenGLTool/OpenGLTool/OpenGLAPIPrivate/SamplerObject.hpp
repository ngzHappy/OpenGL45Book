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
	//GL_TEXTURE_WRAP_S,
	//GL_TEXTURE_WRAP_T, 
	//GL_TEXTURE_WRAP_R,
	//GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, 
	//GL_TEXTURE_BORDER_COLOR, 
	//GL_TEXTURE_MIN_LOD, 
	//GL_TEXTURE_MAX_LOD, 
	//GL_TEXTURE_LOD_BIAS 
	//GL_TEXTURE_COMPARE_MODE, 
	//GL_TEXTURE_COMPARE_FUNC.


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

	
};

}




#endif
