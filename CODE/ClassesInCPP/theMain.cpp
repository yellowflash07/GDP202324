#include "cPlayer.h"
#include "cRobot.h"
#include "cBullet.h"
#include <iostream>

void DoTheGame()
{
}

int main()
{
//	cPlayer bob;		// Stack

	cPlayer* pBob = new cPlayer();		// HEAP

	const unsigned int NUM_ROBOTS = 8;

	cRobot* pRobots = new cRobot[NUM_ROBOTS];	// Heap

	cBullet PlayersBullet;

//	cRobot theRobots[NUM_ROBOTS];			// Stack

	// Place player and robots...

	// Game loop
	{
		// ASsume player presses "shoot" and a director	
		std::cout << "Player shoots..." << std::endl;
		pBob->Shoot();
		std::cout << "Player shot!" << std::endl;


	}



//	delete pRobots;		// YIKES! GOTCHA!! BEWARE
	delete [] pRobots;
	
	delete pBob;

	return 0;
}
