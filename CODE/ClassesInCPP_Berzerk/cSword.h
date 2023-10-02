#pragma once
#include "iWeapon.h"

class cSword : public iWeapon
{
public:
	cSword();
	virtual ~cSword() {};

		// These are all from the iWeapon interface
	virtual glm::vec2 getPosition(void);
	virtual void setPosition(glm::vec2 newPosition);

	virtual glm::vec2 getVelocity(void);
	virtual void setVelocity(glm::vec2 newVelocity);

	virtual bool get_isShot(void);
	virtual void set_IsShot(bool bIsShot);

	bool Shoot(void);
	// ****************************************

	glm::vec2 position;
	glm::vec2 velocity;
	bool isShot;

};

