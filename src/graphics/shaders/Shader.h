#pragma once

#include <GL/glew.h>

class Shader
{
private:
	GLuint m_ShaderID;
	GLenum m_Type;
	bool m_Valid;
	const char* m_ShaderSourcePath;
public:
	Shader(const char* shaderSourcePath, GLenum type);
	~Shader();

	inline GLuint getShaderID() const { return m_ShaderID; }
	inline GLenum getShaderType() const { return m_Type; }
	inline const char* getShaderSourcePath() const { return m_ShaderSourcePath; }
	inline bool isValid() const { return m_Valid; }
};
