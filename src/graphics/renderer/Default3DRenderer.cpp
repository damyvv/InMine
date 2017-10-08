#include "Default3DRenderer.h"

#include <GL/glew.h>

void Default3DRenderer::addToRenderQueue(const IRenderable3D* renderable) {
	m_RenderQueue.push_back(renderable);
}

void Default3DRenderer::render() {
	while (m_RenderQueue.size() > 0) {
		const Renderable3D* r = m_RenderQueue.front()->getRenderable3D();
		m_RenderQueue.pop_front();
		r->bind();
		glDrawElements(GL_TRIANGLES, r->getIndicesCount(), GL_UNSIGNED_BYTE, 0);
	}
}