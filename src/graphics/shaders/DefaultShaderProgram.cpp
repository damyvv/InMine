#include "DefaultShaderProgram.h"

#include <GL/glew.h>

DefaultShaderProgram::DefaultShaderProgram() {
	Shader* vertexShader = new Shader("res/shaders/defaultVertexShader.glsl", GL_VERTEX_SHADER);
	Shader* fragmentShader = new Shader("res/shaders/defaultFragmentShader.glsl", GL_FRAGMENT_SHADER);

	this->attachShader(vertexShader);
	this->attachShader(fragmentShader);

	this->linkProgram();

	delete vertexShader;
	delete fragmentShader;
}

DefaultShaderProgram::~DefaultShaderProgram() {

}