#ifndef _cMesh_HG_
#define _cMesh_HG_

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

// This is where we are going to head...
struct sPhsyicsProperties
{
	sPhsyicsProperties()
	{
		this->position = glm::vec3(0.0f);
		this->velocity = glm::vec3(0.0f);
		this->acceleration = glm::vec3(0.0f);
		this->inverse_mass = 1.0f;	// What should this be??
	}

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	// Since division is "slow" and we are dividing my mass, 
	float inverse_mass;	//	float mass;		

	// Rotational
//	glm::vec3 momentOfWhatever;
//	glm::vec3 rotationalSpeed;
};


class cMesh
{
public:
	cMesh();		// Called on creation   c'tor
	~cMesh();		// Called on deletion   d'tor

	std::string meshName;

	std::string friendlyName;		// "Ground"

	// Physics properties
	//glm::vec3 position;
	sPhsyicsProperties physProps;


	glm::vec3 orientation;
	float scale;

	bool bIsWireframe;
	bool bDoNotLight;


};

#endif

