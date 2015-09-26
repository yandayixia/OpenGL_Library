#pragma once
#include <GL/glew.h>

namespace MyEngine{
	struct GLTextrue {
		//the unique id assigned to this specific texture
		GLuint _id;
		//the width and height of this texture.
		int _width, _height;
	};
}