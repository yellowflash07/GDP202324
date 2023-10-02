#include "cWeaponMaker.h"
#include "cRayGun.h"
#include "cMissleLanucher.h"
// 
#include "cRailGun.h"


iWeapon* cWeaponMaker::pMakeWeapon(std::string typeOfWeapon)
{
	
	iWeapon* pTheWeapon = NULL;

	// Pure virtual classes can't be created (instantiated)
//	pTheWeapon = new iWeapon();

	if (typeOfWeapon == "Regular")
	{
		pTheWeapon = new cWeapon();
		return pTheWeapon;
	}

	if (typeOfWeapon == "Ray Gun")
	{
		pTheWeapon = new cRayGun();
		return pTheWeapon;
	}

	if (typeOfWeapon == "A Missle Launcher, please")
	{
		pTheWeapon = new cMissleLauncher();
		return pTheWeapon;
	}

	if (typeOfWeapon == "Snazzy Rail Gun")
	{
		pTheWeapon = new cRailGun();
		return pTheWeapon;
	}	
	
	return NULL;
}
