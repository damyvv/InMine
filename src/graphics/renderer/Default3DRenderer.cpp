#include "Default3DRenderer.h"

#include <GL/glew.h>

Default3DRenderer::Default3DRenderer(const glm::mat4& projectionMatrix, Camera* cam, DefaultShaderProgram* shaderProgram)
	: m_Camera(cam), m_ShaderProgram(shaderProgram), m_OwnShader(false) {
	m_ShaderProgram->start();
	m_ShaderProgram->setProjectionMatrix(projectionMatrix);
}

Default3DRenderer::Default3DRenderer(const glm::mat4& projectionMatrix, Camera* cam)
	: m_Camera(cam), m_OwnShader(true) {
	m_ShaderProgram = new DefaultShaderProgram();
	m_ShaderProgram->start();
	m_ShaderProgram->setProjectionMatrix(projectionMatrix);
}

Default3DRenderer::~Default3DRenderer() {
	if (m_OwnShader)
		delete m_ShaderProgram;
}

void Default3DRenderer::addToRenderQueue(const IRenderable3D* renderable) {
	m_RenderQueue.push_back(renderable);
}

void Default3DRenderer::render() {
	m_ShaderProgram->start();
	m_ShaderProgram->setViewMatrix(m_Camera->getViewMatrix());
	while (m_RenderQueue.size() > 0) {
		const IRenderable3D* r = m_RenderQueue.front();
		m_ShaderProgram->setModelMatrix(r->getModelMatrix());
		r->getRenderable3D()->bind();
		glDrawElements(GL_TRIANGLES, r->getRenderable3D()->getIndicesCount(), GL_UNSIGNED_BYTE, 0);
		m_RenderQueue.pop_front();
	}
}