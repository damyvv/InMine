#include "Default3DRenderer.h"

#include <GL/glew.h>

Default3DRenderer::Default3DRenderer(DefaultShaderProgram* shaderProgram)
	: m_ShaderProgram(shaderProgram) {}

void Default3DRenderer::addToRenderQueue(const IRenderable3D* renderable) {
	m_RenderQueue.push_back(renderable);
}

void Default3DRenderer::render() {
	m_ShaderProgram->start();
	while (m_RenderQueue.size() > 0) {
		const IRenderable3D* r = m_RenderQueue.front();
		m_ShaderProgram->setModelMatrix(r->getModelMatrix());
		r->getRenderable3D()->bind();
		glDrawElements(GL_TRIANGLES, r->getRenderable3D()->getIndicesCount(), GL_UNSIGNED_BYTE, 0);
		m_RenderQueue.pop_front();
	}
}