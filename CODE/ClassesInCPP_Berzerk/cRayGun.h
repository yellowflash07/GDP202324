#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include "cWeapon.h"
#include <string>

class cRayGun : public cWeapon
{
public:
	cRayGun();
	virtual ~cRayGun() {};

	//glm::vec2 position;
	//glm::vec2 velocity;
	//bool isShot;

	std::string colour;

	virtual bool Shoot(void);

	int AmmoLeft(void) {
		return this->BatteryLeft;
	}

	// private:
	// 	int shoeSize;

	int BatteryLeft;

};
