#pragma once

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

// This is an interface class in C++
// The "i" is a possible convention, like using "c" in front of class
// - Only want methods, NEVER data
// - Add a virtual destructor (because if you use virtual once, you'll need it)
// - Make them "pure vitual" by adding a "= 0" at the end of the signature

class iWeapon
{
public:
	virtual ~iWeapon() {};

	virtual glm::vec2 getPosition(void) = 0;
	virtual void setPosition(glm::vec2 newPosition) = 0;

	virtual glm::vec2 getVelocity(void) = 0;
	virtual void setVelocity(glm::vec2 newVelocity) = 0;

	virtual bool get_isShot(void) = 0;
	virtual void set_IsShot(bool bIsShot) = 0;

	virtual bool Shoot(void) = 0;

//	virtual void Swipe(void);

};
