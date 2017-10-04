#include "InMineConfig.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>

#include "Window.h"

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;

	float vertices[] = {
		0.0, 0.5,
		0.5, -0.5,
		-0.5, -0.5,
	};

	try {
		Window window(800, 600, false, "InMine " + std::string(InMine_VERSION_STRING));

		glEnableVertexAttribArray(0);
		GLuint vbo;
		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glClearColor(1, 0, 0, 1);
		while (window.isOpen()) {
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			window.update();
		}
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
		getchar();
		return -1;
	}

	return 0;
}