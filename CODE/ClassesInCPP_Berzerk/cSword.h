#pragma once
#include "cWeapon.h"

class cSword : public cWeapon
{
public:
	cSword();
	virtual ~cSword() {};

	void Shoot(void);
};

