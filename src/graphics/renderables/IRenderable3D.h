#pragma once

#include "Renderable3D.h"

#include <glm/glm.hpp>

class IRenderable3D
{
public:
	virtual const Renderable3D* getRenderable3D() const = 0;
	virtual const glm::mat4& getModelMatrix() const = 0;
};
