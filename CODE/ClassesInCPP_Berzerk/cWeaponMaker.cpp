#include "cWeaponMaker.h"
#include "cRayGun.h"
#include "cSword.h"
#include "cMissleLanucher.h"
// 
#include "cRailGun.h"


cWeapon* cWeaponMaker::pMakeWeapon(std::string typeOfWeapon)
{
	
	cWeapon* pTheWeapon = NULL;

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

	if (typeOfWeapon == "Sword")
	{
		pTheWeapon = new cSword();
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
