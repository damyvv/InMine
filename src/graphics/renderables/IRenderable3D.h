#pragma once

#include "Renderable3D.h"

class IRenderable3D
{
public:
	virtual inline const Renderable3D* getRenderable3D() const = 0;
};
