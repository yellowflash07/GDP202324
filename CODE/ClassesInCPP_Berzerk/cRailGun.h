#pragma once
#include "cWeapon.h"

class cRailGun : public cWeapon
{
public:
	cRailGun() {};;
	virtual ~cRailGun() {};

	void Shoot(void);
};