#include "Game.h"
#include "GL/glew.h"

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utils/input/Keyboard.h"

#include "../graphics/textures/Texture.h"

#include "../graphics/renderer/Default3DRenderer.h"

Game::Game(int width, int height)
	: m_Width(width), m_Height(height) {
	initRendering();
	initGame();

	m_Camera.position.y = -2;
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
	if (Keyboard::isKeyDown(SDLK_a)) {
		m_Camera.position.x += 0.001f * cos(m_Camera.rotation.y);
		m_Camera.position.z += 0.001f * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_d)) {
		m_Camera.position.x -= 0.001f * cos(m_Camera.rotation.y);
		m_Camera.position.z -= 0.001f * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_w)) {
		m_Camera.position.z += 0.001f * cos(m_Camera.rotation.y);
		m_Camera.position.x -= 0.001f * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_s)) {
		m_Camera.position.z -= 0.001f * cos(m_Camera.rotation.y);
		m_Camera.position.x += 0.001f * sin(m_Camera.rotation.y);
	}
	if (Keyboard::isKeyDown(SDLK_SPACE)) {
		m_Camera.position.y -= 0.001f;
	}
	if (Keyboard::isKeyDown(SDLK_c)) {
		m_Camera.position.y += 0.001f;
	}

	// Rotation
	if (Keyboard::isKeyDown(SDLK_LEFT)) {
		m_Camera.rotation.y -= 0.0002f;
	}
	if (Keyboard::isKeyDown(SDLK_RIGHT)) {
		m_Camera.rotation.y += 0.0002f;
	}
	if (Keyboard::isKeyDown(SDLK_UP)) {
		m_Camera.rotation.x -= 0.0002f;
	}
	if (Keyboard::isKeyDown(SDLK_DOWN)) {
		m_Camera.rotation.x += 0.0002f;
	}
}

Game::~Game() {
	for (int i = 0; i < m_Cubes.size(); i++) {
		delete m_Cubes[i];
	}
}