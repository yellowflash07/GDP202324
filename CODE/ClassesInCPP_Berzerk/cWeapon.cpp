#include "cWeapon.h"

#include <iostream>

cWeapon::cWeapon()
{
	// MakeGunCreationSound();
	std::cout << "cWeapon::cWeapon()" << std::endl;

	this->ammo = 100;
	this->isShot = false;
	this->position = glm::vec2(0.0f);
}

cWeapon::~cWeapon()
{
	std::cout << "cWeapon is destroyed" << std::endl;
}
bool cWeapon::Shoot(int numBullets)
{
	std::cout << "cWeapon::Shot(void)" << std::endl;
	return true;
}


glm::vec2 cWeapon::getPosition(void)
{
	return this->position;
}

void cWeapon::setPosition(glm::vec2 newPosition)
{
	this->position = newPosition;
	return;
}

glm::vec2 cWeapon::getVelocity(void)
{
	return this->velocity;
}

void cWeapon::setVelocity(glm::vec2 newVelocity)
{
	this->velocity = newVelocity;
	return;
}

bool cWeapon::get_isShot(void)
{
	return this->isShot;
}

void cWeapon::set_IsShot(bool bIsShot)
{
	this->isShot = bIsShot;
	return;
}
