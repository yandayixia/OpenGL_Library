#include "GLSLProgram.h"
#include "FatalErrors.h"

#include <fstream>
#include <vector>


namespace MyEngine{
	//empty constructor, initialize everything to 0.
	GLSLProgram::GLSLProgram() :_programID(0), _vertexshaderID(0), _fragmentshaderID(0), _numAttribute(0){}
	GLSLProgram::~GLSLProgram(){}

	void GLSLProgram::_CompileShader(const std::string& filePath, GLuint id){
		std::ifstream tempvertexfile(filePath);
		std::string tempfilecontents = "";
		std::string templine;
		//check if the shader text file is successfully loaded.
		if (tempvertexfile.fail()){
			perror(filePath.c_str());
			FatalError("Failed to open:" + filePath + "!!!!");
		}
		//acquire the content of shader file.
		while (std::getline(tempvertexfile, templine)){
			tempfilecontents += templine + "\n";
		}
		tempvertexfile.close();
		//compile the shader
		const char* contentsPtr = tempfilecontents.c_str();
		//id of the shadder compiling, number of strings, a ptr of the constant c string to the conetent of the file, an array containing the length of each string
		glShaderSource(id, 1, &contentsPtr, nullptr);
		glCompileShader(id);
		//Check if the shadder is successfully compiled.
		GLint tempsuccess = 0;
		//fetch the compile status of a shader ID, storing it in tempsuccess
		glGetShaderiv(id, GL_COMPILE_STATUS, &tempsuccess);

		if (tempsuccess == GL_FALSE){
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//length includes the null pointer.
			std::vector<char> ERRORLOG(maxLength); 
			glGetShaderInfoLog(id, maxLength, &maxLength, &(ERRORLOG[0]));

			glDeleteShader(id);

			std::printf("%s\n", &(ERRORLOG[0]));
			FatalError("Shader " + filePath + " failed to compile!");
		}
	}

	void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
		_programID = glCreateProgram();

		//returns the index of the created shader
		_vertexshaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexshaderID == 0){
			FatalError("Vertex shader failed to be created!!!");
		}

		_fragmentshaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentshaderID == 0){
			FatalError("Fragment shader failed to be created!!!");
		}
		_CompileShader(vertexShaderFilePath, _vertexshaderID);
		_CompileShader(fragmentShaderFilePath, _fragmentshaderID);
	}

	void GLSLProgram::AddAttribute(const std::string attributeName){
		//specify the input of the shaders.
		glBindAttribLocation(_programID, _numAttribute++, attributeName.c_str());
	}

	void GLSLProgram::LinkShaders(){
		//Vertex and fragment shaders are successfully compiled.
		//NOw we will link them together into a program
		//To get a program object:

		//Attach the shaders to our program: 
		glAttachShader(_programID, _vertexshaderID);
		glAttachShader(_programID, _fragmentshaderID);

		//Link our program
		glLinkProgram(_programID);

		//Error checking for linking process:
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE){
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &(infoLog[0]));

			glDeleteProgram(_programID);

			glDeleteShader(_vertexshaderID);
			glDeleteShader(_fragmentshaderID);

			std::printf("%s\n", &(infoLog[0]));
			FatalError("Shaders failed to line!");
		}

		//Detached & delete the Shaders
		glDetachShader(_programID, _vertexshaderID);
		glDetachShader(_programID, _fragmentshaderID);
		glDeleteShader(_vertexshaderID);
		glDeleteShader(_fragmentshaderID);
	}

	void GLSLProgram::use(){
		glUseProgram(_programID);
		for (int i = 0; i < _numAttribute; i++){
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse(){
		glUseProgram(0);
		for (int i = 0; i < _numAttribute; i++){
			glDisableVertexAttribArray(i);
		}
	}
	//GLint is SIGNED! can be negative
	GLint GLSLProgram::GetUniformLocation(const std::string& uniformName){
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX){
			FatalError("Uniform " + uniformName + " not found in shader!");
		}
		return location;
	}
}