#include "TextureManager.h"

#include "SpriteTexture.h"
#include <stb_image.h>
#include <iostream>

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++) {
		delete (Texture*) it->second;
	}
}

Texture* TextureManager::requestTexture(std::string path) {
	if (!m_Textures[path])
		m_Textures[path] = new Texture(path.c_str());
	return m_Textures[path];

}

Texture* TextureManager::requestSpriteTexture(std::string name, std::vector<std::string> paths) {
	if (!m_Textures[name]) {
		if (paths.size() <= 0) return nullptr;
		int width, height;
		int res = stbi_info(paths[0].c_str(), &width, &height, nullptr);
		if (!res) {
			std::cout << "Could not determine image size for sprite texture \"" << name << "\"" << std::endl;
			return nullptr;
		}
		SpriteTexture* tex = new SpriteTexture(width * paths.size(), height);
		for (int i = 0; i < paths.size(); i++) {
			tex->storeTexture(width*i, 0, paths[i].c_str());
		}
		m_Textures[name] = tex;
	}
	return m_Textures[name];
}