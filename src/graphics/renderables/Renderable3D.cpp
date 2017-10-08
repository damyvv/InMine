#include "Renderable3D.h"

#include "../buffers/StaticArrayBuffer.h"
#include "../buffers/StaticIndicesBuffer.h"

Renderable3D::Renderable3D(const std::vector<VertexData3D>& vertices, const std::vector<GLubyte>& indices)
{
	m_VAO = new VertexArray();
	m_VAO->bind();

	m_VBO = new StaticArrayBuffer<VertexData3D>();
	m_VBO->bind();
	m_VBO->storeData(vertices);

	m_IBO = new StaticIndicesBuffer<GLubyte>();
	m_IBO->bind();
	m_IBO->storeData(indices);

	m_IndicesCount = indices.size();


	glEnableVertexArrayAttrib(m_VAO->getID(), 0);
	glEnableVertexArrayAttrib(m_VAO->getID(), 1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (void*)offsetof(VertexData3D, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData3D), (void*)offsetof(VertexData3D, color));
}

Renderable3D::~Renderable3D() {
	delete m_VBO;
	delete m_IBO;
	delete m_VAO;
}