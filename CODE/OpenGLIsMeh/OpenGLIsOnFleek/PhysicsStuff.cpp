// PhysicsStuff.cpp

#include "OpenGLCommon.h"
#include <glm/glm.hpp>
#include <vector>
#include "cMesh.h"
#include <iostream>

#include "cGlobal.h"

#include "cVAOManager/cVAOManager.h"
// This is defined in main
extern cVAOManager* g_pMeshManager;

extern std::vector< cMesh* > g_vec_pMeshesToDraw;


// Using this so that I can see the locations of the "closest point to the triangle"
void DrawObject(cMesh* pCurrentMesh, glm::mat4 matModel,
				glm::mat4 matProjection, glm::mat4 matView,
				GLuint shaderProgramID);			// OpenGL common 

// reutrns NULL if we DIDN'T find the object
cMesh* findObjectByFriendlyName(std::string friendlyNameToFind)
{
	for ( unsigned int index = 0; index != ::g_vec_pMeshesToDraw.size(); index++ )
	{
		// This it? 
		cMesh* pCurrentMesh = ::g_vec_pMeshesToDraw[index];

		if (pCurrentMesh->friendlyName == friendlyNameToFind)
		{
			return pCurrentMesh;
		}
	}

	// Didn't find it
	return NULL;
}

glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

void DoPhysicUpdate(double deltaTime)
{

	// Find the debug sphere
	cMesh* pDebugSphere = findObjectByFriendlyName("DEBUG_SPHERE");


	for (unsigned int meshIndex = 0; meshIndex != ::g_vec_pMeshesToDraw.size(); meshIndex++)
	{

		cMesh* pCurrentMesh = ::g_vec_pMeshesToDraw[meshIndex];

		if (pCurrentMesh->pPhysProps == NULL )
		{
			// Skip this.
			continue;
		}

// ***********************************************************************
		// Explicit forward Euler "integration step"

//		NewVelocity = LastVel + (Accel * DeltaTime)
//		NewPosition = LastPos + (Vel * DeltaTime)	

		// Velocity change is based on the acceleration over this time frame 
//		// This part: (Accel * DeltaTime)
		glm::vec3 deltaVelocityThisFrame = pCurrentMesh->pPhysProps->acceleration * (float)deltaTime;

		// Update the velocity based on this delta velocity
		// Then this part: NewVelocity = LastVel + ...
		pCurrentMesh->pPhysProps->velocity += deltaVelocityThisFrame;


		// Position change is based on the velocity over this time frame
		// This part: (Vel * DeltaTime)	
		glm::vec3 deltaPosition = pCurrentMesh->pPhysProps->velocity * (float)deltaTime;

		// ...then this part: NewPosition = LastPos + ...
		// Upatate the position based on this delta position
//		pCurrentMesh->pPhysProps->position += deltaPosition;
		pCurrentMesh->pPhysProps->position.x += deltaPosition.x;
		pCurrentMesh->pPhysProps->position.y += deltaPosition.y;
		pCurrentMesh->pPhysProps->position.z += deltaPosition.z;
// ***********************************************************************


// ***********************************************************************
	// HACK:Collision detection and response

	// Our ground object is at -10.0f

	// See if our sphere "hits" the ground
	// For spheres, if the ground <= radius of the sphere, it's "hit"
	// Our model has radius of 1.0f


//		const float GROUND_LOCATION_Y = -10.0f;
		const float GROUND_LOCATION_Y = 0.0f;

		// Is this a sphere? 
		if (pCurrentMesh->friendlyName == "Sphere")
		{
			if ( (pCurrentMesh->pPhysProps->position.y - 1.0f) <= GROUND_LOCATION_Y)
			{
				// "Invert" the velocity
				// Velocity goes "up" +ve.
				float newVel = fabs(pCurrentMesh->pPhysProps->velocity.y);

				pCurrentMesh->pPhysProps->velocity.y = newVel;

			}
		}

		// Update the draw location with the physics location
		pCurrentMesh->drawPosition = pCurrentMesh->pPhysProps->position;

// ***********************************************************************

		// HACK: Determine what is the closest position to each triangle in 
		//	the ground mesh

//		sModelDrawInfo groundMeshInfo;
//		if (::g_pMeshManager->FindDrawInfoByModelName("Flat_Grid_100x100.ply", groundMeshInfo))
//		{
//			// For each triangle, get the vertices, then pass them to the 
//			//	sphere-triangle collision function, returning the "closest point"
//			for ( unsigned int index = 0; index != groundMeshInfo.numberOfIndices; index += 3 )
//			{	
//				glm::vec3 verts[3];
//
//				verts[0].x = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index] ].x;
//				verts[0].y = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index] ].y;
//				verts[0].z = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index] ].z;
//
//				verts[1].x = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index + 1] ].x;
//				verts[1].y = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index + 1] ].y;
//				verts[1].z = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index + 1] ].z;
//
//				verts[2].x = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index + 2] ].x;
//				verts[2].y = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index + 2] ].y;
//				verts[2].z = groundMeshInfo.pVertices[ groundMeshInfo.pIndices[index + 2] ].z;
//
//				glm::vec3 closestPoint = ClosestPtPointTriangle(pCurrentMesh->drawPosition,
//																verts[0], verts[1], verts[2]);
//
//
////				::g_pDebugRenderer->AddLine(
//
////				// HACK:
////				if (index == 99 )
////				{
////					std::cout << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << std::endl;
////				}
//				//if (pDebugSphere != NULL)
////				if (pDebugSphere)			// NON zero => true, zero = false;
////				{
////					pDebugSphere->drawPosition = closestPoint;
////					pDebugSphere->scale = 0.5f;
////					pDebugSphere->bIsVisible = true;
////
////// HACK: 
////					extern glm::mat4 matProjection;    // "projection"
////					extern glm::mat4 matView;          // "view" or "camera"
////					extern GLuint shaderProgramID;
////
////					DrawObject(pDebugSphere, glm::mat4(1.0f), 
////							   matProjection, matView, shaderProgramID);
////
////					pDebugSphere->bIsVisible = false;
////				}
////
//			}//for ( unsigned int index = 0...
//		}//if (pMeshManager->FindDrawInfoByModelName(

	}// for (unsigned int meshIndex


	return;
}

