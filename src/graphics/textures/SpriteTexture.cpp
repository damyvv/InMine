#include "SpriteTexture.h"

SpriteTexture::SpriteTexture(int width, int height)
	: Texture(width, height) {
}

SpriteTexture::~SpriteTexture() {

}

void SpriteTexture::storeTexture(int offsetX, int offsetY, const char* path) {
	this->bind();
	int width, height;
	GLubyte* subImg = this->loadImage(path, &width, &height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, width, height, GL_RGBA, GL_UNSIGNED_BYTE, subImg);
	this->freeImage(subImg);
}