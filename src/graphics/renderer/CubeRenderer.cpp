#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(const glm::mat4& projectionMatrix, const Camera* cam) {
	m_Camera = cam;
	m_Shader = new CubeShaderProgram();
	m_Shader->start();
	m_Shader->setProjectionMatrix(projectionMatrix);

	m_Cubes.reserve(BATCH_SIZE);

	glGenBuffers(1, &m_OBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_OBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * BATCH_SIZE, nullptr, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	glBindBuffer(GL_ARRAY_BUFFER, m_OBO);

	static bool options_set = false;
	if (!options_set) {
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribDivisor(3, 1);
		options_set = true;
	}

	glm::vec3* offsetsPtr = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	for (int i = 0; i < m_Cubes.size(); i++) {
		*offsetsPtr++ = m_Cubes[i]->getPosition();
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glDrawElementsInstanced(GL_TRIANGLES, r->getIndicesCount(), GL_UNSIGNED_BYTE, 0, m_Cubes.size());

	m_Cubes.clear();
}