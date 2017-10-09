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
#include "graphics/buffers/StaticIndicesBuffer.h"
#include "graphics/buffers/VertexArray.h"

#include "graphics/shaders/DefaultShaderProgram.h"

#include "graphics/renderables/VertexData.h"

#include "graphics/renderables/Renderable3D.h"

#include "graphics/renderables/Cube.h"

#include "graphics/renderer/Default3DRenderer.h"

#include "utils/input/Keyboard.h"


#define WIDTH 800
#define HEIGHT 600

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;
	std::cout << "GLFW version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

	std::string title = "InMine ";
	title += InMine_VERSION_STRING;
	Window window(WIDTH, HEIGHT, false, title.c_str());
	if (!window.isOpen()) {
		std::cout << "Failed to create window: " << window.getErrorMessage() << std::endl;
		getchar();
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(84.0f / 255.0f, 149.0f / 255.0f, 255.0f / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	DefaultShaderProgram* program = new DefaultShaderProgram();
	Renderer<const IRenderable3D*>* renderer = new Default3DRenderer(program);

	Cube c0;
	Cube c1;
	c1.setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, -5)));

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
		modelMatrix = glm::rotate(modelMatrix, (float) millis / 1000.0f, glm::vec3(1, 1, 0));
		c0.setModelMatrix(modelMatrix);

		renderer->addToRenderQueue(&c0);
		renderer->addToRenderQueue(&c1);
		renderer->render();

		window.update();

		fps.tick();
	}

	return 0;
}