#include "cSword.h"
#include <iostream>

cSword::cSword()
{
}

bool cSword::Shoot(void)
{
	std::cout << "cSword::Shot(void)" << std::endl;
	return true;
}


glm::vec2 cSword::getPosition(void)
{
	return this->position;
}

void cSword::setPosition(glm::vec2 newPosition)
{
	this->position = newPosition;
	return;
}

glm::vec2 cSword::getVelocity(void)
{
	return this->velocity;
}

void cSword::setVelocity(glm::vec2 newVelocity)
{
	this->velocity = newVelocity;
	return;
}

bool cSword::get_isShot(void)
{
	return this->isShot;
}

void cSword::set_IsShot(bool bIsShot)
{
	this->isShot = bIsShot;
	return;
}
