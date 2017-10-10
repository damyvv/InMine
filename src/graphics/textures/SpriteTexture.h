#pragma once

#include "Texture.h"

class SpriteTexture : public Texture
{
private:

public:
	SpriteTexture(int width, int height);
	virtual ~SpriteTexture();

	void storeTexture(int offsetX, int offsetY, const char* path);
};
