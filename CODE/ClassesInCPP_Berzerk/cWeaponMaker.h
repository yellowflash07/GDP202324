#pragma once

#include "iWeapon.h"
//#include "cWeapon.h"
// Do NOT add the includes for the spec
#include <string>

class cWeaponMaker
{
public:
	cWeaponMaker() {};

	// Return the base class
	// Pass a known (primitive or native type) NOT a custom type or ENUM
	// If you pass an unknown type, it returns NULL (or 0)
	iWeapon* pMakeWeapon(std::string typeOfWeapon);

};