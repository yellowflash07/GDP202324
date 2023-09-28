#include "cRayGun.h"
#include <iostream>

cRayGun::cRayGun()
{
	std::cout << "cRayGun is created" << std::endl;
}
cRayGun::~cRayGun()
{
	std::cout << "cRayGun is destroyed" << std::endl;
}


bool cRayGun::Shoot(void)
{
	std::cout << "RayGun goes Bzzzzzzt!" << std::endl;
	return true;
}


