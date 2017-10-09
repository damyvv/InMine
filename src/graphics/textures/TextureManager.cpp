#include "TextureManager.h"

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