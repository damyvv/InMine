#include "CubeShaderProgram.h"

#include <GL/glew.h>

CubeShaderProgram::CubeShaderProgram() {
	Shader* vertexShader = new Shader("res/shaders/cubeVertexShader.glsl", GL_VERTEX_SHADER);
	Shader* fragmentShader = new Shader("res/shaders/cubeFragmentShader.glsl", GL_FRAGMENT_SHADER);

	this->attachShader(vertexShader);
	this->attachShader(fragmentShader);

	this->linkProgram();

	delete vertexShader;
	delete fragmentShader;

	if (this->isValid()) this->getMatrixLocations();
}

CubeShaderProgram::~CubeShaderProgram() {

}

void CubeShaderProgram::getMatrixLocations() {
	m_ModelMatrixLocation = getUniformLocation("modelMatrix");
	m_ProjectionMatrixLocation = getUniformLocation("projectionMatrix");
	m_ViewMatrixLocation = getUniformLocation("viewMatrix");
}