#pragma once

#include "iWeapon.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class cWeapon : public iWeapon
{
public:
	cWeapon();
	virtual ~cWeapon();

	// These are all from the iWeapon interface
	virtual glm::vec2 getPosition(void);
	virtual void setPosition(glm::vec2 newPosition);

	virtual glm::vec2 getVelocity(void);
	virtual void setVelocity(glm::vec2 newVelocity);

	virtual bool get_isShot(void);
	virtual void set_IsShot(bool bIsShot);

	bool Shoot(void);
	// ****************************************


	int AmmoLeft(void) {
		return this->ammo; 
	}



protected:			// Externally private, but parent objects see this as private
	int shoeSize;
	int ammo;
	glm::vec2 position;
	glm::vec2 velocity;
	bool isShot;

};

