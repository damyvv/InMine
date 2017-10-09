#pragma once

#include <GL/glew.h>
#include <string>

class Texture
{
private:
	GLuint m_ID;
	int m_Width, m_Height;
public:
	Texture(const char* path);
	~Texture();

	inline void bind() { glBindTexture(GL_TEXTURE_2D, m_ID); }
	inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
};
