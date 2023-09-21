#ifndef _cPlayer_HG_
#define _cPlayer_HG_

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#include "cMissleLanucher.h"
#include "cRayGun.h"

enum eWeaponType
{
	NONE,							// 0
	RAY_GUN,						// 1
	MISSLE_LAUNCHER
};


class cPlayer : private cRayGun
{
public:
	cPlayer();		// constructor (c'tor)
	~cPlayer();		// destructor (d'tor)

	void Shoot(void);
	void Move(glm::vec2 newdirection);

	glm::vec2 position;	// xy position
	bool bIsAlive;
	glm::vec2  direction;

//	cBullet bullet;			

//	cRayGun* pWeapon1 = new cRayGun();
//	cMissleLauncher* pWeapon2 = new cMissleLauncher();

	cWeapon* pTheWeapon = new cRayGun();
//	cWeapon* pTheWeapon = new cMissleLauncher();


	//bool hasRayGun;
	//bool hasMissleLaucher;
	eWeaponType weaponType;
};

#endif //_cPlayer_HG_
