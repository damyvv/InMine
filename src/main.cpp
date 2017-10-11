#include <InMineConfig.h>

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>
#include <stdio.h>

#include "graphics/Window.h"
#include "utils/FPSCounter.h"

#include "game/Game.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *args[]) {
	std::cout << "InMine version: " << InMine_VERSION_STRING << std::endl;
	std::cout << "SDL version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION << "." << SDL_PATCHLEVEL << std::endl;

	std::string title = "InMine ";
	title += InMine_VERSION_STRING;
	Window window(WIDTH, HEIGHT, false, title.c_str());
	if (!window.isOpen()) {
		std::cout << "Failed to create window: " << window.getErrorMessage() << std::endl;
		getchar();
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	Game game(WIDTH, HEIGHT);

	FPSCounter fps;
	while (window.isOpen()) {

		game.update();
		game.render();

		window.update();

		int err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << err << std::endl;
		}

		fps.tick();
	}

	return 0;
}