#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include "cWeapon.h"
#include <string>

class cRayGun : public cWeapon
{
public:
	cRayGun();
	virtual ~cRayGun();

	// These are all from the iWeapon interface
	virtual glm::vec2 getPosition(void);
	virtual void setPosition(glm::vec2 newPosition);

	virtual glm::vec2 getVelocity(void);
	virtual void setVelocity(glm::vec2 newVelocity);

	virtual bool get_isShot(void);
	virtual void set_IsShot(bool bIsShot);

	bool Shoot(int numBullets);
	// ****************************************

	std::string colour;

	int AmmoLeft(void) {
		return this->BatteryLeft;
	}

	// private:
	// 	int shoeSize;

	int BatteryLeft;

};
