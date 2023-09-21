#include "cPlayer.h"
#include "cBullet.h"

#include <iostream>

void cPlayer::Shoot(void)
{
	// Create a bullet
	cBullet bullet;			// STACK
	// Set the direction on the bullet
	bullet.direction[0] = this->direction[0];
	bullet.direction[1] = this->direction[1];
	bullet.position[0] = this->position[0];
	bullet.position[1] = this->position[1];
	bullet.velocity = 1.0f;

	{
		cBullet bullet2;			// STACK
	}

	return;
}



// constructor (c'tor)
cPlayer::cPlayer()
{
	std::cout << "cPlayer::cPlayer()" << std::endl;

	this->position[0] = 0.0f;
	this->position[1] = 0.0f;	// xy position

	this->bIsAlive = true;

	this->direction[0] = 1.0f;
	this->direction[1] = 0.0f;	
}

// destructor (d'tor)
cPlayer::~cPlayer()
{
	std::cout << "cPlayer::~cPlayer()" << std::endl;
}


