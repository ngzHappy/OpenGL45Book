

#ifndef __functionvarray____OPENGL__API__PRIVATE__0x00
#define __functionvarray____OPENGL__API__PRIVATE__0x00

#include <string>
#include "VertexArrayType.hpp"

namespace gl {//gl

/*
void glGenVertexArrays(	GLsizei n,GLuint *arrays);
*/
inline void genVertexArrays(SizeInteger n,
                VertexArrayObject *arrays){
    glGenVertexArrays(n,(GLuint *)arrays);
}

/* error!! this function dose not exists */
extern void genVertexArrays(SizeInteger,NamedVertexArrayObject *);
	

/*
void glCreateVertexArrays(	GLsizei n,
    GLuint *arrays);
*/
inline void createVertexArrays(GLsizei n,NamedVertexArrayObject *arrays ){
    glCreateVertexArrays(n,(GLuint *)arrays);
}

/*
void glDeleteVertexArrays(	GLsizei n,const GLuint *arrays);
*/
inline void deleteVertexArrays(
        SizeInteger n,
        const VertexArrayObject *arrays){
    glDeleteVertexArrays(n,(GLuint *)arrays);
}


/*
void glBindVertexArray(	GLuint array);
*/
inline void bindVertexArray(const VertexArrayObject & array){
    glBindVertexArray( (GLuint)(array) );
}

/* 应该足够用了 */
enum class VertexAttribIndex : UnsignedInteger{
    Value0,Value1,Value2,Value3,Value4,Value5,Value6,Value7,Value8,Value9,Value10,
    Value11,Value12,Value13,Value14,Value15,Value16,Value17,Value18,Value19,Value20,Value21,
    Value22,Value23,Value24,Value25,Value26,Value27,Value28,Value29,Value30,Value31,Value32,
    Value33,Value34,Value35,Value36,Value37,Value38,Value39,Value40,Value41,Value42,Value43,
    Value44,Value45,Value46,Value47,Value48,Value49,Value50,Value51,Value52,Value53,Value54,
    Value55,Value56,Value57,Value58,Value59,Value60,Value61,Value62,Value63,Value64,Value65,
    Value66,Value67,Value68,Value69,Value70,Value71,Value72,Value73,Value74,Value75,Value76,
    Value77,Value78,Value79,Value80,Value81,Value82,Value83,Value84,Value85,Value86,Value87,
    Value88,Value89,Value90,Value91,Value92,Value93,Value94,Value95,Value96,Value97,Value98,
    Value99,Value100,Value101,Value102,Value103,Value104,Value105,Value106,Value107,Value108,Value109,
    Value110,Value111,Value112,Value113,Value114,Value115,Value116,Value117,Value118,Value119,Value120,
    Value121,Value122,Value123,Value124,Value125,Value126,Value127,Value128,Value129,Value130,Value131,
    Value132,Value133,Value134,Value135,Value136,Value137,Value138,Value139,Value140,Value141,Value142,
    Value143,Value144,Value145,Value146,Value147,Value148,Value149,Value150,Value151,Value152,Value153,
    Value154,Value155,Value156,Value157,Value158,Value159,Value160,Value161,Value162,Value163,Value164,
    Value165,Value166,Value167,Value168,Value169,Value170,Value171,Value172,Value173,Value174,Value175,
    Value176,Value177,Value178,Value179,Value180,Value181,Value182,Value183,Value184,Value185,Value186,
    Value187,Value188,Value189,Value190,Value191,Value192,Value193,Value194,Value195,Value196,Value197,
    Value198,Value199,Value200,Value201,Value202,Value203,Value204,Value205,Value206,Value207,Value208,
};

inline void enableVertexAttribArray(VertexAttribIndex index){
    glEnableVertexAttribArray((UnsignedInteger)index);
}
inline void disableVertexAttribArray(VertexAttribIndex index){
    glDisableVertexAttribArray((UnsignedInteger)index);
}


enum class VertexAttribPointerType:GLenum{
        BYTE                        = GL_BYTE,
        UNSIGNED_BYTE               = GL_UNSIGNED_BYTE,
        SHORT                       = GL_SHORT,
        UNSIGNED_SHORT              = GL_UNSIGNED_SHORT,
        INT                         = GL_INT,
        UNSIGNED_INT                = GL_UNSIGNED_INT,
        HALF_FLOAT                  = GL_HALF_FLOAT,
        FLOAT                       = GL_FLOAT,
        DOUBLE                      = GL_DOUBLE,
        FIXED                       = GL_FIXED,
        INT_2_10_10_10_REV          = GL_INT_2_10_10_10_REV,
        UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
        UNSIGNED_INT_10F_11F_11F_REV= GL_UNSIGNED_INT_10F_11F_11F_REV,
};
/*
void glVertexAttribPointer(	GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const GLvoid * pointer);

GL_BYTE
GL_UNSIGNED_BYTE,
GL_SHORT
GL_UNSIGNED_SHORT,
GL_INT
GL_UNSIGNED_INT
GL_HALF_FLOAT
GL_FLOAT
GL_DOUBLE
GL_FIXED
GL_INT_2_10_10_10_REV
GL_UNSIGNED_INT_2_10_10_10_REV
GL_UNSIGNED_INT_10F_11F_11F_REV

*/
inline void vertexAttribPointer(
	VertexAttribIndex index,
    SizeIntegerValue  size       =SizeIntegerValue::Four,
	VertexAttribPointerType type =VertexAttribPointerType::FLOAT,
    Boolean normalized           =false,
    SizeInteger stride           =0,
    const Void * pointer         =0){
glVertexAttribPointer(
	(UnsignedInteger)index,
	(GLint)size,
	(GLenum)type,
	normalized,
	stride,
	pointer);
}

}//~gl

#endif
