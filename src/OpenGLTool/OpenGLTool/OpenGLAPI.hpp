#ifndef  __OPENGL_1_API__HPP__0x00
#define  __OPENGL_1_API__HPP__0x00

#include <utility>
#include <memory>
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
#include "OpenGLAPIPrivate/SamplerObject.hpp"
#include "OpenGLAPIPrivate/SamplerObjectFunction.hpp"

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
inline void deleteAny(const SamplerObject & v) {
	deleteSamplers(1, &v);
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

inline void deleteAny(const NamedSamplerObject & v){
    deleteSamplers(1,&v);
}

template<typename T0 , typename ... Args>
inline void deleteAny( const T0 & a0,  const Args &...args) {
	deleteAny(a0);
	deleteAny(args...);
}

}

namespace gl {

	template<typename T>
	class ObjectPointer  : 
		public  std::unique_ptr<T, void(*)(T*)>{
		typedef std::unique_ptr<T, void(*)(T*)> SuperType;
	public:
		ObjectPointer() :SuperType(
			nullptr, 
			[](T*) {}) {}
		using SuperType::SuperType;
		static void deleteObjectFunction(T * d) {
			if (d == 0) { return; }
			gl::deleteAny(*d);
			delete d;
		}

		const T & operator*() const { return SuperType::operator*(); }
		const T & operator*() { return SuperType::operator*(); }
	private:
		
	};

	template<typename T,typename ... Args>  ObjectPointer<T> create( Args... );
	
	template<> ObjectPointer<NamedBuffer> 
		create<NamedBuffer>() {
		typedef ObjectPointer<NamedBuffer> T;
		typedef T::element_type element_type;
		T ans(new element_type,&T::deleteObjectFunction);
		gl::createBuffers(1, ans.get());
		return std::move(ans);
	}

	template<> ObjectPointer<NamedTexture> 
		create<NamedTexture, gl::CreateTexturesTarget>( gl::CreateTexturesTarget tar ) {
		typedef ObjectPointer<NamedTexture> T;
		typedef T::element_type element_type;
		T ans(new element_type, &T::deleteObjectFunction);
		gl::createTextures(tar,1, ans.get());
		return std::move(ans);
	}

	template<> ObjectPointer<NamedSamplerObject> 
		create<NamedSamplerObject>() {
		typedef ObjectPointer<NamedSamplerObject> T;
		typedef T::element_type element_type;
		T ans(new element_type, &T::deleteObjectFunction);
		gl::createSamplers(1, ans.get());
		return std::move(ans);
	}

	template<> ObjectPointer<NamedVertexArrayObject> 
		create<NamedVertexArrayObject>() {
		typedef ObjectPointer<NamedVertexArrayObject> T;
		typedef T::element_type element_type;
		T ans(new element_type, &T::deleteObjectFunction);
		gl::createVertexArrays(1, ans.get());
		return std::move(ans);
	}

	template<> ObjectPointer<Program> 
		create<Program, Program>(Program program) {
		typedef ObjectPointer<Program> T;
		typedef T::element_type element_type;
		T ans(new element_type(program), &T::deleteObjectFunction);
		return std::move(ans);
	}

	template<> ObjectPointer<NamedFrameBufferObject> 
		create<NamedFrameBufferObject>() {
		typedef ObjectPointer<NamedFrameBufferObject> T;
		typedef T::element_type element_type;
		T ans(new element_type, &T::deleteObjectFunction);
		gl::createFrameBuffers(1, ans.get());
		return std::move(ans);
	}

	typedef ObjectPointer<NamedFrameBufferObject> NamedFrameBufferObjectPointer;
	typedef ObjectPointer<Program> ProgramPointer;
	typedef ObjectPointer<NamedVertexArrayObject> NamedVertexArrayObjectPointer;
	typedef ObjectPointer<NamedSamplerObject> NamedSamplerObjectPointer;
	typedef ObjectPointer<NamedTexture> NamedTexturePointer;
	typedef ObjectPointer<NamedBuffer> NamedBufferPointer;

}

#endif

