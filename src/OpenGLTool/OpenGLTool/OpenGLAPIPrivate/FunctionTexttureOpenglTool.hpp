#ifndef __FUNCTION__OPENGL__TOOL_TXETURE__0x00
#define __FUNCTION__OPENGL__TOOL_TXETURE__0x00

#include "TexttureOpenglTool.hpp"
#include "../QGLTools.hpp"
#include <memory>

#ifdef QT_CORE_LIB
#include <QImage>
#include <QString>
#include <QuaZip/quazip.h>
#include <QuaZip/quazipfile.h>
#include <string>
#include <sstream>
#include <vector>
#include <QImageReader>

#endif

namespace gl{

/*
void glGenTextures(	GLsizei n,
GLuint * textures);
*/
static inline void genTextures(SizeInteger n, Texture * textures){
    glGenTextures(n, (GLuint *)textures);
}
enum class CreateTexturesTarget:GLenum{
    TEXTURE_1D = GL_TEXTURE_1D,
    TEXTURE_2D = GL_TEXTURE_2D,
    TEXTURE_3D = GL_TEXTURE_3D,
    TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
    TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
    TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
    TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
    TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
    TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
    TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
    TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
};

/*
void glCreateTextures(	GLenum target,
    GLsizei n,
    GLuint *textures);
*/
inline void createTextures(	CreateTexturesTarget target,
                        GLsizei n,
                        NamedTexture *textures){
    glCreateTextures(GLenum(target),n,(GLuint *)textures);
}
/* 创建一个texture */
inline void createTexture(
        NamedTexture *textures,
        CreateTexturesTarget target = CreateTexturesTarget::TEXTURE_2D
        ){
    glCreateTextures(GLenum(target),1,(GLuint *)textures);
}

/*
void glDeleteTextures(	GLsizei n,
const GLuint * textures);
*/
	static inline void deleteTextures(SizeInteger n,const Texture * textures){
		glDeleteTextures(n, (const GLuint *)textures);
	}
enum class BindTextureTarget:GLenum{
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_3D = GL_TEXTURE_3D,
	TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
	TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
	TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
	TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
};
/*
void glBindTexture(	GLenum target,
GLuint texture);
GL_TEXTURE_1D
GL_TEXTURE_2D
GL_TEXTURE_3D
GL_TEXTURE_1D_ARRAY
GL_TEXTURE_2D_ARRAY
GL_TEXTURE_RECTANGLE
GL_TEXTURE_CUBE_MAP
GL_TEXTURE_CUBE_MAP_ARRAY
GL_TEXTURE_BUFFER
GL_TEXTURE_2D_MULTISAMPLE 
GL_TEXTURE_2D_MULTISAMPLE_ARRAY
*/
static inline void bindTexture(
	BindTextureTarget target,
	Texture texture
	){
	glBindTexture((GLenum)target, (GLuint)texture);
}

/**/
#ifdef QT_CORE_LIB

	static inline Texture genTexture2D(
        QImage image ,
        GLenum tar = GL_TEXTURE_2D
		){
		Texture ans;
        if(image.isNull()){return ans;}
        image = QGLTools::project(image);
        if(image.width()<=0||image.height()<=0){return ans;}
		GLuint texture = 0;
		glGenTextures(1, &texture);
		if (0 == texture){ return ans; }
        glBindTexture(tar,texture);
        glTexParameteri(tar, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(tar, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(tar, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
        glTexParameteri(tar, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
		glTexImage2D(
            tar, 0, GL_RGBA,
			image.width(), image.height(), 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
		return Texture(texture);
	}

    static inline NamedTexture createTexture2D(
        QImage  image ,
        GLenum tar = GL_TEXTURE_2D
        ){
        NamedTexture ans;
        if(image.isNull()){return ans;}
        image = QGLTools::project(image);
		const int width = image.width();
		const int height = image.height();
        if(width<=0){return ans;}
        if(height<=0){return ans;}
        GLuint texture = 0;
        glCreateTextures(tar,1, &texture);
        if (0 == texture){ return ans; } 
		glTextureStorage2D(
			texture, 1, GL_RGBA8, width,  height 
             );
		glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
		//glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
		glTextureSubImage2D(
			texture,0,
			0, 0,  width ,  height ,
			GL_RGBA, GL_UNSIGNED_BYTE, image.bits()
			);

        return NamedTexture(texture);
    }

	static inline Texture genTexture2D(
		const QString & fileName,
		GLenum tar = GL_TEXTURE_2D
		) {
		return genTexture2D(std::move(QImage(fileName)) , tar );
	}

	static inline NamedTexture createTexture2D(
		const QString & fileName,
		GLenum tar = GL_TEXTURE_2D
		) {
		return createTexture2D(std::move(QImage(fileName)),tar );
	}

	static inline NamedTexture createTexture2DArray(
		const QString zipFileName,
		GLenum tar = GL_TEXTURE_2D_ARRAY
		) {
		QuaZip zip( zipFileName );
		if (false == zip.open(QuaZip::mdUnzip)) { return NamedTexture(); }
		
		int width = 0;
		int height = 0;
		int imageNum = 0;

		{
			if (zip.setCurrentFile("info.txt")==false) { return NamedTexture(); };
			QuaZipFile file(&zip);
			if (file.open(QFile::ReadOnly)==false) { return NamedTexture(); }
			
			{
				QByteArray temp = file.readAll();
				std::stringstream ss( temp.toStdString() );
				ss >> width   ;
				ss >> height  ;
				ss >> imageNum;
			}

			if (width <= 0) { return NamedTexture(); }
			if (height <= 0) { return NamedTexture(); }
			if (imageNum <= 0) { return NamedTexture(); }
		}

		std::vector< std::uint32_t > pool;
		const int size_ = width*height;
		pool.reserve( size_*imageNum  );
		if ( zip.goToFirstFile() && (int(pool.size())<size_*imageNum) ) {
			do {
				if (zip.getCurrentFileName() == "info.txt") { continue; }
				QuaZipFile file(&zip);
				if (file.open(QFile::ReadOnly) == false) { return NamedTexture(); }
				QImageReader ireader(&file );
				//ireader.setAutoTransform(true);
				//ireader.setAutoDetectImageFormat(true);
				//ireader.setBackgroundColor(QColor(0,0,0,0));
				QImage image ;
				ireader.read(&image) ;
				if (image.width() != width) { continue ; }
				if (image.height() != height ) { continue ; }
				image = QGLTools::project(image);
				auto begin_ = (std::uint32_t *)(image.bits());
				for (int i = 0; i < size_;++i) {
					pool.push_back(*begin_);
					++begin_;
				}
			} while (zip.goToNextFile());
		}

		if (int(pool.size())<size_*imageNum) { 
			return NamedTexture();
		}
		else {
			GLuint texture = 0;
			glCreateTextures(tar, 1, &texture);
			if (0 == texture) { return NamedTexture();}
			glTextureStorage3D(texture, 1, GL_RGBA8, width, height, imageNum);
			//glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
			//glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTextureSubImage3D(texture, 0, 0, 0, 0, width, height, imageNum,
				GL_RGBA, GL_UNSIGNED_BYTE,pool.data());
			return NamedTexture(texture);
		}

		return NamedTexture();
	}

#endif
}

#endif
