#include "cPlayer.h"
#include "cBullet.h"

#include <iostream>

void cPlayer::Shoot(void)
{
	// Create a bullet
//	cBullet bullet;			// STACK

	//this->bullet.isShot = true;

	//// Set the direction on the bullet
	//this->bullet.direction = this->direction;
	//this->bullet.position = this->position;
	//this->bullet.velocity = 1.0f;



	return;
}

void cPlayer::Attack(void)
{
	std::cout << "Player Attacks!" << std::endl;

	this->pTheWeapon->Shoot();
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


