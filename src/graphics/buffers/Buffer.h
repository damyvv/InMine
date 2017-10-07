#pragma once

#include <GL/glew.h>
#include <vector>

template <class T>
class Buffer
{
protected:
	GLuint m_ID;
	const GLenum m_Target;
protected:
	Buffer(GLenum target) : m_Target(target) { glGenBuffers(1, &m_ID); }
public:
	virtual ~Buffer() { 
		unbind();
		glDeleteBuffers(1, &m_ID);
	}

	virtual void storeData(const std::vector<T>& data) {
		this->bind();
		glBufferData(this->m_Target, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
	}

	inline void bind() const { glBindBuffer(m_Target, m_ID); }
	inline void unbind() const { glBindBuffer(m_Target, 0); }

};