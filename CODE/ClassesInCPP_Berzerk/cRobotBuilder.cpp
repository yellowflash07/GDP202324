#include "cRobotBuilder.h"

// 
#include "cRobot.h"
#include "cSuperRobot.h"
// Types of things I need to "build" a robot
#include "cWeaponMaker.h"
#include "cSword.h"

iRobot* cRobotBuilder::BuildRobot(std::string theRobotWeWant)
{
	cWeaponMaker* pWeaponMaker = new cWeaponMaker();

	if (theRobotWeWant == "Robot")
	{
		cRobot* pARegularRobot = new cRobot();

		pARegularRobot->pTheWeapon = pWeaponMaker->pMakeWeapon("Snazzy Rail Gun");

		return pARegularRobot;

	}
	if (theRobotWeWant == "Super Robot")
	{
		cSuperRobot* pSR = new cSuperRobot();

		pSR->pTheSword = new cSword();
		pSR->pTheWeapons[0] = pWeaponMaker->pMakeWeapon("Regular");
		pSR->pTheWeapons[1] = pWeaponMaker->pMakeWeapon("A Missle Launcher, please");
		return pSR;
	}


	// What are you talking about??
	return NULL;
}

