#include "Game.h"
#include "GL/glew.h"

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utils/input/Keyboard.h"
#include "../utils/input/Mouse.h"

#include "../graphics/textures/Texture.h"

#include "../graphics/renderer/Default3DRenderer.h"

Game::Game(int width, int height)
	: m_Width(width), m_Height(height) {
	initRendering();
	initGame();

	m_Camera.position.y = -2;

	m_DT = m_StartDT = 0;
}

void Game::initRendering() {
	glClearColor(84.0f / 255.0f, 149.0f / 255.0f, 255.0f / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glm::mat4 projectionMatrix = glm::perspective(70.0f, (float)m_Width / (float)m_Height, 0.1f, 100.0f);
	m_Renderer = new Default3DRenderer(projectionMatrix, &m_Camera);
}

void Game::initGame() {
	Texture* grass = m_TextureManager.requestSpriteTexture("grass", {
		"res/textures/pack0/assets/minecraft/textures/blocks/grass_side.png",
		"res/textures/pack0/assets/minecraft/textures/blocks/grass_top.png",
		"res/textures/pack0/assets/minecraft/textures/blocks/dirt.png"
	});
	grass->bind();

	Cube* c0 = new Cube();
	c0->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)));
	m_Cubes.push_back(c0);
}

void Game::update() {
	calcDT();

	handleInput();
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < m_Cubes.size(); i++) {
		m_Renderer->addToRenderQueue(m_Cubes[i]);
	}
	m_Renderer->render();
}

void Game::handleInput() {
	// Movement
	float moveAmt = m_DT * 3.0f / 1000.0f;
	if (Keyboard::isKeyDown(SDLK_a)) {
		m_Camera.position.x += moveAmt * cos(m_Camera.rotation.y);
		m_Camera.position.z += moveAmt * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_d)) {
		m_Camera.position.x -= moveAmt * cos(m_Camera.rotation.y);
		m_Camera.position.z -= moveAmt * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_w)) {
		m_Camera.position.z += moveAmt * cos(m_Camera.rotation.y);
		m_Camera.position.x -= moveAmt * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_s)) {
		m_Camera.position.z -= moveAmt * cos(m_Camera.rotation.y);
		m_Camera.position.x += moveAmt * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_SPACE)) {
		m_Camera.position.y -= moveAmt;
	}
	if (Keyboard::isKeyDown(SDLK_c)) {
		m_Camera.position.y += moveAmt;
	}

	static bool mouseCap = false;
	if (Keyboard::getKeyState(SDLK_ESCAPE) == Keyboard::KEY_PRESS) {
		mouseCap = !mouseCap;
		SDL_SetRelativeMouseMode((SDL_bool)mouseCap);
	}

	// Rotation
	if (mouseCap) {
		m_Camera.rotation.y += 0.002f * Mouse::getDX();
		m_Camera.rotation.x += 0.002f * Mouse::getDY();
	}
}

void Game::calcDT() {
	if (!m_DT && !m_StartDT) {
		m_StartDT = SDL_GetTicks();
	}
	else {
		int now = SDL_GetTicks();
		m_DT = now - m_StartDT;
		m_StartDT = now;
	}
}

Game::~Game() {
	for (int i = 0; i < m_Cubes.size(); i++) {
		delete m_Cubes[i];
	}
}