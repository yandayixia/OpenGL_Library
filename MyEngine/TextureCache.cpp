#include "TextureCache.h"
#include "ImageLoader.h"
#include <string>
#include <map>
#include <iostream>
#include "GLTexture.h"

namespace MyEngine{
	TextureCache::TextureCache(){}
	TextureCache::~TextureCache(){}

	GLTextrue TextureCache::GetTexture(std::string texturePath){
		//lookup the texture and see if its in the map
		std::map<std::string, GLTextrue> ::iterator mit = _textureMap.find(texturePath);

		//check if its not in the map
		if (mit == _textureMap.end()){
			//load the texture
			GLTextrue newTexture = ImageLoader::loadPNG(texturePath);
			std::pair<std::string, GLTextrue> newPair(texturePath, newTexture);
			//and add the new pair into the map.
			_textureMap.insert(newPair);
			std::cout << "Adding New texture!" << std::endl;
			return newTexture;
		}
		//std::cout << "Using Loaded texture!!!" << std::endl;
		return mit->second;
	}
}