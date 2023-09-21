#ifndef _cPlayer_HG_
#define _cPlayer_HG_

#include <glm/glm.hpp>
#include <glm/vec2.hpp>


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


};

#endif //_cPlayer_HG_
