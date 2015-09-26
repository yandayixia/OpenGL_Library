#pragma once
#include <string>
#include <GL/glew.h>
#include "FatalErrors.h"

namespace MyEngine{
	class GLSLProgram{
		GLuint _programID;
		GLuint _vertexshaderID;
		GLuint _fragmentshaderID;
		int _numAttribute;
		//Methods:
		void _CompileShader(const std::string& filePath, GLuint id);

	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void AddAttribute(const std::string rattributeName);
		void LinkShaders();

		void use();
		void unuse();

		GLint GetUniformLocation(const std::string& uniformName);
	};
}