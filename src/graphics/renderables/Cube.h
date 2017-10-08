#pragma once

#include "Renderable3D.h"

#include <memory>

class Cube
{
private:
	static Renderable3D* _sharedMesh;
	static unsigned long _cubeCount;
	static const std::vector<VertexData3D> _cubeVertices;
	static const std::vector<GLubyte> _cubeIndices;
public:
	Cube();
	~Cube();

	inline const Renderable3D* getRenderable3D() const { return _sharedMesh; }
};