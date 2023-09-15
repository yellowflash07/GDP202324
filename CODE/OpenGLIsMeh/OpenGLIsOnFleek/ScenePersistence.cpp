
#include <string>
#include <fstream>
#include "cMesh.h"
#include <vector>



// Save the scene to a file

//g_vecMeshesToDraw
//
extern std::vector<cMesh> g_vecMeshesToDraw;

bool SaveVectorSceneToFile( std::string saveFileName )
{

	// "O" for "output" file stream
	std::ofstream theSameFile(saveFileName.c_str());

	for ( unsigned int index = 0; index != g_vecMeshesToDraw.size(); index++ )
	{
		theSameFile << g_vecMeshesToDraw[index].meshName << std::endl;
		theSameFile << g_vecMeshesToDraw[index].position.x << " "
					<< g_vecMeshesToDraw[index].position.y << " "
					<< g_vecMeshesToDraw[index].position.z << std::endl;
		// And so on....
	}

	return true;
}

bool LoadVectorSceneToFile( std::string loadFileName )
{

	// "i" for "output" file stream
	std::ifstream theSameFile(loadFileName.c_str());

	for ( unsigned int index = 0; index != g_vecMeshesToDraw.size(); index++ )
	{
		theSameFile >> g_vecMeshesToDraw[index].meshName;
		theSameFile >> g_vecMeshesToDraw[index].position.x
					>> g_vecMeshesToDraw[index].position.y
					>> g_vecMeshesToDraw[index].position.z;
		// And so on....
	}

	return true;
}