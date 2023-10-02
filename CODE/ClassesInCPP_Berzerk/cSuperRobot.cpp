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
	
	this->pTheWeapons[0]->Shoot();
	this->pTheWeapons[1]->Shoot();

	this->pTheSword->Slash(100.0f);
	return;
}


void cSuperRobot::Move(glm::vec2 toWhere)
{
	std::cout << "cSuperRobot moves to " << toWhere.x << ", " << toWhere.y << std::endl;
	std::cout << "(and makes WAY more noise because it's way bigger, or something" << std::endl;
	return;
}