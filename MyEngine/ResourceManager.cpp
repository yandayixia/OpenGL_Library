#include "ResourceManager.h"
#include "TextureCache.h"

namespace MyEngine{
	TextureCache ResourceManager::_textureCache;

	GLTextrue ResourceManager::GetTexture(std::string texturePath){
		return _textureCache.GetTexture(texturePath);
	}
}