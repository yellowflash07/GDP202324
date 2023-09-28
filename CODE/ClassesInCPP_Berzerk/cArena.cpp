#include "cArena.h"

//#include "cWeapon.h"
//#include "cRayGun.h"

cArena::cArena()
{
	this->pTheWeaponFactory = new cWeaponMaker();
}

cArena::~cArena()
{
	delete this->pTheWeaponFactory;
}


void cArena::Init(int numRobots, int numPlayers)
{
	for ( unsigned int count = 0; count != numRobots; count++ )
	{
		cRobot* pARobot = new cRobot();

//		pARobot->pTheWeapon = new cWeapon();
		pARobot->pTheWeapon = this->pTheWeaponFactory->pMakeWeapon("Snazzy Rail Gun");

		this->vecRobots.push_back(pARobot);
	}

	for ( unsigned int count = 0; count != 2; count++ )
	{
		cSuperRobot* pARobot = new cSuperRobot();

//		pARobot->pTheWeapon = new cWeapon();
//		pARobot->pThe_2nd_Weapon = new cMissleLauncher();
		pARobot->pTheWeapon =this->pTheWeaponFactory->pMakeWeapon("Regular");
		pARobot->pThe_2nd_Weapon = this->pTheWeaponFactory->pMakeWeapon("A Missle Launcher, please");

		this->vecRobots.push_back(pARobot);

	}
	for (unsigned int count = 0; count != numPlayers; count++)
	{
		cPlayer* pAPlayer = new cPlayer();

//		pAPlayer->pTheWeapon = new cRayGun();
		pAPlayer->pTheWeapon = this->pTheWeaponFactory->pMakeWeapon("Ray Gun");

		this->vecPlayers.push_back(pAPlayer);
	}


	return;
}

void cArena::Update(void)
{

	for (unsigned int index = 0; index != this->vecRobots.size(); index++)
	{
		this->vecRobots[index]->Attack();
	}


	for (unsigned int index = 0; index != this->vecPlayers.size(); index++)
	{
		this->vecPlayers[index]->Attack();
	}

	return;
}