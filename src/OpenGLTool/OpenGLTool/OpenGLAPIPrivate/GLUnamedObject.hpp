#ifdef _MSC_VER
#pragma warning(disable:4819)   
#endif

#ifndef __GL__UN__NAMED__OBJECT__0x00__
#define __GL__UN__NAMED__OBJECT__0x00__

#include "GLUnamedObject.hxx"
#include "ProgramType.hpp"

namespace gl {
 
class UnNamedObject{
public:
    static void useProgram(const gl::Program & p){p.use();}
 
    template<typename T>
    static gl::Program::AtomicFunctions<T>
    useProgram(const Program &p ,T   locker){
        return std::move( p.use(locker) );
    }
 
};

class UnNamedDrawObject :
        public UnNamedObject,
        public __UnNamedObject
{
public:

};

}


#endif


