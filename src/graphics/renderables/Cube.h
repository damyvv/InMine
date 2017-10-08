#pragma once

#include "Renderable3D.h"

#include <memory>

class Cube
{
private:
	static Renderable3D* _sharedMesh;
	static unsigned long _cubeCount;
	static const std::vector<VertexData3D> Cube::_cubeVertices;
	static const std::vector<GLubyte> Cube::_cubeIndices;
public:
	Cube();
	~Cube();
};