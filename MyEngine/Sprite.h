#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>


namespace MyEngine{
	class Sprite{
		float _x, _y;
		float _height, _width;
		GLuint _vboID;
		GLTextrue _texture;

	public:
		Sprite();
		~Sprite();

		void Init(float x, float y, float width, float height, std::string texturePath);
		void Draw();
	};

}