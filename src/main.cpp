#include "InMineConfig.h"
#include <iostream>

#include <GLFW/glfw3.h>

#include "Window.h"

int main() {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;

	Window window(800, 600, false, "InMine " + std::string(InMine_VERSION_STRING));

	glClearColor(1, 0, 0, 1);
	while (window.isOpen()) {
		glClear(GL_COLOR_BUFFER_BIT);

		window.update();
	}

	return 0;
}