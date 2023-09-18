#pragma once

class cRobot
{
public:
	cRobot();		// constructor (c'tor)
	~cRobot();		// destructor (d'tor)
	float pos[2];	// xy position
	bool bIsDead;
	float dir[2];
	bool bNoticedPlayer;
};

struct sBullet
{

};