#pragma once

// Super Robot is just like the robot, but 
//	it's faster (I quess) or maybe has a differnet mesh
// BUT it can use a missle launcher or a regular weapon
//  and it dual weilds. 

//#include "cMissleLanucher.h"
#include "iRobot.h"
#include "iWeapon.h"
#include "cSword.h"

class cSuperRobot : public iRobot
{
public:
	cSuperRobot();
	virtual ~cSuperRobot() {};

	// Has two weapons...
	iWeapon* pTheWeapons[2];
	// ... and a sword!
	cSword* pTheSword;

	// From iRobot interface
	virtual void Attack(void);
	virtual void Move(glm::vec2 toWhere);
};

