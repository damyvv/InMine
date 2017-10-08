#pragma once

#include "Renderer.h"
#include "../renderables/IRenderable3D.h"

#include "../shaders/DefaultShaderProgram.h"

#include <deque>

class Default3DRenderer : public Renderer<const IRenderable3D*>
{
private:
	std::deque<const IRenderable3D*> m_RenderQueue;
	DefaultShaderProgram* m_ShaderProgram;
public:
	Default3DRenderer(DefaultShaderProgram* shaderProgram);
	virtual ~Default3DRenderer() = default;

	virtual void addToRenderQueue(const IRenderable3D*);
	virtual void render();
};
