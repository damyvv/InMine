#include "Cube.h"

Cube::Cube()
	: m_ModelMatrix(1)
{
	if (_cubeCount == 0) {
		_sharedMesh = new Renderable3D(_cubeVertices, _cubeIndices);
	}
	_cubeCount++;
}

Cube::~Cube()
{
	_cubeCount--;
	if (_cubeCount == 0) {
		delete _sharedMesh;
	}
}

Renderable3D* Cube::_sharedMesh = nullptr;

unsigned long Cube::_cubeCount = 0;

const std::vector<VertexData3D> Cube::_cubeVertices({
	// FRONT
	{ { -0.5f, -0.5f,  0.5f },{ 1, 0, 0, 1 } },
	{ { 0.5f, -0.5f,  0.5f },{ 1, 0, 0, 1 } },
	{ { 0.5f,  0.5f,  0.5f },{ 1, 0, 0, 1 } },
	{ { -0.5f,  0.5f,  0.5f },{ 1, 0, 0, 1 } },

	// BACK
	{ { -0.5f,  0.5f, -0.5f },{ 0, 1, 0, 1 } },
	{ { 0.5f,  0.5f, -0.5f },{ 0, 1, 0, 1 } },
	{ { 0.5f, -0.5f, -0.5f },{ 0, 1, 0, 1 } },
	{ { -0.5f, -0.5f, -0.5f },{ 0, 1, 0, 1 } },

	// LEFT
	{ { -0.5f, -0.5f, -0.5f },{ 0, 0, 1, 1 } },
	{ { -0.5f, -0.5f,  0.5f },{ 0, 0, 1, 1 } },
	{ { -0.5f,  0.5f,  0.5f },{ 0, 0, 1, 1 } },
	{ { -0.5f,  0.5f, -0.5f },{ 0, 0, 1, 1 } },

	// RIGHT
	{ { 0.5f,  0.5f, -0.5f },{ 0, 1, 1, 1 } },
	{ { 0.5f,  0.5f,  0.5f },{ 0, 1, 1, 1 } },
	{ { 0.5f, -0.5f,  0.5f },{ 0, 1, 1, 1 } },
	{ { 0.5f, -0.5f, -0.5f },{ 0, 1, 1, 1 } },

	// TOP
	{ { -0.5f,  0.5f,  0.5f },{ 1, 1, 0, 1 } },
	{ { 0.5f,  0.5f,  0.5f },{ 1, 1, 0, 1 } },
	{ { 0.5f,  0.5f, -0.5f },{ 1, 1, 0, 1 } },
	{ { -0.5f,  0.5f, -0.5f },{ 1, 1, 0, 1 } },

	// BOTTOM
	{ { -0.5f, -0.5f, -0.5f },{ 1, 0, 1, 1 } },
	{ { 0.5f, -0.5f, -0.5f },{ 1, 0, 1, 1 } },
	{ { 0.5f, -0.5f,  0.5f },{ 1, 0, 1, 1 } },
	{ { -0.5f, -0.5f,  0.5f },{ 1, 0, 1, 1 } },
});

const std::vector<GLubyte> Cube::_cubeIndices({
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,

	16, 17, 18,
	18, 19, 16,

	20, 21, 22,
	22, 23, 20,
});