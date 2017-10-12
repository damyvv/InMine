#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(const glm::mat4& projectionMatrix, const Camera* cam) {
	m_Camera = cam;
	m_Shader = new CubeShaderProgram();
	m_Shader->start();
	m_Shader->setProjectionMatrix(projectionMatrix);

	m_Cubes.reserve(BATCH_SIZE);
}

CubeRenderer::~CubeRenderer() {
	delete m_Shader;
}

void CubeRenderer::addToRenderQueue(const Cube* cube) {
	if (this->isFull()) return;
	m_Cubes.push_back(cube);
}

void CubeRenderer::render() {
	if (m_Cubes.size() <= 0) return;
	
	m_Shader->start();
	m_Shader->setViewMatrix(m_Camera->getViewMatrix());

	const Renderable3D* r = m_Cubes[0]->getRenderable3D();
	r->bind();

	for (int i = 0; i < m_Cubes.size(); i++) {
		m_Shader->setModelMatrix(m_Cubes[i]->getModelMatrix());
		glDrawElements(GL_TRIANGLES, r->getIndicesCount(), GL_UNSIGNED_BYTE, 0);
	}

	m_Cubes.clear();
}