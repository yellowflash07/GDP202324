#pragma once

#include "cPlayer.h"
#include "cRobot.h"
#include "cSuperRobot.h"
#include "cWeaponMaker.h"	// Factory object
#include <vector>

class cArena
{
public:
	~cArena();
	void Init(int numRobots, int numPlayers);


	void Update(void);

	// Any static variable is available even if the object
	//	isn't created yet;
	static cArena* getTheArena(void);

	static int hi;

private:
	cArena();

	std::vector< cRobot* > vecRobots;
	std::vector< cPlayer* > vecPlayers;

	cWeaponMaker* pTheWeaponFactory;

	// Static means "shared" because there's only one
	static cArena* m_pTheOneAndOnlyArena;

};
