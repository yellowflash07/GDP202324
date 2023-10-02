#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

//#include "cRayGun.h"
#include "iWeapon.h"
#include "iRobot.h"

class cRobot : public iRobot
{
public:
	cRobot();		// constructor (c'tor)
	~cRobot();		// destructor (d'tor)
	glm::vec2 pos;	// xy position
	bool bIsDead;
	glm::vec2 dir;	// direction
	bool bNoticedPlayer;

	iWeapon* pTheWeapon;

	// From iRobot interface
	virtual void Attack(void);
	virtual void Move(glm::vec2 toWhere);
};




