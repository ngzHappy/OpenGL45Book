#ifndef __IS__OPENGL__FINISHED__0x00
#define __IS__OPENGL__FINISHED__0x00

#include "BaseType.hpp"
#include <memory>

namespace gl {

class IsGLFinished{

		class ThisData{
		public:
			GLsync sync = 0;
			volatile mutable bool is_end = false;
			ThisData(){ sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0); }
			~ThisData(){ glDeleteSync(sync); }
		};

		std::shared_ptr<ThisData> data;
		enum{TIME_OUT=0};
	public:
		IsGLFinished(){}
		bool begin(){
			if (data){ return false; }
			data = std::shared_ptr<ThisData>(new ThisData);
			return true;
		}
		void end() const{
			if (data){
				glFlush();
				glClientWaitSync(data->sync, GL_SYNC_FLUSH_COMMANDS_BIT, TIME_OUT);
				data->is_end = true;
			}
		}
		bool isFinished()const{ 
			if (data){
				if (data->is_end==false){
					this->end();
				}
				GLint result = GL_UNSIGNALED;
				glGetSynciv(data->sync, GL_SYNC_STATUS, sizeof(result), 0, &result);
				return (result == GL_SIGNALED);
			}
			return true; 
		}

        explicit operator bool()const{ return this->isFinished(); }
	};

}//~namespace gl

#endif
