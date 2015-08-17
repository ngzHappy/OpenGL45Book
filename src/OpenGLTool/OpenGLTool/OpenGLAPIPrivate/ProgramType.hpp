
#ifndef __PROGRAMTYPE____OPENGL__API__PRIVATE__0x00
#define __PROGRAMTYPE____OPENGL__API__PRIVATE__0x00

#include "GLUnamedObject.hxx"

namespace gl {

//layout(location = 0) in vec3 vPositon;
//layout(binding=0,std430) buffer TestBuffer{
//    float datas[];
//};
//layout(std140, binding = 0) uniform TestUniform{
//    mat4 mvp;
//};
//layout (binding = 0, rgba32ui) readonly uniform uimage2D image_in;
//layout (binding = 0) uniform sampler2DMS input_image;
//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, (GLuint)thisp->testBuffer);
//void glBindImageTexture

class Program
        :public __UnNamedObject
{
    union{
    UnsignedInteger program_ ;
    UnsignedInteger value_ ;
    };
public:

    template<typename T>
    class AtomicFunctions{
        T   locker  ;
    public:
        AtomicFunctions(T   locker_):locker(locker_){
            if(locker){locker->lock();}
        }
        AtomicFunctions(){
            if(locker){
				glFlush();
				locker->unlock();
			}
        }
    };

	/* 使用当前程序 */
	void use() const { glUseProgram(program_); }

    template<typename T>
    AtomicFunctions<T> use( T   locker ) const {
        AtomicFunctions<T> ans(locker);
        glUseProgram(program_);
        return ans;
    }

/* ----------------------------------------- */

    Program():program_(0){}
    Program(const Program & v ):program_(v.program_){}

    typedef Program ThisType;
    friend bool operator<(const Program & l,const Program & r){
        return l.value_ <r.value_;
    }
    friend bool operator>(const Program & l,const Program & r){
        return l.value_ >r.value_;
    }
    friend bool operator>=(const Program & l,const Program & r){
        return l.value_ >=r.value_;
    }
    friend bool operator<=(const Program & l,const Program & r){
        return l.value_ <=r.value_;
    }
    friend bool operator==(const Program & l,const Program & r){
        return l.value_ ==r.value_;
    }
    friend bool operator!=(const Program & l,const Program & r){
        return l.value_ !=r.value_;
    }

    explicit operator const UnsignedInteger&()const{return value_;}
    explicit Program(const UnsignedInteger v):value_(v){}
    explicit operator bool()const{return value_!=0; }
//glGetUniformIndices
//void glGetActiveUniformsiv
	GLint getUniformLocation(const char * name) {
		return glGetUniformLocation(program_,name);
	}

	/* uniform int sampleSize = 8; */
	void setUniform1f( 
		GLint location,
		GLfloat v0) {
		glProgramUniform1f(program_,location,v0);
	}

	void setUniform2f( 
		GLint location,
		GLfloat v0,
		GLfloat v1) {
		glProgramUniform2f(program_,location,v0,v1);
	}

	void setUniform3f( 
		GLint location,
		GLfloat v0,
		GLfloat v1,
		GLfloat v2) {
		glProgramUniform3f(program_,location,v0,v1,v2);
	}

	void setUniform4f( 
		GLint location,
		GLfloat v0,
		GLfloat v1,
		GLfloat v2,
		GLfloat v3) {
		glProgramUniform4f(program_,location,v0,v1,v2,v3);
	}

	void setUniform1i( 
		GLint location,
		GLint v0) {
		glProgramUniform1i(program_,location,v0);
	}

	void setUniform2i( 
		GLint location,
		GLint v0,
		GLint v1) {
		glProgramUniform2i(program_, location, v0,v1);
	}

	void setUniform3i( 
		GLint location,
		GLint v0,
		GLint v1,
		GLint v2) {
		glProgramUniform3i(program_, location, v0, v1,v2);
	}

	void setUniform4i( 
		GLint location,
		GLint v0,
		GLint v1,
		GLint v2,
		GLint v3) {
		glProgramUniform4i(program_, location, v0, v1, v2,v3);
	}

	void setUniform1ui( 
		GLint location,
		GLuint v0) {
		glProgramUniform1ui(program_,location,v0);
	}

	void setUniform2ui( 
		GLint location,
		GLint v0,
		GLuint v1) {
		glProgramUniform2ui(program_, location, v0,v1);
	}

	void setUniform3ui( 
		GLint location,
		GLint v0,
		GLint v1,
		GLuint v2) {
		glProgramUniform3ui(program_, location, v0, v1,v2);
	}

	void setUniform4ui( 
		GLint location,
		GLint v0,
		GLint v1,
		GLint v2,
		GLuint v3) {
		glProgramUniform4ui(program_, location, v0, v1, v2,v3);
	}

	void setUniform1fv( 
		GLint location,
		GLsizei count,
		const GLfloat *value) {
		glProgramUniform1fv(program_,location,count,value);
	}

	void setUniform2fv( 
		GLint location,
		GLsizei count,
		const GLfloat *value) {
		glProgramUniform2fv(program_, location, count, value);
	}

	void setUniform3fv( 
		GLint location,
		GLsizei count,
		const GLfloat *value) {
		glProgramUniform3fv(program_, location, count, value);
	}

	void setUniform4fv(
		GLint location,
		GLsizei count,
		const GLfloat *value) {
		glProgramUniform4fv(program_, location, count, value);
	}

	void setUniform1iv(
		GLint location,
		GLsizei count,
		const GLint *value) {
		glProgramUniform1iv(program_, location, count, value);
	}

	void setUniform2iv(
		GLint location,
		GLsizei count,
		const GLint *value) {
		glProgramUniform2iv(program_, location, count, value);
	}

	void setUniform3iv(
		GLint location,
		GLsizei count,
		const GLint *value) {
		glProgramUniform3iv(program_, location, count, value);
	}

	void setUniform4iv(
		GLint location,
		GLsizei count,
		const GLint *value) {
		glProgramUniform4iv(program_, location, count, value);
	}

	void setUniform1uiv(
		GLint location,
		GLsizei count,
		const GLuint *value) {
		glProgramUniform1uiv(program_, location, count, value);
	}

	void setUniform2uiv(
		GLint location,
		GLsizei count,
		const GLuint *value) {
		glProgramUniform2uiv(program_, location, count, value);
	}

	void setUniform3uiv(
		GLint location,
		GLsizei count,
		const GLuint *value) {
		glProgramUniform3uiv(program_, location, count, value);
	}

	void setUniform4uiv(
		GLint location,
		GLsizei count,
		const GLuint *value) {
		glProgramUniform4uiv(program_, location, count, value);
	}

	void setUniformMatrix2fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix2fv(program_,location,count,transpose,value);
	}

	void setUniformMatrix3fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix3fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix4fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix4fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix2x3fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix2x3fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix3x2fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix3x2fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix2x4fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix2x4fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix4x2fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix4x2fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix3x4fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix3x4fv(program_, location, count, transpose, value);
	}

	void setUniformMatrix4x3fv(
		GLint location,
		GLsizei count,
		GLboolean transpose,
		const GLfloat *value) {
		glProgramUniformMatrix4x3fv(program_, location, count, transpose, value);
	}

};

}


#endif


