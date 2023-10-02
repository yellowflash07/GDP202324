#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "cWeapon.h"

class cMissleLauncher : public cWeapon
{
public:
	cMissleLauncher();
	virtual ~cMissleLauncher() {};

	// These are all from the iWeapon interface
	virtual glm::vec2 getPosition(void);
	virtual void setPosition(glm::vec2 newPosition);

	virtual glm::vec2 getVelocity(void);
	virtual void setVelocity(glm::vec2 newVelocity);

	virtual bool get_isShot(void);
	virtual void set_IsShot(bool bIsShot);

	bool Shoot(void);
	// ****************************************

	//glm::vec2 position;
	//glm::vec2 velocity;
	//bool isShot;


};
