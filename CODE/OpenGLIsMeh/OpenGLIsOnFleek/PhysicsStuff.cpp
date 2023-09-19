// PhysicsStuff.cpp

#include <glm/glm.hpp>
#include <vector>
#include "cMesh.h"

extern std::vector<cMesh> g_vecMeshesToDraw;

void DoPhysicUpdate(double deltaTime)
{

	for (unsigned int index = 0; index != ::g_vecMeshesToDraw.size(); index++)
	{
// ***********************************************************************
		// Explicit forward Euler "integration step"

//		NewVelocity = LastVel + (Accel * DeltaTime)
//		NewPosition = LastPos + (Vel * DeltaTime)	

		// Velocity change is based on the acceleration over this time frame 
//		// This part: (Accel * DeltaTime)
		glm::vec3 deltaVelocityThisFrame = g_vecMeshesToDraw[index].physProps.acceleration * (float)deltaTime;

		// Update the velocity based on this delta velocity
		// Then this part: NewVelocity = LastVel + ...
		g_vecMeshesToDraw[index].physProps.velocity += deltaVelocityThisFrame;


		// Position change is based on the velocity over this time frame
		// This part: (Vel * DeltaTime)	
		glm::vec3 deltaPosition = g_vecMeshesToDraw[index].physProps.velocity * (float)deltaTime;

		// ...then this part: NewPosition = LastPos + ...
		// Upatate the position based on this delta position
		g_vecMeshesToDraw[index].physProps.position += deltaPosition;
// ***********************************************************************


// ***********************************************************************
		// HACK:Collision detection and response

		// Our ground object is at -10.0f

		// See if our sphere "hits" the ground
		// For spheres, if the ground <= radius of the sphere, it's "hit"
		// Our model has radius of 1.0f


		const float GROUND_LOCATION_Y = -10.0f;

		// Is this a sphere? 
		if (::g_vecMeshesToDraw[index].friendlyName == "Sphere")
		{
			if ( (::g_vecMeshesToDraw[index].physProps.position.y - 1.0f) <= GROUND_LOCATION_Y)
			{
				// "Invert" the velocity
				// Velocity goes "up" +ve.
				float newVel = fabs(::g_vecMeshesToDraw[index].physProps.velocity.y);

				::g_vecMeshesToDraw[index].physProps.velocity.y = newVel;

			}
		}


// ***********************************************************************


	}

	return;
}