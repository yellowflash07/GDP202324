#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "cWeapon.h"

class cMissleLauncher : public cWeapon
{
public:
	cMissleLauncher();
	virtual ~cMissleLauncher() {};

	//glm::vec2 position;
	//glm::vec2 velocity;
	//bool isShot;

	bool Shoot(void);

};
