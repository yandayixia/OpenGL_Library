#pragma once
#include <glm/glm.hpp>
#include <MyEngine/SpriteBatch.h>

class Bullet
{
	int _lifeTime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;

public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();

	void Draw(MyEngine::SpriteBatch& spriteBatch);

	//return true if it's out of time.
	bool Update();
};

