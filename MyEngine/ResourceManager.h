#pragma once
#include "TextureCache.h"

namespace MyEngine{
	class ResourceManager
	{
		static TextureCache _textureCache;
	public:
		static GLTextrue GetTexture(std::string texturePath);
	};
}
