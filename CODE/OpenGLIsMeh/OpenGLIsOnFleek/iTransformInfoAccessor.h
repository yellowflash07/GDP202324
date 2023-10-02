#pragma once

#include "sTransformInfo.h"

// Interface class:
// - class
// - virtual destructor
// - ONLY methods
// - ALL methods are vitual 
// - All are PURE vitual ("= 0" at end)

class iTransformInfoAccessor
{
public:
	virtual ~iTransformInfoAccessor() {};

	virtual sTransformInfo getTransformInfo(void) = 0;
	virtual void setTransformInfo(sTransformInfo newTransformInfo) = 0;
};
