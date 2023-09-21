#include "cMesh.h"
#include <iostream>			// For KillAllHumans() cout

// Constructor: Called on creation   c'tor
cMesh::cMesh()
{
//	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = 1.0f;

	this->bIsWireframe = false;
	this->bDoNotLight = false;

	// If it's NULL or 0, then it's ignored by the physics loop
	this->pPhysProps = NULL;		// or 0 or nullptr

}

// Destructor: Called on deletion   d'tor
cMesh::~cMesh()
{

}

//void cMesh::KillAllHumans(void)
//{
//	std::cout << "Kill all humans!" << std::endl;
//	return;
//}