// From: Real-Time Collision Detection- Ericson, Christer- 9781558607323- Books - Amazon.ca
// https://www.amazon.ca/Real-Time-Collision-Detection-Christer-Ericson/dp/1558607323/ref=pd_lpo_sccl_1/137-6663593-0701065?pd_rd_w=YiI8A&content-id=amzn1.sym.687e7c56-2b08-4044-894f-bbad969cf967&pf_rd_p=687e7c56-2b08-4044-894f-bbad969cf967&pf_rd_r=JWS56NJC99QEH56TYFJX&pd_rd_wg=zBE6V&pd_rd_r=d611733e-ec29-4b30-bd70-89f092f1991a&pd_rd_i=1558607323&psc=1
// Chapter 5:

glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
	float snom = glm::dot(p - a, ab), sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = glm::dot(p - a, ac), tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
	float unom = glm::dot(p - b, bc), udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	glm::vec3 n = glm::cross(b - a, c - a);
	float vc = glm::dot(n, glm::cross(a - p, b - p));
	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = glm::dot(n, glm::cross(b - p, c - p));
	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = glm::dot(n, glm::cross(c - p, a - p));
	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}

// The OG code from the book:
//Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
//{
//	Vector ab = b - a;
//	Vector ac = c - a;
//	Vector bc = c - b;
//
//	// Compute parametric position s for projection P' of P on AB,
//	// P' = A + s*AB, s = snom/(snom+sdenom)
//	float snom = Dot(p - a, ab), sdenom = Dot(p - b, a - b);
//
//	// Compute parametric position t for projection P' of P on AC,
//	// P' = A + t*AC, s = tnom/(tnom+tdenom)
//	float tnom = Dot(p - a, ac), tdenom = Dot(p - c, a - c);
//
//	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out
//
//	// Compute parametric position u for projection P' of P on BC,
//	// P' = B + u*BC, u = unom/(unom+udenom)
//	float unom = Dot(p - b, bc), udenom = Dot(p - c, b - c);
//
//	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
//	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out
//
//
//	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
//	Vector n = Cross(b - a, c - a);
//	float vc = Dot(n, Cross(a - p, b - p));
//	// If P outside AB and within feature region of AB,
//	// return projection of P onto AB
//	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
//		return a + snom / (snom + sdenom) * ab;
//
//	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
//	float va = Dot(n, Cross(b - p, c - p));
//	// If P outside BC and within feature region of BC,
//	// return projection of P onto BC
//	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
//		return b + unom / (unom + udenom) * bc;
//
//	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
//	float vb = Dot(n, Cross(c - p, a - p));
//	// If P outside CA and within feature region of CA,
//	// return projection of P onto CA
//	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
//		return a + tnom / (tnom + tdenom) * ac;
//
//	// P must project inside face region. Compute Q using barycentric coordinates
//	float u = va / (va + vb + vc);
//	float v = vb / (va + vb + vc);
//	float w = 1.0f - u - v; // = vc / (va + vb + vc)
//	return u * a + v * b + w * c;
//}

