#pragma once

// Super Robot is just like the robot, but 
//	it's faster (I quess) or maybe has a differnet mesh
// BUT it can use a missle launcher or a regular weapon
//  and it dual weilds. 

//#include "cMissleLanucher.h"
#include "cRobot.h"
//#include "cSword.h"

class cSuperRobot : public cRobot
{
public:
	cSuperRobot();
	virtual ~cSuperRobot() {};

	cWeapon* pThe_2nd_Weapon;
//	cSword* pTheSword;
//	cWeapon* pTheSword;

	void Attack(void);
};

