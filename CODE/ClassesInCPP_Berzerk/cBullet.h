#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class cBullet
{
public:
	cBullet();
	~cBullet();
	glm::vec2 position;
	glm::vec2 direction;
	float velocity;
};