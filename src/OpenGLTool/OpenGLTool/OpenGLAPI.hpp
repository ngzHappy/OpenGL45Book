#ifndef  __OPENGL_1_API__HPP__0x00
#define  __OPENGL_1_API__HPP__0x00

#include <utility>
#include "OpenGLAPIPrivate/OpenGLBase.hpp"
#include "OpenGLAPIPrivate/BaseType.hpp"
#include "OpenGLAPIPrivate/ProgramType.hpp"
#include "OpenGLAPIPrivate/ProgramFunction.hpp"
#include "OpenGLAPIPrivate/BufferFunction.hpp"
#include "OpenGLAPIPrivate/BufferType.hpp"
#include "OpenGLAPIPrivate/GlobalFunctionOpengl.hpp"
#include "OpenGLAPIPrivate/VertexArrayFunction.hpp"
#include "OpenGLAPIPrivate/VertexArrayType.hpp"
#include "OpenGLAPIPrivate/DrawFunctions.hpp"
#include "OpenGLAPIPrivate/PointsOpengl.hpp"
#include "OpenGLAPIPrivate/FunctionTexttureOpenglTool.hpp"
#include "OpenGLAPIPrivate/TexttureOpenglTool.hpp"
#include "OpenGLAPIPrivate/IsFinishedGL.hpp"
#include "OpenGLAPIPrivate/FBOFunctionGL.hpp"
#include "OpenGLAPIPrivate/FBOTypeGL.hpp"
#include "OpenGLAPIPrivate/QGLDebugTool.hpp"
#include "OpenGLAPIPrivate/TextureRender.hpp"
#include "OpenGLAPIPrivate/MultiSampleTextureRender.hpp"
#include "OpenGLAPIPrivate/DispatchCompute.hpp"

namespace gl {

inline std::pair<Integer,Integer> getVersion(){
    std::pair<Integer,Integer> ans;
    glGetIntegerv(GL_MAJOR_VERSION, &(ans.first));
    glGetIntegerv(GL_MINOR_VERSION, &(ans.second));
    return ans;
}

inline void deleteAny(const Program & v ){
    deleteProgram(v);
}
inline void deleteAny(const Buffer & v ){
    deleteBuffers(1,&v);
}
inline void deleteAny(const Texture & v){
	deleteTextures(1,&v);
}
inline void deleteAny(const VertexArrayObject & v ){
    deleteVertexArrays(1,&v);
}
inline void deleteAny(const NamedBuffer & v ){
    deleteBuffers(1,&v);
}
inline void deleteAny(const NamedTexture & v){
    deleteTextures(1,&v);
}
inline void deleteAny(const NamedVertexArrayObject & v ){
    deleteVertexArrays(1,&v);
}
inline void deleteAny(const NamedFrameBufferObject & v){
    deleteFramebuffers(1,&v);
}
inline void deleteAny(const FrameBufferObject & v){
    deleteFramebuffers(1,&v);
}
template<typename T0 , typename ... Args>
inline void deleteAny( const T0 & a0,  const Args &...args) {
	deleteAny(a0);
	deleteAny(args...);
}

}


#endif

