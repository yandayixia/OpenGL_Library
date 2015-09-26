#pragma once
#include <map>
#include <string>
#include "GLTexture.h"

namespace MyEngine{
	class TextureCache
	{
		//a map of "path vs GLTexture" pairs
		std::map<std::string, GLTextrue> _textureMap;
	public:
		TextureCache();
		~TextureCache();
		//If the GLTexture has already been stored in _textureMap, search and return directly.
		//Otherwise load and add the new pair into _textureMap.
		GLTextrue GetTexture(std::string texturePath);
	};
}