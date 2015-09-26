  #include "Sprite.h"
#include "Vertex.h"
#include <cstddef> //to get the "offsetof" operation
#include "ResourceManager.h"

namespace MyEngine{
	Sprite::Sprite(){
		//always initialize vertex buffer object to zero.
		_vboID = 0;
	}


	Sprite::~Sprite(){
		if (_vboID != 0){
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::Init(float x, float y, float width, float height, std::string texturePath){
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::GetTexture(texturePath);

		if (_vboID == 0){
			//Generate one buffer, pass in a ptr to the local vertex buffer object.
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];
		//populate position
		vertexData[0].SetPosition(x + width, y + height);
		vertexData[0].SetUV(1.0f, 1.0f);

		vertexData[1].SetPosition(x, y + height);
		vertexData[1].SetUV(0.0f, 1.0f);

		vertexData[2].SetPosition(x, y);
		vertexData[2].SetUV(0.0f, 0.0f);

		vertexData[3].SetPosition(x, y);
		vertexData[3].SetUV(0.0f, 0.0f);

		vertexData[4].SetPosition(x + width, y);
		vertexData[4].SetUV(1.0f, 0.0f);

		vertexData[5].SetPosition(x + width, y + height);
		vertexData[5].SetUV(1.0f, 1.0f);

		//populate color
		for (int i = 0; i < 6; i++){
			vertexData[i].SetColor(255, 0, 255, 255);
		}
		vertexData[1].SetColor(0, 0, 255, 255);

		vertexData[1].SetColor(0, 255, 0, 255);

		//Bind the buffer, common array buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::Draw(){
		glBindTexture(GL_TEXTURE_2D, _texture._id);
		//we can only have 1 array buffer binded at the same time.
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//what mode to draw, index to start, how many verticies.
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}