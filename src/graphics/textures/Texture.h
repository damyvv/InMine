#pragma once

#include <GL/glew.h>
#include <string>

class TextureManager;
class Texture
{
	friend TextureManager;

protected:
	GLuint m_ID;
	int m_Width, m_Height;
public:
	inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); }
	inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }

protected:
	Texture(const char* path);
	Texture(int width, int height);
	virtual ~Texture();

	GLubyte* loadImage(const char* path, int* width, int* height);
	void freeImage(GLubyte* image);
private:
	void genTexture();
};
