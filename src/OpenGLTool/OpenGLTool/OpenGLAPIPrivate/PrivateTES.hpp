#ifndef __PRIVATE__TES__0x00__
#define __PRIVATE__TES__0x00__

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

	static inline Program VTEFProgramLoadSources(
		const std::string & vFile,
		const std::string & teFile,
		const std::string & fFile
		) {

		if ( fFile.empty() || vFile.empty()|| teFile.empty() ) { return Program(); }

		{//0
			auto printProgramInfo = [](GLuint e) {

				GLint log_length;
				glGetProgramiv(e, GL_INFO_LOG_LENGTH, &log_length);
				log_length += 16;

				typedef void(*DFunction)(char *);
				std::unique_ptr<char, DFunction> infos_(
					new char[log_length],
					[](char * d) {delete[]d; }
				);

				char * info = infos_.get();

				glGetProgramInfoLog(e, 1024, NULL, info);
				std::cout << info << std::endl;
				std::cout.flush();
			};

			auto printError = [](const std::string & err) {
				std::cout << err << std::endl;
				std::cout.flush();
			};

			auto printErrorDetail = [](GLuint e) {
				typedef void(*DFunction)(char *);

				GLint log_length;
				glGetShaderiv(e, GL_INFO_LOG_LENGTH, &log_length);
				log_length += 16;

				std::unique_ptr<char, DFunction> infos_(
					new char[log_length],
					[](char * d) {delete[]d; }
				);
				char * info = infos_.get();
				glGetShaderInfoLog(e, log_length, NULL, info);
				std::cout << info << std::endl;
				std::cout.flush();
			};

			enum {
				VS__ = 0,
				TE__ = 1,
				FS__ = 2
			};

			class ShaderFree {
			public:
				std::array<GLuint, 3> data;
				ShaderFree() {
					data[0] = 0;
					data[1] = 0;
					data[2] = 0;
				}
				~ShaderFree() {
					glDeleteShader(data[VS__]);
					glDeleteShader(data[TE__]);
					glDeleteShader(data[FS__]);
				}
			}shaders;



			GLuint * shader = &(shaders.data[0]);

			{//1
				shader[VS__] = glCreateShader(GL_VERTEX_SHADER);
				if (0 == (shader[VS__])) {
					printError("GL_VERTEX_SHADER not surported!");
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
			}//1

			{//2
				const GLchar * sources[] = {
					vFile.c_str(),
					teFile.c_str(),
					fFile.c_str() };

				GLint lengths[] = {
					(GLint)(vFile.size()),
					(GLint)(teFile.size()),
					(GLint)(fFile.size())
				};

				glShaderSource(shader[0], 1, &sources[0], &lengths[0]);
				glShaderSource(shader[1], 1, &sources[1], &lengths[1]);
				glShaderSource(shader[2], 1, &sources[2], &lengths[2]);

				glCompileShader(shader[0]);
				glCompileShader(shader[1]);
				glCompileShader(shader[2]);

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
 
			}//3

			GLuint program = glCreateProgram();
			if (program == 0) {
				printError("can not create program!");
				return Program();
			}

			glAttachShader(program, shader[0]);
			glAttachShader(program, shader[1]);
			glAttachShader(program, shader[2]);
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

	static inline Program VTEFProgramLoadSources(
		const char * vFile,
		const char * teFile,
		const char * fFile
		) {
		return VTEFProgramLoadSources(
			std::string(vFile),
			std::string(teFile),
			std::string(fFile)
			);
	}

	static inline Program VTEFProgamLoad(
		const std::string & v_name,
		const std::string & te_name,
		const std::string & f_name
		) {
		std::string   vFile;
		std::string   teFile;
		std::string   fFile;

		//30K
		vFile.reserve(1024 * 30);
		fFile.reserve(1024 * 30);
		teFile.reserve(1024 * 30);

		{
			std::ifstream ifs(v_name);
			if (false == ifs.is_open()) { return Program(); }
			std::string line;
			std::getline(ifs, line);
			typedef   std::string::value_type VType;
			if ((line.size() >= 3) &&
				(line[0] == VType(0xef)) &&
				(line[1] == VType(0xbb)) &&
				(line[2] == VType(0xbf))) {
				vFile += std::string(line.begin() + 3, line.end()) + "\n";
			}
			else {
				vFile += line + "\n";
			}
			while (std::getline(ifs, line)) {
				vFile += line + "\n";
			}
		}

		{
			std::ifstream ifs(te_name);
			if (false == ifs.is_open()) { return Program(); }
			std::string line;
			std::getline(ifs, line);
			typedef   std::string::value_type VType;
			if ((line.size() >= 3) &&
				(line[0] == VType(0xef)) &&
				(line[1] == VType(0xbb)) &&
				(line[2] == VType(0xbf))) {
				teFile += std::string(line.begin() + 3, line.end()) + "\n";
			}
			else {
				teFile += line + "\n";
			}
			while (std::getline(ifs, line)) {
				teFile += line + "\n";
			}
		}

		{
			std::ifstream ifs(f_name);
			if (false == ifs.is_open()) { return Program(); }
			std::string line;
			std::getline(ifs, line);
			typedef   std::string::value_type VType;
			if ((line.size() >= 3) &&
				(line[0] == VType(0xef)) &&
				(line[1] == VType(0xbb)) &&
				(line[2] == VType(0xbf))) {
				fFile += std::string(line.begin() + 3, line.end()) + "\n";
			}
			else {
				fFile += line + "\n";
			}
			while (std::getline(ifs, line)) {
				fFile += line + "\n";
			}
		}

		return VTEFProgramLoadSources(
			vFile,
			teFile,
			fFile
			);
	}

	static inline Program VTEFProgamLoad(
		const char * v_name,
		const char * te_name,
		const char * f_name
		) {
		typedef std::string T;
		return VTEFProgamLoad(
			T(v_name),  T(te_name), T(f_name)
			);
	}


#ifdef QT_CORE_LIB

	static inline Program VTEFProgamLoad(
		const QString & v_name,
		const QString & te_name,
		const QString & f_name
		) {

		auto T = [](const QString & x)->std::string {
			return std::move(x.toLocal8Bit().toStdString());
		};

		return VTEFProgamLoad(
			T(v_name),  T(te_name), T(f_name)
			);

	}

	static inline Program VTEFProgramLoadSources(
		const QString & vFile,
		const QString & teFile,
		const QString & fFile
		) {

		auto T = [](const QString & x)->std::string {
			return std::move(x.toLocal8Bit().toStdString());
		};

		return VTEFProgramLoadSources(
			T(vFile), T(teFile), T(fFile)
			);

	}


#endif

}

 

#endif

