#ifndef __FBO__TYPE__HPP__0x00
#define __FBO__TYPE__HPP__0x00

#include "BaseType.hpp"

namespace gl{

	/*  */
	class FrameBufferObject{
	protected:
		union{
			UnsignedInteger fbo_;
			UnsignedInteger value_;
		};
	public:

		typedef FrameBufferObject ThisType;
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
		explicit FrameBufferObject(const UnsignedInteger v) :value_(v){}
		explicit operator bool()const{ return value_ != 0; }

		FrameBufferObject() :fbo_(0){}
		FrameBufferObject(const FrameBufferObject & v) :value_(v.value_){}

	};

	/*  */
    class NamedFrameBufferObject :
            public FrameBufferObject
    {
        NamedFrameBufferObject(const FrameBufferObject & v):
            FrameBufferObject(v){}
    public:
		explicit operator const UnsignedInteger&()const{ return value_; }
		explicit operator bool()const{ return value_ != 0; }
        NamedFrameBufferObject(){}
        NamedFrameBufferObject(const UnsignedInteger v):FrameBufferObject(v){
        }

		void clearColor( 
			float r,float g,float b,float a ,
			GLint drawBuffer =0) {
			const float temp[]{r,g,b,a};
			glClearNamedFramebufferfv(
				value_,GL_COLOR, drawBuffer,
				temp
				);
		}

		void clearColor(
			const float *  color ,
			GLint drawBuffer = 0) {
			glClearNamedFramebufferfv(
				value_, GL_COLOR, drawBuffer,
				color
				);
		}

		void clearDepth(const float & value ) {
			glClearNamedFramebufferfv(value_, GL_DEPTH, 0,&value);
		}

		void clearStencil(const float & value) {
			glClearNamedFramebufferfv(value_, GL_STENCIL, 0, &value);
		}

    };
}

#endif
