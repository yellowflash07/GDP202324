#pragma once
#include "iWeapon.h"

class cRailGun : public iWeapon
{
public:
	cRailGun() {};;
	virtual ~cRailGun() {};

	// These are all from the iWeapon interface
	virtual glm::vec2 getPosition(void);
	virtual void setPosition(glm::vec2 newPosition);

	virtual glm::vec2 getVelocity(void);
	virtual void setVelocity(glm::vec2 newVelocity);

	virtual bool get_isShot(void);
	virtual void set_IsShot(bool bIsShot);

	bool Shoot(int numBullets);
	// ****************************************

	glm::vec2 position;
	glm::vec2 velocity;
	bool isShot;

};