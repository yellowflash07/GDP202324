#ifndef _cPhysics_HG_
#define _cPhysics_HG_

// This manages all the physics stuff
#include "sPhsyicsProperties.h"
#include "cVAOManager/cVAOManager.h"		// For the mesh indirect
#include <vector>

class cPhysics
{
public:
	cPhysics();
	~cPhysics();

	void setVAOManager(cVAOManager* pTheMeshManager);

	// Once you pass this in, the cPhysics handles the lifetime
	// (i.e. IT will call delete)
	// When added, if a mesh is present, the drawPosition, etc. are set
	void AddShape(sPhsyicsProperties* pNewShape);

	void Update(double deltaTime);

	// returns NULL if not found
	sPhsyicsProperties* findShapeByUniqueID(unsigned int uniqueIDtoFind);
	sPhsyicsProperties* findShapeByFriendlyName(std::string friendlyNameToFind);

	// Vector is empty if none found
	std::vector<sPhsyicsProperties*> findShapesByType(sPhsyicsProperties::eShape shapeType);
	// Returns false if none found
	bool findShapesByType(sPhsyicsProperties::eShape shapeType, std::vector<sPhsyicsProperties*> &vecShapes);

private:
	std::vector< sPhsyicsProperties* > m_vec_pPhysicalProps;
	
	bool m_Sphere_Sphere_IntersectionTest(sPhsyicsProperties* pSphereA, sPhsyicsProperties* pShpereB);
	bool m_Sphere_Plane_IntersectionTest(sPhsyicsProperties* pSphere, sPhsyicsProperties* pPlane);
	bool m_Sphere_Triangle_IntersectionTest(sPhsyicsProperties* pSphere, sPhsyicsProperties* pTriangle);
	bool m_Sphere_AABB_IntersectionTest(sPhsyicsProperties* pSphere, sPhsyicsProperties* pAABB);
	bool m_Sphere_Capsule_IntersectionTest(sPhsyicsProperties* pSphere, sPhsyicsProperties* pCapsule);
	bool m_Sphere_TriMeshIndirect_IntersectionTest(sPhsyicsProperties* pSphere, sPhsyicsProperties* pTriMesh);
	bool m_Sphere_TriMeshLocal_IntersectionTest(sPhsyicsProperties* pSphere, sPhsyicsProperties* pTriMesh);


	// The basic tests
	bool m_TestSphereTriangle(float sphereRadius, glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 sphereCentre);
	glm::vec3 m_ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

	cVAOManager* m_pMeshManager = NULL;
};

#endif // _cPhysics_HG_