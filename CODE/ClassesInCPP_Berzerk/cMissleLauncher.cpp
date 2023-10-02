#include "cMissleLanucher.h"
#include <iostream>

cMissleLauncher::cMissleLauncher()
{


}

bool cMissleLauncher::Shoot(void)
{
	std::cout << "cMissleLauncher shoots a missle!" << std::endl;
	return true;
}


glm::vec2 cMissleLauncher::getPosition(void)
{
	return this->position;
}

void cMissleLauncher::setPosition(glm::vec2 newPosition)
{
	this->position = newPosition;
	return;
}

glm::vec2 cMissleLauncher::getVelocity(void)
{
	return this->velocity;
}

void cMissleLauncher::setVelocity(glm::vec2 newVelocity)
{
	this->velocity = newVelocity;
	return;
}

bool cMissleLauncher::get_isShot(void)
{
	return this->isShot;
}

void cMissleLauncher::set_IsShot(bool bIsShot)
{
	this->isShot = bIsShot;
	return;
}
