

#ifndef __PRIVATE__COMPUTE__SHADER__LOADER__0x00__
#define __PRIVATE__COMPUTE__SHADER__LOADER__0x00__



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

static inline Program CProgramLoadSources (
        const std::string & cFile
        ){


    if ( cFile.empty()) { return Program(); }

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
            std::array<GLuint, 1> data ;
            ShaderFree() {
                data[0] = 0;
            }
            ~ShaderFree() {
                glDeleteShader(data[1]);
            }
        }shaders;

        GLuint * shader = &(shaders.data[0]);

        {//1
            shader[0] = glCreateShader(GL_VERTEX_SHADER);
            if (0 == (shader[0])) {
                printError("GL_VERTEX_SHADER not surported!");
                return Program();
            }

        }//1

        {//2
            const GLchar * sources[] = {cFile.c_str()  };
            GLint lengths[] = {
                (GLint)(cFile.size())
            };

            glShaderSource(shader[0], 1, &sources[0], &lengths[0]);

            glCompileShader(shader[0]);

        }//2

        {//3
            GLint testVal;
            glGetShaderiv(shader[0], GL_COMPILE_STATUS, &testVal);
            if (testVal == GL_FALSE) {
                printErrorDetail(shader[0]);
                return Program();
            }

        }//3

        GLuint program = glCreateProgram();
        if (program == 0) {
            printError("can not create program!");
            return Program();
        }

        glAttachShader(program, shader[0]);
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

static inline Program CProgamLoad(
        const std::string & c_name
        ){
    std::string cFile;

    //30K
    cFile.reserve(1024*30);

    {
        std::ifstream ifs(c_name);
        if(false==ifs.is_open()){return Program();}
        std::string line;
        std::getline(ifs, line);
        typedef   std::string::value_type VType;
        if ((line.size()>=3)&&(line[0]== VType(0xef)) && (line[1] == VType(0xbb)) && (line[2] == VType(0xbf))) {
            cFile += std::string(line.begin()+3,line.end()) + "\n";
        }
        else {
            cFile += line + "\n";
        }
        while (std::getline(ifs,line)) {
            cFile+=line+"\n";
        }
    }



    return CProgramLoadSources(cFile );
}

#ifdef QT_CORE_LIB


static inline Program CProgamLoad(const QString & c_fileName){
    return CProgamLoad( c_fileName.toLocal8Bit().toStdString() );
}

static inline Program CProgramLoadSources(const QString & cFile){
    return CProgramLoadSources(cFile.toUtf8().toStdString());
}


#endif


}




#endif

