#include "InMineConfig.h"
#include <iostream>

#include <GLFW\glfw3.h>

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	std::string title = "InMine " + std::string(InMine_VERSION_STRING);
	window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glClearColor(1, 0, 0, 1);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}