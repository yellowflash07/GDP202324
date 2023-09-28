#pragma once

#include "cPlayer.h"
#include "cRobot.h"
#include "cSuperRobot.h"
#include "cWeaponMaker.h"	// Factory object
#include <vector>

class cArena
{
public:
	cArena();
	~cArena();
	void Init(int numRobots, int numPlayers);


	void Update(void);
private:

	std::vector< cRobot* > vecRobots;
	std::vector< cPlayer* > vecPlayers;

	cWeaponMaker* pTheWeaponFactory;

};
