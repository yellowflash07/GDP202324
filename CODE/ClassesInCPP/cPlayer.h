#ifndef _cPlayer_HG_
#define _cPlayer_HG_

class cPlayer
{
public:
	cPlayer();		// constructor (c'tor)
	~cPlayer();		// destructor (d'tor)

	void Shoot(void);
	void Move(float newdirection[2]);

	float position[2];	// xy position
	bool bIsAlive;
	float direction[2];


};

#endif //_cPlayer_HG_
