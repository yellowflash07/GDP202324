#ifndef _cMesh_HG_
#define _cMesh_HG_

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

#include "sTransformInfo.h"
#include "iTransformInfoAccessor.h"

class cMesh : public iTransformInfoAccessor
{
public:
	cMesh();		// Called on creation   c'tor
	~cMesh();		// Called on deletion   d'tor

	std::string meshName;

	std::string friendlyName;		// "Ground"


public:
	// From the iTransformInfoAccessor interface
	virtual sTransformInfo getTransformInfo(void);
	virtual void setTransformInfo(sTransformInfo newTransformInfo);
private:
	// Draw loop uses this: 
/*	glm::vec3 drawPosition;
	glm::vec3 drawOrientation;
	float drawScale;*/	
	sTransformInfo transformInfo;

public:
	bool bIsVisible;

	bool bUseDebugColours;
	glm::vec4 wholeObjectDebugColourRGBA;

	// Physics properties
	// Physics update this:
//	sPhsyicsProperties* pPhysProps;

	bool bIsWireframe;
	bool bDoNotLight;

	void Update(double deltaTime);

};

#endif

