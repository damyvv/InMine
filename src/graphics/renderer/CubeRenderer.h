#pragma once

#include "Renderer.h"
#include "../renderables/Cube.h"
#include "../Camera.h"
#include "../shaders/CubeShaderProgram.h"

#include <vector>

#define BATCH_SIZE 50000

class CubeRenderer : public Renderer<const Cube*> {
private:
	std::vector<const Cube*> m_Cubes;
	const Camera* m_Camera;
	CubeShaderProgram* m_Shader;

	GLuint m_OBO;
public:
	CubeRenderer(const glm::mat4& projectionMatrix, const Camera* cam);
	~CubeRenderer();

	void addToRenderQueue(const Cube*);
	void render();
	inline bool isFull() { return m_Cubes.size() == BATCH_SIZE; }
};