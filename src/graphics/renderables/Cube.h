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

	glm::vec3 m_Position;
public:
	Cube();
	Cube(glm::vec3 pos);
	~Cube();

	inline const Renderable3D* getRenderable3D() const { return _sharedMesh; }

	inline const glm::vec3& getPosition() const { return m_Position; }
	inline void setPosition(const glm::vec3 vec) { m_Position = vec; }

private:
	inline void initMesh();
};