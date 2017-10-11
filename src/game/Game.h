#pragma once

#include "../graphics/Camera.h"
#include "../graphics/renderer/Renderer.h"
#include "../graphics/renderables/IRenderable3D.h"
#include "../graphics/textures/TextureManager.h"

#include "../graphics/renderables/Cube.h"
#include <vector>

class Game
{
private:
	TextureManager m_TextureManager;
	Camera m_Camera;
	Renderer<const IRenderable3D*>* m_Renderer;
	std::vector<Cube*> m_Cubes;
	int m_Width, m_Height;
public:
	Game(int width, int height);
	~Game();

	void update();
	void render();

private:
	void initRendering();
	void initGame();
	void handleInput();
};