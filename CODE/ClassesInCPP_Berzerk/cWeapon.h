#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class cWeapon
{
public:
	cWeapon();
	virtual ~cWeapon();


	glm::vec2 position;
	glm::vec2 velocity;
	bool isShot;

	virtual void Shoot(void);
	void KillAllHumans(void);

protected:			// Externally private, but parent objects see this as private
	int shoeSize;

};

