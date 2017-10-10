#include <InMineConfig.h>

#include <SDL.h>
#include <GL/glew.h>

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

#include "graphics/Camera.h"

#include "graphics/textures/TextureManager.h"

#include "graphics/textures/SpriteTexture.h"

#include "stb_image.h"

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

	glClearColor(84.0f / 255.0f, 149.0f / 255.0f, 255.0f / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);

	DefaultShaderProgram* program = new DefaultShaderProgram();
	Renderer<const IRenderable3D*>* renderer = new Default3DRenderer(program);

	TextureManager tm;

	glActiveTexture(GL_TEXTURE0);
	SpriteTexture* sp = new SpriteTexture(16 * 3, 16);
	sp->storeTexture(0 * 16, 0, "res/textures/pack0/assets/minecraft/textures/blocks/grass_side.png");
	sp->storeTexture(1 * 16, 0, "res/textures/pack0/assets/minecraft/textures/blocks/grass_top.png");
	sp->storeTexture(2 * 16, 0, "res/textures/pack0/assets/minecraft/textures/blocks/dirt.png");

	Camera cam;

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
		program->setViewMatrix(cam.getViewMatrix());

		// Movement
		if (Keyboard::isKeyDown(SDLK_a)) {
			cam.position.x += 0.001f * cos(cam.rotation.y);
			cam.position.z += 0.001f * sin(cam.rotation.y);
		}
		if (Keyboard::isKeyDown(SDLK_d)) {
			cam.position.x -= 0.001f * cos(cam.rotation.y);
			cam.position.z -= 0.001f * sin(cam.rotation.y);
		}
		if (Keyboard::isKeyDown(SDLK_w)) {
			cam.position.z += 0.001f * cos(cam.rotation.y);
			cam.position.x -= 0.001f * sin(cam.rotation.y);
		}
		if (Keyboard::isKeyDown(SDLK_s)) {
			cam.position.z -= 0.001f * cos(cam.rotation.y);
			cam.position.x += 0.001f * sin(cam.rotation.y);
		}
		if (Keyboard::isKeyDown(SDLK_SPACE)) {
			cam.position.y -= 0.001f;
		}
		if (Keyboard::isKeyDown(SDLK_c)) {
			cam.position.y += 0.001f;
		}

		// Rotation
		if (Keyboard::isKeyDown(SDLK_LEFT)) {
			cam.rotation.y -= 0.0002f;
		}
		if (Keyboard::isKeyDown(SDLK_RIGHT)) {
			cam.rotation.y += 0.0002f;
		}
		if (Keyboard::isKeyDown(SDLK_UP)) {
			cam.rotation.x -= 0.0002f;
		}
		if (Keyboard::isKeyDown(SDLK_DOWN)) {
			cam.rotation.x += 0.0002f;
		}

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

		int err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << err << std::endl;
		}

		fps.tick();
	}

	return 0;
}