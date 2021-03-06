﻿
#ifndef __BUFFeR____OPENGL__API__PRIVATE__0x00
#define __BUFFeR____OPENGL__API__PRIVATE__0x00

#include "BaseType.hpp"

namespace gl {

class Buffer{
protected:
    union{
    UnsignedInteger program_ ;
    UnsignedInteger value_ ;
    };
public:

    typedef Buffer ThisType;
    friend bool operator<(const ThisType & l,const ThisType & r){
        return l.value_ <r.value_;
    }
    friend bool operator>(const ThisType & l,const ThisType & r){
        return l.value_ >r.value_;
    }
    friend bool operator>=(const ThisType & l,const ThisType & r){
        return l.value_ >=r.value_;
    }
    friend bool operator<=(const ThisType & l,const ThisType & r){
        return l.value_ <=r.value_;
    }
    friend bool operator==(const ThisType & l,const ThisType & r){
        return l.value_ ==r.value_;
    }
    friend bool operator!=(const ThisType & l,const ThisType & r){
        return l.value_ !=r.value_;
    }

    explicit operator const UnsignedInteger&()const{return value_;}
    explicit Buffer(const UnsignedInteger v):value_(v){}
    explicit operator bool()const{return value_!=0; }

    Buffer():program_(0){}
    Buffer(const Buffer & v ):value_(v.value_){}

};


class NamedBuffer : public Buffer {
    NamedBuffer(const Buffer & v):Buffer(v){ /* a buffer can not convto named buffer */ }
public:
	explicit operator const UnsignedInteger&()const{ return value_; }
	explicit operator bool()const{ return value_ != 0; }
    NamedBuffer(){}
    explicit NamedBuffer(const UnsignedInteger v):Buffer(v){}

	enum class Access : GLenum {
		READ_ONLY = GL_READ_ONLY,
		WRITE_ONLY = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE,
	};
	void * map(Access access = Access::READ_ONLY) {
		return glMapNamedBuffer(value_, GLenum(access));
	}
	void unmap() {
		glUnmapNamedBuffer(value_);
	}
	template<typename T >
	T * map(Access access = Access::READ_ONLY) {
		return (T*)(glMapNamedBuffer(value_, GLenum(access)));
	}
};



}//gl

 


#endif
