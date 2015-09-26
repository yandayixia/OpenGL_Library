#include "Bullet.h"
#include <MyEngine/GLTexture.h>
#include <MyEngine/ResourceManager.h>
#include <MyEngine/SpriteBatch.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_position = pos;
	_direction = dir;
	_speed = speed;
	_lifeTime = lifeTime;
}


Bullet::~Bullet()
{
}

void Bullet::Draw(MyEngine::SpriteBatch& spriteBatch){
	static MyEngine::GLTextrue myTexture = MyEngine::ResourceManager::getTexture("Texture/ship.png");
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	MyEngine::Color myColor;
	myColor.r = 255;
	myColor.g = 255;
	myColor.b = 255;
	myColor.a = 255;
	glm::vec4 tempsize(_position.x, _position.y, 30, 30);
	spriteBatch.Draw(tempsize, uv, myTexture._id, 0.0f, myColor);
}

//return true if it's out of time.
bool Bullet::Update(){
	_position += _direction*_speed;
	_lifeTime--;
	if (_lifeTime == 0){
		return true;
	}
	return false;
}