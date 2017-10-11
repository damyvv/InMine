#pragma once

#include <map>
#include <vector>

class Texture;
class TextureManager
{
private:
	std::map<std::string, Texture*> m_Textures;
public:
	TextureManager();
	~TextureManager();

	Texture* requestTexture(std::string path);
	Texture* requestSpriteTexture(std::string name, std::vector<std::string> paths);
};
