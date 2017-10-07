#pragma once

#include "ShaderProgram.h"

#include <glm/glm.hpp>

class DefaultShaderProgram : public ShaderProgram
{
private:
	GLint m_ModelMatrixLocation, m_ProjectionMatrixLocation;
public:
	DefaultShaderProgram();
	~DefaultShaderProgram();

	inline void setModelMatrix(glm::mat4& modelMatrix) const { loadUniformMat4(m_ModelMatrixLocation, modelMatrix); };
	inline void setProjectionMatrix(glm::mat4& projectionMatrix) const { loadUniformMat4(m_ProjectionMatrixLocation, projectionMatrix); };

private:
	void getMatrixLocations();

	inline void loadUniformMat4(GLint location, const glm::mat4& mat) const { glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]); }
};
