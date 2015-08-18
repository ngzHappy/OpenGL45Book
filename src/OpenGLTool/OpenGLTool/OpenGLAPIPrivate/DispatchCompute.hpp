#ifndef __DISPATH__GL__0x00__
#define __DISPATH__GL__0x00__

#include "BaseType.hpp"
#include "GLUnamedObject.hpp"

namespace gl {

/*

void glDispatchCompute(
GLuint num_groups_x,
GLuint num_groups_y,
GLuint num_groups_z);
*/

void disPatchCompute(
        GLuint num_groups_x=1,
        GLuint num_groups_y=1,
        GLuint num_groups_z=1 ){
glDispatchCompute(
            num_groups_x,
            num_groups_y,
            num_groups_z
            );
}

namespace DisPatchCompute{

class Pack :
public UnNamedDrawObject{
public:
    GLuint num_groups_x;
    GLuint num_groups_y;
    GLuint num_groups_z;
    Pack():num_groups_x(1),
        num_groups_y(1),
        num_groups_z(1){}
    Pack(GLuint num_groups_x_ ,
         GLuint num_groups_y_=1,
         GLuint num_groups_z_=1 ):
        num_groups_x(num_groups_x_),
        num_groups_y(num_groups_y_),
        num_groups_z(num_groups_z_){
    }
};

void disPatch(const Pack & pack){
    glDispatchCompute(pack.num_groups_x,
                      pack.num_groups_y,
                      pack.num_groups_z);
}

}

void disPatch(const DisPatchCompute::Pack & pack){
    gl::DisPatchCompute::disPatch(pack);
}
void dispatch(const DisPatchCompute::Pack & pack){
    gl::DisPatchCompute::disPatch(pack);
}

}//gl


#endif

