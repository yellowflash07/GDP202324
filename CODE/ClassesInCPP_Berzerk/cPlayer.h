#ifndef _cPlayer_HG_
#define _cPlayer_HG_

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "cRayGun.h"
#include "cWeapon.h"

enum eWeaponType
{
	NONE,							// 0
	RAY_GUN,						// 1
	MISSLE_LAUNCHER
};


class cPlayer 
{
public:
	cPlayer();		// constructor (c'tor)
	~cPlayer();		// destructor (d'tor)

	void Shoot(void);
	void Move(glm::vec2 newdirection);

	glm::vec2 position;	// xy position
	bool bIsAlive;
	glm::vec2  direction;

	cWeapon* pTheWeapon;

};

#endif //_cPlayer_HG_
