#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

//#include "cRayGun.h"
#include "cWeapon.h"

class cRobot 
{
public:
	cRobot();		// constructor (c'tor)
	~cRobot();		// destructor (d'tor)
	glm::vec2 pos;	// xy position
	bool bIsDead;
	glm::vec2 dir;	// direction
	bool bNoticedPlayer;

	cWeapon* pTheWeapon;

	virtual void Attack(void);
};

struct sBullet
{

};