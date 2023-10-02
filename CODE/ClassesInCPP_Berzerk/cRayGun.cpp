#include "cRayGun.h"
#include <iostream>

cRayGun::cRayGun()
{
	std::cout << "cRayGun is created" << std::endl;
	this->BatteryLeft = 100;
}

cRayGun::~cRayGun()
{
	std::cout << "cRayGun is destroyed" << std::endl;
}


bool cRayGun::Shoot(int numBullets)
{
	std::cout << "RayGun goes Bzzzzzzt!" << std::endl;
	return true;
}


glm::vec2 cRayGun::getPosition(void)
{
	return this->position;
}

void cRayGun::setPosition(glm::vec2 newPosition)
{
	this->position = newPosition;
	return;
}

glm::vec2 cRayGun::getVelocity(void)
{
	return this->velocity;
}

void cRayGun::setVelocity(glm::vec2 newVelocity)
{
	this->velocity = newVelocity;
	return;
}

bool cRayGun::get_isShot(void)
{
	return this->isShot;
}

void cRayGun::set_IsShot(bool bIsShot)
{
	this->isShot = bIsShot;
	return;
}
