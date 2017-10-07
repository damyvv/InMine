#include "ShaderProgram.h"

#include <GL/glew.h>

#include <iostream>

ShaderProgram::ShaderProgram() {
	m_ProgramID = glCreateProgram();
	m_Valid = false;
}

void ShaderProgram::attachShader(const Shader* shader) {
	if (!shader->isValid()) {
		const char* shaderType = (const char*) glGetString(shader->getShaderType());
		std::cout << "Failed to attach " << shader->getShaderSourcePath() << ". The shader is invalid. Check the logs to see what went wrong." << std::endl;
		return;
	}
	glAttachShader(m_ProgramID, shader->getShaderID());
	m_Shaders.push_back(shader);
}

void ShaderProgram::linkProgram() {
	glLinkProgram(m_ProgramID);

	for (const Shader* shader : m_Shaders) {
		glDetachShader(m_ProgramID, shader->getShaderID());
	}

	GLint result;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		std::cout << "Failed to link the shader program. OpenGL Error:" << std::endl;

		GLint length;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetProgramInfoLog(m_ProgramID, length, NULL, log);
		std::cout << log << std::endl;
		return;
	}
	m_Valid = true;
}

GLint ShaderProgram::getUniformLocation(const char* name) {
	GLint loc = glGetUniformLocation(m_ProgramID, name);
	if (loc < 0) {
		std::cout << "Failed to get uniform location for \"" << name << "\"" << std::endl;
	}
	return loc;
}