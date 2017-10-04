#pragma once

#include <GL/glew.h>

#include <vector>
#include "Shader.h"

class ShaderProgram
{
private:
	GLuint m_ProgramID;
	bool m_Valid;
	std::vector<const Shader*> m_Shaders;
public:
	ShaderProgram();
	virtual ~ShaderProgram() {};

	void attachShader(const Shader *shader);
	inline void start() const { glUseProgram(m_ProgramID); }
	inline GLuint getProgramID() const { return m_ProgramID; }
	inline bool isValid() const { return m_Valid; }

	void linkProgram();
};
