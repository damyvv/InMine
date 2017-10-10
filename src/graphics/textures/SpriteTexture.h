#pragma once

#include "Texture.h"
#include "TextureManager.h"

class SpriteTexture : public Texture
{
	friend TextureManager;

protected:
	SpriteTexture(int width, int height);
	virtual ~SpriteTexture();
public:
	virtual void storeTexture(int offsetX, int offsetY, const char* path);
};
