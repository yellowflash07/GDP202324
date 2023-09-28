#include "cSuperRobot.h"

#include <iostream>

cSuperRobot::cSuperRobot()
{
	std::cout << "SuperRobot!" << std::endl;
	// Make it stop....
}

void cSuperRobot::Attack(void)
{
	std::cout << "SuperRobot Attacks! " << std::endl;
	this->pTheWeapon->Shoot();
	this->pThe_2nd_Weapon->Shoot();
	return;
}
