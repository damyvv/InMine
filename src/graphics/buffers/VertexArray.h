#pragma once

#include <GL/glew.h>

class VertexArray
{
private:
	GLuint m_ID;
public:
	VertexArray() { glGenVertexArrays(1, &m_ID); }
	virtual ~VertexArray() { glDeleteVertexArrays(1, &m_ID); }

	inline void bind() const { glBindVertexArray(m_ID); }
	inline void unbind() const { glBindVertexArray(0); }

	inline GLuint getID() const { return m_ID; }
};
