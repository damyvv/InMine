#include <InMineConfig.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>

#include "graphics/Window.h"
#include "utils/FPSCounter.h"

#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/Shader.h"

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;
	std::cout << "GLFW version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;

	float vertices[] = {
		0.0, 0.5,
		0.5, -0.5,
		-0.5, -0.5,
	};

	std::string title = "InMine ";
	title += InMine_VERSION_STRING;
	Window window(800, 600, false, title.c_str());
	if (!window.isOpen()) {
		std::cout << "Failed to create window: " << window.getErrorMessage() << std::endl;
		getchar();
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glEnableVertexAttribArray(0);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glClearColor(1, 0, 0, 1);

	Shader* vertexShader = new Shader("res/shaders/defaultVertexShader.glsl", GL_VERTEX_SHADER);
	Shader* fragmentShader = new Shader("res/shaders/defaultFragmentShader.glsl", GL_FRAGMENT_SHADER);
	ShaderProgram program;
	program.attachShader(vertexShader);
	program.attachShader(fragmentShader);
	program.linkProgram();
	delete vertexShader;
	delete fragmentShader;

	if (program.isValid())
		program.start();

	FPSCounter fps;
	while (window.isOpen()) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.update();

		fps.tick();
	}

	return 0;
}