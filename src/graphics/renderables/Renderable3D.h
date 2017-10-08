#pragma once

#include <vector>
#include <GL/glew.h>

#include "VertexData.h"

#include "../buffers/VertexArray.h"
#include "../buffers/Buffer.h"

class Renderable3D
{
private:
	VertexArray* m_VAO;
	Buffer<VertexData3D>* m_VBO;
	Buffer<GLubyte>* m_IBO;
	GLsizei m_IndicesCount;
public:
	Renderable3D(const std::vector<VertexData3D>& vertices, const std::vector<GLubyte>& indices);
	virtual ~Renderable3D();

	virtual inline void bind() const { m_VAO->bind(); }
	inline GLsizei getIndicesCount() const { return m_IndicesCount; }
};
