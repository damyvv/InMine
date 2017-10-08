#pragma once

#include "Renderer.h"
#include "../renderables/IRenderable3D.h"

#include <deque>

class Default3DRenderer : public Renderer<const IRenderable3D*>
{
private:
	std::deque<const IRenderable3D*> m_RenderQueue;
public:
	Default3DRenderer() = default;
	virtual ~Default3DRenderer() = default;

	virtual void addToRenderQueue(const IRenderable3D*);
	virtual void render();
};
