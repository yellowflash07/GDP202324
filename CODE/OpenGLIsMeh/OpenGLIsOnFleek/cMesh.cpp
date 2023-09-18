#include "cMesh.h"
#include <iostream>			// For KillAllHumans() cout

// Constructor: Called on creation   c'tor
cMesh::cMesh()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = 1.0f;
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

