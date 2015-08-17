#ifndef __varrayTYPE____OPENGL__API__PRIVATE__0x00
#define __varrayTYPE____OPENGL__API__PRIVATE__0x00

#include "BaseType.hpp"
#include "BufferType.hpp"
namespace gl {

class VertexArrayObject{
protected:
    union{
    UnsignedInteger vertexArrayObject_ ;
    UnsignedInteger value_ ;
    };
public:

    typedef VertexArrayObject ThisType;
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
    explicit VertexArrayObject(const UnsignedInteger v):value_(v){}
    explicit operator bool()const{return value_!=0; }

    VertexArrayObject():value_(0){}
    VertexArrayObject(const VertexArrayObject & v ):value_(v.value_){}

};


class NamedVertexArrayObject :public VertexArrayObject {
NamedVertexArrayObject(const VertexArrayObject & v):
    VertexArrayObject(v){/* can not convert */}
public:
	enum class Size : int{
		One = 1,Two =2,Three=3,Four =4
	};

    NamedVertexArrayObject(){}
    explicit NamedVertexArrayObject(const UnsignedInteger v):
        VertexArrayObject(v){}
	explicit operator const UnsignedInteger&()const{ return value_; }
	explicit operator bool()const{ return value_ != 0; }
	
	void vertexArrayElementBuffer(const Buffer & buffer) {
		glVertexArrayElementBuffer( value_,(GLuint)buffer );
	}
    void bindElementBuffer(const Buffer & buffer){
        glVertexArrayElementBuffer( value_,(GLuint)buffer );
    }

	void bindDivisor(
		GLuint bindingindex,
		GLuint divisor=1) {
		glVertexArrayBindingDivisor(value_, bindingindex, divisor);
	}

	enum class Type :GLenum{
		BYTE=GL_BYTE, 
		UNSIGNED_BYTE= GL_UNSIGNED_BYTE,
		SHORT=GL_SHORT, 
		UNSIGNED_SHORT=GL_UNSIGNED_SHORT,
		INT=GL_INT, 
		UNSIGNED_INT= GL_UNSIGNED_INT,
		FIXED=GL_FIXED, 
		INT_2_10_10_10_REV= GL_INT_2_10_10_10_REV,
		FLOAT=GL_FLOAT, 
		UNSIGNED_INT_2_10_10_10_REV= GL_UNSIGNED_INT_2_10_10_10_REV,
		HALF_FLOAT=GL_HALF_FLOAT, 
		UNSIGNED_INT_10F_11F_11F_REV= GL_UNSIGNED_INT_10F_11F_11F_REV,
		DOUBLE=GL_DOUBLE,
	};
	/*将buffer绑定到glsl上*/
	//GL_BYTE, GL_SHORT, GL_INT, GL_FIXED, GL_FLOAT, GL_HALF_FLOAT,GL_DOUBLE
	//GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, and GL_UNSIGNED_INT
	//GL_INT_2_10_10_10_REV and GL_UNSIGNED_INT_2_10_10_10_REV
	//GL_UNSIGNED_INT_10F_11F_11F_REV
	void bindBuffer(
		GLuint bindingindex,
		NamedBuffer buffer,
        IntegerPtr offset =0                    /*包的起始偏置*/,
        SizeInteger stride =4*sizeof(gl::Float) /*包的大小*/,
        UnsignedInteger relativeoffset =0       /*解包后的起始偏置*/,
        Size size = Size::Four                  /*读取数据的大小*/,
        Type type = Type::FLOAT                 /*读取数据的类型*/,
		GLboolean normalized = false/*是否强制归一化*/)
	{
		_bindBuffer(
			bindingindex,(GLuint)buffer,
			offset,stride,
			relativeoffset, size,(GLenum)type,
			normalized
			);
	}
	void bind()const {
		glBindVertexArray(value_);
	}
private:
	void enableVertexArrayAttrib(UnsignedInteger index) {
		glEnableVertexArrayAttrib(value_, index);
	}
	/*
	attribindex : from glsl
	bindingindex : from local
	*/
	void vertexArrayAttribBinding(UnsignedInteger attribindex, UnsignedInteger bindingindex) {
		glVertexArrayAttribBinding(value_, attribindex, bindingindex);
	}
	//??glVertexArrayVertexBuffer
	//void glVertexArrayVertexBuffer(GLuint vaobj,
	//	GLuint bindingindex,
	//	GLuint buffer,
	//	GLintptr offset,
	//	GLsizei stride);
	// 此函数用于解包 glBindVertexBuffer
	void vertexArrayVertexBuffer(
		GLuint bindingindex,
		GLuint buffer,
		GLintptr offset/*包的起始位置*/,
		GLsizei stride/*包的大小*/
		) {
		glVertexArrayVertexBuffer(value_, bindingindex, buffer, offset, stride);
	}
	//??glVertexArrayAttribFormat
	// 此函数用于读包
	void vertexArrayAttribFormat(
		GLuint attribindex /*glsl*/,
		Size size/*buffer!!*/,
		GLenum type/*buffer!!*/,
		GLboolean normalized = false/*buffer!!*/,
		GLuint relativeoffset = 0/*解包后的偏置*/
		) {
		glVertexArrayAttribFormat(value_,
			attribindex, (GLint)size, type, normalized, relativeoffset);
	}
	//??glVertexArrayVertexBuffers
	void _bindBuffer(
		GLuint bindingindex,
		GLuint buffer,
		GLintptr offset       /*包的起始偏置*/,
		GLsizei stride        /*包的大小*/,
		GLuint relativeoffset /*解包后的起始偏置*/,
		Size size             /*读取数据的大小*/,
		GLenum type           /*读取数据的类型*/,
		GLboolean normalized = false/*是否强制归一化*/
		) {
		//本函数假定glsl attribindex 与 buffer bindingindex 一致
		const GLuint & attribindex = bindingindex;
		//将buffer绑定
		this->enableVertexArrayAttrib(bindingindex);
		this->vertexArrayVertexBuffer(
			bindingindex, 
			buffer, 
			offset, 
			stride
			);
		//设定glsl如何从buffer中取数据
		this->vertexArrayAttribFormat(
			attribindex, 
			size, 
			type, 
			normalized, 
			relativeoffset
			);
		//bind glsl to loacal
		glVertexArrayAttribBinding(value_, attribindex, bindingindex);
	}
};

}

#endif
