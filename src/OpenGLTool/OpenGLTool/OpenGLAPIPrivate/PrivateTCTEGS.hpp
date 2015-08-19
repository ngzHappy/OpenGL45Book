#ifndef __TCTS__PRIVATE__HPP_g_0x00__
#define __TCTS__PRIVATE__HPP_g_0x00__

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

static inline Program VTCTEGFProgramLoadSources (
        const std::string & vFile,
        const std::string & tcFile,
        const std::string & teFile,
        const std::string & gFile,
        const std::string & fFile
        ){

    if (fFile.empty() || vFile.empty()) { return Program(); }
	if (tcFile.empty() || teFile.empty()) { return Program(); }
	if (gFile.empty() ) { return Program(); }

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

        enum{
            VS__=0,
            TC__=1,
            TE__=2,
			GS__=3,
            FS__=4
        };

        class ShaderFree{
        public:
            std::array<GLuint, 5> data ;
            ShaderFree() {
				data[2] = 0;
				data[4] = 0;
                data[0] = 0;
				data[3] = 0;
                data[1] = 0;
            }
            ~ShaderFree() {
                glDeleteShader(data[VS__]);
                glDeleteShader(data[TC__]);
                glDeleteShader(data[TE__]);
                glDeleteShader(data[FS__]);
				glDeleteShader(data[GS__]);
            }
        }shaders;



        GLuint * shader = &(shaders.data[0]);

        {//1
            shader[VS__] = glCreateShader(GL_VERTEX_SHADER);
            if (0 == (shader[VS__])) {
                printError("GL_VERTEX_SHADER not surported!");
                return Program();
            }

            shader[TC__] = glCreateShader(GL_TESS_CONTROL_SHADER);
            if (0 == (shader[TC__])) {
                printError("GL_TESS_CONTROL_SHADER not surported!");
                return Program();
            }

            shader[TE__] = glCreateShader(GL_TESS_EVALUATION_SHADER);
            if (0 == (shader[TE__])) {
                printError("GL_TESS_EVALUATION_SHADER not surported!");
                return Program();
            }

            shader[FS__] = glCreateShader(GL_FRAGMENT_SHADER);
            if (0 == (shader[FS__])) {
                printError("GL_FRAGMENT_SHADER not surported!");
                return Program();
            }

			shader[GS__] = glCreateShader(GL_GEOMETRY_SHADER);
			if (0 == (shader[GS__])) {
				printError("GL_GEOMETRY_SHADER not surported!");
				return Program();
			}
        }//1

        {//2
            const GLchar * sources[] = {
                vFile.c_str(),
                tcFile.c_str(),
                teFile.c_str(),
				gFile.c_str(),
                fFile.c_str() };

            GLint lengths[] = {
                (GLint)(vFile.size()),
                (GLint)(tcFile.size()),
                (GLint)(teFile.size()),
				(GLint)(gFile.size()),
                (GLint)(fFile.size())
            };

            glShaderSource(shader[0], 1, &sources[0], &lengths[0]);
            glShaderSource(shader[1], 1, &sources[1], &lengths[1]);
            glShaderSource(shader[2], 1, &sources[2], &lengths[2]);
            glShaderSource(shader[3], 1, &sources[3], &lengths[3]);
			glShaderSource(shader[4], 1, &sources[4], &lengths[4]);
            glCompileShader(shader[0]);
            glCompileShader(shader[1]);
            glCompileShader(shader[2]);
            glCompileShader(shader[3]);
			glCompileShader(shader[4]);
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
    
            glGetShaderiv(shader[2], GL_COMPILE_STATUS, &testVal);
            if (testVal == GL_FALSE) {
                printErrorDetail(shader[2]);
                return Program();
            }
            glGetShaderiv(shader[3], GL_COMPILE_STATUS, &testVal);
            if (testVal == GL_FALSE) {
                printErrorDetail(shader[3]);
                return Program();
            }
			glGetShaderiv(shader[4], GL_COMPILE_STATUS, &testVal);
			if (testVal == GL_FALSE) {
				printErrorDetail(shader[4]);
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
        glAttachShader(program, shader[2]);
		glAttachShader(program, shader[3]);
		glAttachShader(program, shader[4]);
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

static inline Program VTCTEGFProgramLoadSources (
        const char * vFile,
        const char * tcFile,
        const char * teFile,
        const char * gFile,
        const char * fFile
        ){
    return VTCTEGFProgramLoadSources(
                std::string(vFile),
                std::string(tcFile),
                std::string(teFile),
                std::string(gFile),
                std::string(fFile)
                );
}

static inline Program VTCTEGFProgamLoad(
        const std::string & v_name ,
        const std::string & tc_name,
        const std::string & te_name,
        const std::string & g_name,
        const std::string & f_name
        ){
    std::string   vFile ;
    std::string   tcFile;
    std::string   teFile;
    std::string   fFile ;
    std::string   gFile ;

    //30K
    vFile.reserve(1024*30);
	fFile.reserve(1024 * 30);
	teFile.reserve(1024 * 30);
	tcFile.reserve(1024 * 30);

    {
        std::ifstream ifs(v_name);
        if(false==ifs.is_open()){return Program();}
        std::string line;
        std::getline(ifs, line);
        typedef   std::string::value_type VType;
        if ((line.size()>=3)&&
                (line[0]== VType(0xef)) &&
                (line[1] == VType(0xbb)) &&
                (line[2] == VType(0xbf))) {
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
        std::ifstream ifs(tc_name);
        if(false==ifs.is_open()){return Program();}
        std::string line;
        std::getline(ifs, line);
        typedef   std::string::value_type VType;
        if ((line.size()>=3)&&
                (line[0]== VType(0xef)) &&
                (line[1] == VType(0xbb)) &&
                (line[2] == VType(0xbf))) {
            tcFile += std::string(line.begin()+3,line.end()) + "\n";
        }
        else {
            tcFile += line + "\n";
        }
        while (std::getline(ifs,line)) {
            tcFile+=line+"\n";
        }
    }

    {
        std::ifstream ifs(te_name);
        if(false==ifs.is_open()){return Program();}
        std::string line;
        std::getline(ifs, line);
        typedef   std::string::value_type VType;
        if ((line.size()>=3)&&
                (line[0]== VType(0xef)) &&
                (line[1] == VType(0xbb)) &&
                (line[2] == VType(0xbf))) {
            teFile += std::string(line.begin()+3,line.end()) + "\n";
        }
        else {
            teFile += line + "\n";
        }
        while (std::getline(ifs,line)) {
            teFile+=line+"\n";
        }
    }

    {
        std::ifstream ifs(f_name);
        if(false==ifs.is_open()){return Program();}
        std::string line;
        std::getline(ifs, line);
        typedef   std::string::value_type VType;
        if ((line.size()>=3)&&
                (line[0]== VType(0xef)) &&
                (line[1] == VType(0xbb)) &&
                (line[2] == VType(0xbf))) {
            fFile += std::string(line.begin()+3,line.end()) + "\n";
        }
        else {
            fFile += line + "\n";
        }
        while (std::getline(ifs,line)) {
            fFile+=line+"\n";
        }
    }

	{
		std::ifstream ifs(g_name);
		if (false == ifs.is_open()) { return Program(); }
		std::string line;
		std::getline(ifs, line);
		typedef   std::string::value_type VType;
		if ((line.size() >= 3) &&
			(line[0] == VType(0xef)) &&
			(line[1] == VType(0xbb)) &&
			(line[2] == VType(0xbf))) {
			gFile += std::string(line.begin() + 3, line.end()) + "\n";
		}
		else {
			gFile += line + "\n";
		}
		while (std::getline(ifs, line)) {
			gFile += line + "\n";
		}
	}

    return VTCTEGFProgramLoadSources(
                vFile,
                tcFile,
                teFile,
                gFile,
                fFile
                );
}

static inline Program VTCTEGFProgamLoad(
        const char * v_name ,
        const char * tc_name,
        const char * te_name,
        const char * g_name,
        const char * f_name
        ){
    typedef std::string T;
    return VTCTEGFProgamLoad(
                T(v_name),T(tc_name),T(g_name),
                T(te_name),T(f_name)
                );
}


#ifdef QT_CORE_LIB

static inline Program VTCTEGFProgamLoad(
        const QString & v_name ,
        const QString & tc_name,
        const QString & te_name,
        const QString & g_name,
        const QString & f_name
        ){

    auto T = [](const QString & x)->std::string{
        return std::move( x.toLocal8Bit().toStdString() );
    };

    return VTCTEGFProgamLoad(
                T(v_name),T(tc_name),T(te_name),
                T(g_name),T(f_name)
                );

}

static inline Program VTCTEGFProgramLoadSources (
        const QString & vFile,
        const QString & tcFile,
        const QString & teFile,
        const QString & gFile,
        const QString & fFile
        ){

    auto T = [](const QString & x)->std::string{
        return std::move( x.toLocal8Bit().toStdString() );
    };

    return VTCTEGFProgramLoadSources(
                T(vFile),T(tcFile),T(teFile),
                T(gFile),T(fFile)
                );

}


#endif

}


#endif

