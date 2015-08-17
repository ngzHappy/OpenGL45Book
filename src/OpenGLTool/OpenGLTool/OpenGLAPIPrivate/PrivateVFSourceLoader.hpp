
#ifndef __program__VF__SOURCE__LOADER__p0x00
#define __program__VF__SOURCE__LOADER__p0x00

#include "ProgramFunction.hpp"
#include <memory>
#ifdef QT_CORE_LIB
#include <QString>
#endif
#include <string>
#include <fstream>
#include <array> 
#include <iostream>

namespace gl {

/*
 * return 0 is error!
*/
static inline Program VFProgramLoadSources (
        const std::string & vFile,
        const std::string & fFile
        ){


    if (fFile.empty() || vFile.empty()) { return Program(); }

	{//0
        auto printProgramInfo=[](GLuint e){

            GLint log_length;
            glGetProgramiv(e, GL_INFO_LOG_LENGTH, &log_length);
            log_length+=16;

            typedef void( *DFunction)(char *);
            std::unique_ptr<char, DFunction> infos_(
                new char[log_length],
                [](char * d){delete[]d; }
            );

            char * info = infos_.get() ;

            glGetProgramInfoLog(e, 1024, NULL, info);
            std::cout << info << std::endl;
            std::cout.flush();
        };
        auto printError = [](const std::string & err) {
			std::cout << err << std::endl;
			std::cout.flush();
		};
		auto printErrorDetail =[](GLuint e){
			typedef void( *DFunction)(char *);

            GLint log_length;
            glGetShaderiv(e, GL_INFO_LOG_LENGTH, &log_length);
            log_length+=16;

			std::unique_ptr<char, DFunction> infos_(
                new char[log_length],
				[](char * d){delete[]d; }
			);
			char * info = infos_.get() ;
            glGetShaderInfoLog(e, log_length, NULL, info);
			std::cout << info << std::endl;
			std::cout.flush();
		};

		class ShaderFree{
		public:
			std::array<GLuint, 2> data ;
			ShaderFree() {
				data[0] = 0;
				data[1] = 0;
			}
			~ShaderFree() {
				glDeleteShader(data[1]);
				glDeleteShader(data[0]);
			}
		}shaders;

		GLuint * shader = &(shaders.data[0]);

		{//1
			shader[0] = glCreateShader(GL_VERTEX_SHADER);
			if (0 == (shader[0])) {
				printError("GL_VERTEX_SHADER not surported!");
                return Program();
			}

			shader[1] = glCreateShader(GL_FRAGMENT_SHADER);
			if (0 == (shader[1])) {
				printError("GL_FRAGMENT_SHADER not surported!");
                return Program();
			}
		}//1

		{//2
			const GLchar * sources[] = {vFile.c_str(),fFile.c_str() };
			GLint lengths[] = {
				(GLint)(vFile.size()),
				(GLint)(fFile.size())
			};

			glShaderSource(shader[0], 1, &sources[0], &lengths[0]);
			glShaderSource(shader[1], 1, &sources[1], &lengths[1]);

			glCompileShader(shader[0]);
			glCompileShader(shader[1]);

		}//2

		{//3
			GLint testVal;
			glGetShaderiv(shader[0], GL_COMPILE_STATUS, &testVal);
			if (testVal == GL_FALSE) {
				printErrorDetail(shader[0]);
                return Program();
			}
			glGetShaderiv(shader[1], GL_COMPILE_STATUS, &testVal);
			if (testVal == GL_FALSE) {
				printErrorDetail(shader[1]);
                return Program();
			}
		}//3

		GLuint program = glCreateProgram();
		if (program == 0) {
			printError("can not create program!");
            return Program();
		}

		glAttachShader(program, shader[0]);
		glAttachShader(program, shader[1]);
		glLinkProgram(program);

		{
			GLint testVal;
			glGetProgramiv(program, GL_LINK_STATUS, &testVal);
			if (testVal == GL_FALSE)
			{
                printProgramInfo(program);
				glDeleteProgram(program);
                return Program();
			}
		}

        return Program(program);
	}//0

    return Program();
}

static inline Program VFProgamLoad(
        const std::string & v_name,
        const std::string & f_name
        ){
    std::string vFile;
    std::string fFile;
    //30K
    vFile.reserve(1024*30);
    fFile.reserve(1024*30);

    {
        std::ifstream ifs(v_name);
        if(false==ifs.is_open()){return Program();}
        std::string line;
        std::getline(ifs, line);
        typedef   std::string::value_type VType;
        if ((line.size()>=3)&&(line[0]== VType(0xef)) && (line[1] == VType(0xbb)) && (line[2] == VType(0xbf))) {
            vFile += std::string(line.begin()+3,line.end()) + "\n";
        }
        else {
            vFile += line + "\n";
        }
        while (std::getline(ifs,line)) {
            vFile+=line+"\n";
        }
    }

    {
        std::ifstream ifs(f_name);
        if (false == ifs.is_open()) { return Program(); }
        std::string line;
        std::getline(ifs, line);
        typedef std::string::value_type VType;
        if ((line.size() >= 3) && (line[0] == VType(0x00ef)) && (line[1] == VType(0x00bb)) && (line[2] == VType(0x00bf))) {
            fFile += std::string(line.begin() + 3, line.end()) + "\n";
        }
        else {
            fFile += line + "\n";
        }
        while (std::getline(ifs, line)) {
            fFile += line + "\n";
        }
    }

    return VFProgramLoadSources(vFile,fFile);
}

static inline Program VFProgramLoadSources (
        const char *  vFile,
        const char * fFile
        ){
     return VFProgramLoadSources(std::string(vFile),std::string(fFile));
}

#ifdef QT_CORE_LIB
static inline Program VFProgamLoad(
        const QString & v_name,
        const QString & f_name
        ){
    const auto v = std::move( v_name.toLocal8Bit().toStdString() );
    const auto f = std::move( f_name.toLocal8Bit().toStdString() );
    return VFProgamLoad(v,f);
}

static inline Program VFProgramLoadSources (
        const QString & vFile,
        const QString & fFile
        ){
    std::string vf ,ff;
    vf = std::move( vFile.toUtf8().toStdString() );
    ff = std::move( fFile.toUtf8().toStdString() );
    return VFProgramLoadSources(vf,ff);
}

#endif

}

#endif
