#include "cBullet.h"
#include <iostream>

cBullet::cBullet()
{
	std::cout << "cBullet::cBullet()" << std::endl;
	this->isShot = false;
}

cBullet::~cBullet()
{
	std::cout << "cBullet::~cBullet()" << std::endl;
}