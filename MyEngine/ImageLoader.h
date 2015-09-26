#pragma once
#include "GLTexture.h"

#include <string>


namespace MyEngine{
	class ImageLoader{

	public:
		static GLTextrue loadPNG(std::string filePath);

	};
}
