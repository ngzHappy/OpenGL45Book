#ifndef __SAMPLE_fun_OBJECT__H__0x00__
#define __SAMPLE_fun_OBJECT__H__0x00__

#include "SamplerObject.hpp"


namespace gl {

void createSamplers(GLsizei n,NamedSamplerObject * samplers){
    glCreateSamplers( n, (GLuint *)samplers);
}

void deleteSamplers(GLsizei n,const NamedSamplerObject * samplers){
    glDeleteSamplers(n,(const GLuint *)samplers);
}

void genSamplers(GLsizei n, SamplerObject * samplers){
    glGenSamplers(n,(GLuint *)samplers);
}

void deleteSamplers(GLsizei n,const SamplerObject * samplers){
    glDeleteSamplers(n,(const GLuint *)samplers);
}


}



#endif




