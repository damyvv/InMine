#pragma once

#include "Renderer.h"
#include "../renderables/IRenderable3D.h"

#include "../shaders/DefaultShaderProgram.h"
#include "../Camera.h"

#include <deque>

class Default3DRenderer : public Renderer<const IRenderable3D*>
{
private:
	std::deque<const IRenderable3D*> m_RenderQueue;
	DefaultShaderProgram* m_ShaderProgram;
	bool m_OwnShader;
	const Camera* m_Camera;
public:
	Default3DRenderer(const glm::mat4& projectionMatrix, Camera* cam, DefaultShaderProgram* shaderProgram);
	Default3DRenderer(const glm::mat4& projectionMatrix, Camera* cam);
	virtual ~Default3DRenderer();

	virtual void addToRenderQueue(const IRenderable3D*);
	virtual void render();
};
