#pragma once

#include "iRobot.h"

#include <string>


class cRobotBuilder
{
public:
	// Returns NULL if an invalid robot is returned
	iRobot* BuildRobot(std::string theRobotWeWant);
};
