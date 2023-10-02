#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class cSword 
{
public:
	cSword();
	virtual ~cSword() {};

	// These are all from the iWeapon interface
	virtual glm::vec2 getPosition(void);
	virtual void setPosition(glm::vec2 newPosition);

	void Slash(float power);
	// ****************************************

	glm::vec2 position;

};

