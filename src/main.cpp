#include <InMineConfig.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdio.h>
#include <chrono>

#include "graphics/Window.h"
#include "utils/FPSCounter.h"

#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/Shader.h"

#include "graphics/buffers/StaticArrayBuffer.h"
#include "graphics/buffers/VertexArray.h"

#include "graphics/shaders/DefaultShaderProgram.h"


#define WIDTH 800
#define HEIGHT 600

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;
	std::cout << "GLFW version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

	glm::vec2 vertices[] = {
		{0, 100},
		{100, 0},
		{0, 0},
		{0, 100},
		{100, 100},
		{100, 0},
	};

	std::string title = "InMine ";
	title += InMine_VERSION_STRING;
	Window window(WIDTH, HEIGHT, false, title.c_str());
	if (!window.isOpen()) {
		std::cout << "Failed to create window: " << window.getErrorMessage() << std::endl;
		getchar();
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	VertexArray vao;
	vao.bind();
	StaticArrayBuffer<glm::vec2> buffer;
	buffer.storeData(std::vector<glm::vec2>(vertices, vertices + sizeof(vertices) / sizeof(float)));

	glEnableVertexArrayAttrib(vao.getID(), 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glClearColor(84.0 / 255.0, 149.0 / 255.0, 255.0 / 255.0, 1);

	ShaderProgram* program = new DefaultShaderProgram();

	if (program->isValid())
		program->start();
	else
		return -1;

	glm::mat4 modelMatrix(1);
	GLuint modelMatrix_location = glGetUniformLocation(program->getProgramID(), "modelMatrix");
	glUniformMatrix4fv(modelMatrix_location, 1, GL_FALSE, &modelMatrix[0][0]);

	glm::mat4 projectionMatrix = glm::ortho(0.0f, (float) window.getWidth(), 0.0f, (float) window.getHeight(), -1.0f, 1000.0f);
	GLuint projectionMatrix_location = glGetUniformLocation(program->getProgramID(), "projectionMatrix");
	glUniformMatrix4fv(projectionMatrix_location, 1, GL_FALSE, &projectionMatrix[0][0]);

	FPSCounter fps;
	while (window.isOpen()) {
		glClear(GL_COLOR_BUFFER_BIT);

		auto now = std::chrono::high_resolution_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(200 + 100*sin(millis / 500.0), 200 + 100*cos(millis / 500.0), 0));
		modelMatrix = glm::rotate(modelMatrix, (float) millis / 1000.0f, glm::vec3(0, 0, 1));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-50, -50, 0));
		glUniformMatrix4fv(modelMatrix_location, 1, GL_FALSE, &modelMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();

		fps.tick();
	}

	return 0;
}