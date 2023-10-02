#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "sTransformInfo.h"
#include "iTransformInfoAccessor.h"


// This is where we are going to head...
struct sPhsyicsProperties
{
	// How the physics item knows what type of object this is
	enum eShape
	{
		UNKNOWN_OR_UNDEFINED,
		SPHERE,
		PLANE,
		AABB,
		CAPSULE,
		MESH
	};

	sPhsyicsProperties()
	{
		this->velocity = glm::vec3(0.0f);
		this->acceleration = glm::vec3(0.0f);
		this->inverse_mass = 1.0f;	// What should this be??
		//
		this->pTheAssociatedMesh = NULL;
		//
		this->shapeType = UNKNOWN_OR_UNDEFINED;
		//
		this->sphere_radius = 0.0f;
		this->direction = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	sTransformInfo transformInfo;

	glm::vec3 velocity;
	glm::vec3 acceleration;

	eShape shapeType;

	// Here we list the specific properties of the shape type
	// Some of these are part of the transformInfo
	// 
	// SPHERE:
	float sphere_radius;
	// centre is sTransformInfo.position
	// 
	// PLANE:
	glm::vec3 direction;
	// centre is sTransformInfo.position
	
	

	// Since division is "slow" and we are dividing my mass, 
	// Could make this immovable by making this 0 (infinite mass)
	float inverse_mass;	//	float mass;		

//	cMesh* pTheAssociatedMesh;
	iTransformInfoAccessor* pTheAssociatedMesh;

	// Rotational
//	glm::vec3 momentOfWhatever;
//	glm::vec3 rotationalSpeed;
};
