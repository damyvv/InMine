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

#include "graphics/renderables/VertexData.h"


#define WIDTH 800
#define HEIGHT 600

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;
	std::cout << "GLFW version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

	VertexData3D vertices[] = {
		{ {-0.5f,  0.5f, -0.5f }, { 1, 0, 0, 1 } },
		{ { 0.5f, -0.5f, -0.5f }, { 0, 1, 0, 1 } },
		{ {-0.5f, -0.5f, -0.5f }, { 0, 0, 1, 1 } },
		{ {-0.5f,  0.5f, -0.5f }, { 1, 0, 0, 1 } },
		{ { 0.5f,  0.5f, -0.5f }, { 1, 1, 1, 1 } },
		{ { 0.5f, -0.5f, -0.5f }, { 0, 1, 0, 1 } },
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
	StaticArrayBuffer<VertexData3D> buffer;
	buffer.storeData(std::vector<VertexData3D>(vertices, vertices + sizeof(vertices) / sizeof(VertexData3D)));

	glEnableVertexArrayAttrib(vao.getID(), 0);
	glEnableVertexArrayAttrib(vao.getID(), 1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (void*) offsetof(VertexData3D, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (void*) offsetof(VertexData3D, color));

	glClearColor(84.0f / 255.0f, 149.0f / 255.0f, 255.0f / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	DefaultShaderProgram* program = new DefaultShaderProgram();

	if (program->isValid())
		program->start();
	else
		return -1;

	glm::mat4 modelMatrix(1);
	program->setModelMatrix(modelMatrix);

	glm::mat4 projectionMatrix = glm::perspective(70.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
	program->setProjectionMatrix(projectionMatrix);

	FPSCounter fps;
	while (window.isOpen()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto now = std::chrono::high_resolution_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -5));
		modelMatrix = glm::rotate(modelMatrix, (float)millis / 1000.0f, glm::vec3(0, 1, 0));
		program->setModelMatrix(modelMatrix);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();

		fps.tick();
	}

	return 0;
}