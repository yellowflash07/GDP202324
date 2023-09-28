#include "cWeapon.h"

#include <iostream>

cWeapon::cWeapon()
{
	// MakeGunCreationSound();
	std::cout << "cWeapon::cWeapon()" << std::endl;
}

cWeapon::~cWeapon()
{
	std::cout << "cWeapon is destroyed" << std::endl;
}
bool cWeapon::Shoot(void)
{
	std::cout << "cWeapon::Shot(void)" << std::endl;
	return;
}
