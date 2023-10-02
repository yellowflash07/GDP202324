#pragma once
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

class iRobot
{
public:
	virtual ~iRobot() {};

	virtual void Attack(void) = 0;

	virtual void Move(glm::vec2 toWhere) = 0;

};

