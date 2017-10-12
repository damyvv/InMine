#pragma once

#include "ShaderProgram.h"

#include <glm/glm.hpp>

class CubeShaderProgram : public ShaderProgram
{
private:
	GLint m_ModelMatrixLocation, m_ProjectionMatrixLocation, m_ViewMatrixLocation;
public:
	CubeShaderProgram();
	~CubeShaderProgram();

	inline void setModelMatrix(const glm::mat4& modelMatrix) const { loadUniformMat4(m_ModelMatrixLocation, modelMatrix); };
	inline void setProjectionMatrix(const glm::mat4& projectionMatrix) const { loadUniformMat4(m_ProjectionMatrixLocation, projectionMatrix); };
	inline void setViewMatrix(const glm::mat4& viewMatrix) const { loadUniformMat4(m_ViewMatrixLocation, viewMatrix); }

private:
	void getMatrixLocations();

	inline void loadUniformMat4(GLint location, const glm::mat4& mat) const { glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]); }
};
