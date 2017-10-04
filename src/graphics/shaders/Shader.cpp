#include "Shader.h"

#include "../../utils/FileLoader.h"

#include <iostream>

Shader::Shader(const char* shaderSourcePath, GLenum type) {
	m_ShaderSourcePath = shaderSourcePath;
	m_Type = type;
	m_Valid = false;
	m_ShaderID = 0;

	std::string shaderSource;
	int result = FileLoader::fileToString(shaderSourcePath, shaderSource);
	if (result != FileLoader::OK) {
		std::cout << "Failed to find shader: " << shaderSourcePath << std::endl;
		return;
	}


	const char* sourcePtr = shaderSource.c_str();
	GLint size = shaderSource.size();

	m_ShaderID = glCreateShader(m_Type);
	glShaderSource(m_ShaderID, 1, &sourcePtr, &size);

	glCompileShader(m_ShaderID);

	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		std::cout << "Failed to compile shader: " << shaderSourcePath << std::endl
			<< "OpenGL Error: " << std::endl;

		GLint length;
		glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetShaderInfoLog(m_ShaderID, length, NULL, log);
		std::cout << log << std::endl;
		return;
	}

	m_Valid = true;
}

Shader::~Shader() {
	glDeleteShader(m_ShaderID);
}