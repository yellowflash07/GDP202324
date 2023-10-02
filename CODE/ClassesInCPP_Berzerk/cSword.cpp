#include "cSword.h"
#include <iostream>

cSword::cSword()
{
}

void cSword::Slash(float power)
{
	std::cout << "cSword::Slash() with power = " << power << std::endl;
	return;
}


glm::vec2 cSword::getPosition(void)
{
	return this->position;
}

void cSword::setPosition(glm::vec2 newPosition)
{
	this->position = newPosition;
	return;
}

