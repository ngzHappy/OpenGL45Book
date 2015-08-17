#ifndef __FUNCTION__FBO__HPP__0x00
#define __FUNCTION__FBO__HPP__0x00

#include "FBOTypeGL.hpp"
#include "TexttureOpenglTool.hpp"
#include <memory>
#include <iostream>

namespace gl{



/*	void glCreateFramebuffers(GLsizei n,
		GLuint *ids);
*/
    inline void createFrameBuffers(SizeInteger n ,NamedFrameBufferObject * ids ){
        glCreateFramebuffers(n,(GLuint *)ids);
    }
/*
void glGenFramebuffers(	GLsizei n,
    GLuint *ids);
*/
    inline void genFramebuffers(SizeInteger n ,  FrameBufferObject * ids){
        glGenFramebuffers( n,(GLuint *)ids );
    }
/*
void glDeleteFramebuffers(	GLsizei n,
    GLuint *framebuffers);
*/
    inline void deleteFramebuffers(SizeInteger n ,const FrameBufferObject * ids){
        glDeleteFramebuffers(n,(GLuint *)ids);
    }


    class DefaultFrameBufferObject{
    private:
        class Data{
        public:
            int width                  = 0;
            int height                 = 0;
            GLuint renderBuffer        = 0;
            GLuint frameBuffer         = 0;
            GLuint depthBuffer         = 0;
            bool isFramebufferComplete = false;
            ~Data(){
                glDeleteFramebuffers(1,&frameBuffer);
                glDeleteTextures(1,&renderBuffer);
                glDeleteTextures(1,&depthBuffer);
            }
        } ;
        std::shared_ptr<Data> data;
    private:
        void init_frame_buffer(std::shared_ptr<Data> td){
            Data & d = *(td.get());

            glCreateFramebuffers(1,&(d.frameBuffer));
            if(0==d.frameBuffer){return;}
            glCreateTextures( GL_TEXTURE_RECTANGLE,1,&(d.renderBuffer));
            glCreateTextures( GL_TEXTURE_RECTANGLE,1,&(d.depthBuffer ));
            if(0==d.renderBuffer){return;}
            if(0==d.depthBuffer){return;}

            glTextureParameteri(d.depthBuffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(d.depthBuffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(d.renderBuffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(d.renderBuffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTextureStorage2D( d.renderBuffer,
                                    1, GL_RGBA32F,
                                     d.width,d.height  );
            glTextureStorage2D(
                        d.depthBuffer,
                        1,GL_DEPTH_COMPONENT32F,d.width,d.height
                        );

            glNamedFramebufferTexture(
                        d.frameBuffer,
                        GL_COLOR_ATTACHMENT0,
                        d.renderBuffer,0//??
                        );
            glNamedFramebufferTexture(
                        d.frameBuffer,
                        GL_DEPTH_ATTACHMENT,
                        d.depthBuffer,0//??
                        );

            GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
            glNamedFramebufferDrawBuffers(
                    d.frameBuffer,
                    1,drawBuffers);
            //check
            GLenum fboStatus = glCheckNamedFramebufferStatus(
                        d.frameBuffer,
                        GL_DRAW_FRAMEBUFFER);
            if (fboStatus!=GL_FRAMEBUFFER_COMPLETE){
                d.isFramebufferComplete = false;
                switch ( fboStatus )
                {
					 case GL_FRAMEBUFFER_UNDEFINED: std::cout << "GL_FRAMEBUFFER_UNDEFINED"; break;
					 case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
					 case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
					 case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
					 case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
					 case GL_FRAMEBUFFER_UNSUPPORTED:std::cout << "GL_FRAMEBUFFER_UNSUPPORTED"; break;
					 case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
					 case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
					 default:
                    break;
                }
                std::cout<<std::endl;
                std::cout.flush();
                return ;
            }
            else{
                d.isFramebufferComplete = true;
            }

            data = td;
        }
    public:
		class NULLType{};
        explicit operator bool()const{return bool(data);}

        DefaultFrameBufferObject(int width,int height){
            if(width<=0){return;}
            if(height<=0){return;}
            std::shared_ptr<Data> temp_data = std::shared_ptr<Data>(new Data);
            temp_data->width = width ;
            temp_data->height = height ;
            init_frame_buffer( std::move(temp_data) );
        }
        DefaultFrameBufferObject( ){}

        int width()const{
			if (data)return data->width;
			return 0;
		}
        int height()const{
			if(data)return data->height;
			return 0;
		}
        NamedFrameBufferObject frameBuffer()const{
            if(data)return NamedFrameBufferObject(data->frameBuffer);
			return NamedFrameBufferObject(0);
        }
		NamedTexture renderBuffer()const{
			if(data)return NamedTexture(data->renderBuffer);
			return NamedTexture(0);
		}
		NamedTexture depthBuffer()const{
			if(data)return NamedTexture(data->depthBuffer);
			return NamedTexture(0);
		}
    };

/*
 * 创建一个默认的FBO 具有一个深度缓冲区
*/
    static inline DefaultFrameBufferObject
    createDefaultFrameBuffer(int width,int height){
        if(width<=0){return DefaultFrameBufferObject( );}
        if(height<=0){return DefaultFrameBufferObject( );}
        return DefaultFrameBufferObject(width,height);
    }


    class DefaultMultiSampleFrameBufferObject{
    private:
        class Data{
        public:
            int width                  = 0;
            int height                 = 0;
            GLuint renderBuffer        = 0;
            GLuint frameBuffer         = 0;
            GLuint depthBuffer         = 0;
            GLint  samples             = 0;
            bool isFramebufferComplete = false;
            ~Data(){
                glDeleteFramebuffers(1,&frameBuffer);
                glDeleteTextures(1,&renderBuffer);
                glDeleteTextures(1,&depthBuffer);
            }
        } ;
        std::shared_ptr<Data> data;
    private:
        void init_frame_buffer(std::shared_ptr<Data> td){
            Data & d = *(td.get());

            glCreateFramebuffers(1,&(d.frameBuffer));
            if(0==d.frameBuffer){return;}

            glCreateTextures( GL_TEXTURE_2D_MULTISAMPLE,1,&(d.renderBuffer));
            glCreateTextures( GL_TEXTURE_2D_MULTISAMPLE,1,&(d.depthBuffer ));
            if(0==d.renderBuffer){return;}
            if(0==d.depthBuffer){return;}

            glTextureParameteri(d.depthBuffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(d.depthBuffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(d.renderBuffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(d.renderBuffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTextureStorage2DMultisample( 
				d.renderBuffer,
                d.samples , 
				GL_RGBA32F ,
                d.width,
				d.height,
				false /*??*/  
				);

			glTextureStorage2DMultisample(
				d.depthBuffer,
				d.samples,
				GL_DEPTH_COMPONENT32F,
				d.width,
				d.height,
				false /*??*/
				);     
			
            glNamedFramebufferTexture(
                        d.frameBuffer,
                        GL_DEPTH_ATTACHMENT,
                        d.depthBuffer,0/* ?? */ 
                        );

			glNamedFramebufferTexture(
				d.frameBuffer,
				GL_COLOR_ATTACHMENT0,
				d.renderBuffer, 0 /* ?? */
				);
									            
            //check
            GLenum fboStatus = glCheckNamedFramebufferStatus(
                        d.frameBuffer,
                        GL_DRAW_FRAMEBUFFER);
		 
            if (fboStatus!=GL_FRAMEBUFFER_COMPLETE){
                d.isFramebufferComplete = false;
                switch ( fboStatus )
                {
                     case GL_FRAMEBUFFER_UNDEFINED: std::cout << "GL_FRAMEBUFFER_UNDEFINED"; break;
                     case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
                     case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
                     case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
                     case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
                     case GL_FRAMEBUFFER_UNSUPPORTED:std::cout << "GL_FRAMEBUFFER_UNSUPPORTED"; break;
                     case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
                     case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:std::cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
                     default:
                    break;
                }
                std::cout<<std::endl;
                std::cout.flush();
                return ;
            }
            else{
                d.isFramebufferComplete = true;
            }

            data = td;
        }
    public:
        class NULLType{};
        explicit operator bool()const{return bool(data);}

        DefaultMultiSampleFrameBufferObject(int width,int height,int samples){
            if(width<=0){return;}
            if(height<=0){return;}
            if(samples<=0){return;}
            std::shared_ptr<Data> temp_data = std::shared_ptr<Data>(new Data);
            temp_data->width = width ;
            temp_data->height = height ;
            temp_data->samples = samples ;
            init_frame_buffer( std::move(temp_data) );
        }
        DefaultMultiSampleFrameBufferObject( ){}

        GLint  samples()const{
            if(data){return data->samples;}
            return 0;
        }
        int width()const{
            if (data)return data->width;
            return 0;
        }
        int height()const{
            if(data)return data->height;
            return 0;
        }
        NamedFrameBufferObject frameBuffer()const{
            if(data)return NamedFrameBufferObject(data->frameBuffer);
            return NamedFrameBufferObject(0);
        }
        NamedTexture renderBuffer()const{
            if(data)return NamedTexture(data->renderBuffer);
            return NamedTexture(0);
        }
        NamedTexture depthBuffer()const{
            if(data)return NamedTexture(data->depthBuffer);
            return NamedTexture(0);
        }
    };

    static inline DefaultMultiSampleFrameBufferObject
    createDefaultFrameBuffer(int width,int height,int samples){
        if(width<=0){return DefaultMultiSampleFrameBufferObject( );}
        if(height<=0){return DefaultMultiSampleFrameBufferObject( );}
        if(samples<=0){return DefaultMultiSampleFrameBufferObject( );}
        return DefaultMultiSampleFrameBufferObject(width,height,samples);
    }

}

#endif
