#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* path) {
	genTexture();

	GLubyte* pixels = loadImage(path, &m_Width, &m_Height);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	freeImage(pixels);
}

Texture::Texture(int width, int height)
	: m_Width(width), m_Height(height) {
	genTexture();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_ID);
}

GLubyte* Texture::loadImage(const char* path, int* width, int* height) {
	return stbi_load(path, width, height, nullptr, 4);
}

void Texture::freeImage(GLubyte* image) {
	stbi_image_free(image);
}

void Texture::genTexture() {
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}