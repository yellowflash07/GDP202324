#include "cMesh.h"
#include <vector>

extern std::vector< cMesh* > g_vec_pMeshesToDraw;

float getRandomFloat(float a, float b);

bool LoadModels(void)
{

        // bun_zipper_res2_xyz_n_rgba.ply
    // bathtub_xyz_n_rgba.ply

//    // Add some models to the "scene"
//    cMesh bunny1;   
//    bunny1.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
//    bunny1.position = glm::vec3(-1.0f, 0.0f, 0.0f);
//    bunny1.scale = 10.0f;
//    bunny1.orientation.x = glm::radians(45.0f);
//
//    cMesh bunny2;
//    bunny2.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
//    bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    bunny2.scale = 7.5f;
//    bunny2.orientation.y = glm::radians(135.0f);
//
//    cMesh bathtub;
//    bathtub.meshName = "bathtub_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    bathtub.scale = 0.25f;
//
////    // Smart array of cMesh object
////    std::vector<cMesh> vecMeshesToDraw;
//    g_vecMeshesToDraw.push_back(bunny1);
//    g_vecMeshesToDraw.push_back(bunny2);
//    g_vecMeshesToDraw.push_back(bathtub);
//    g_vecMeshesToDraw.push_back(terrain);

//    cMesh* pTerrain = new cMesh();
//    pTerrain->meshName = "Terrain_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    pTerrain->scale = 1.0f;
//    pTerrain->drawPosition.y = -25.0f;
//    ::g_vec_pMeshesToDraw.push_back(pTerrain);


//    cMesh* pGridGroundMesh = new cMesh();
//    pGridGroundMesh->meshName = "Flat_Grid_100x100.ply";
    //pGridGroundMesh->bIsWireframe = true;
    //pGridGroundMesh->bDoNotLight = true;
    // note this does NOT have a physProps, so is ignored by the physics update loop
//    pGridGroundMesh->drawPosition.y = 0.0f;   //  0,-10,0
//    pGridGroundMesh->friendlyName = "Ground";
//    ::g_vec_pMeshesToDraw.push_back(pGridGroundMesh);

    cMesh* pFlat_1x1_planeMesh = new cMesh();
    pFlat_1x1_planeMesh->meshName = "Flat_1x1_plane.ply";
    //pFlat_1x1_planeMesh->bIsWireframe = true;
    //pFlat_1x1_planeMesh->bDoNotLight = true;
    // note this does NOT have a physProps, so is ignored by the physics update loop
    pFlat_1x1_planeMesh->drawPosition.y = -5.0f;   //  0,-10,0
    pFlat_1x1_planeMesh->drawPosition.x = 10.0f;
    pFlat_1x1_planeMesh->friendlyName = "Ground";
    //
    pFlat_1x1_planeMesh->orientation.z = glm::radians(+12.0f);
   ::g_vec_pMeshesToDraw.push_back(pFlat_1x1_planeMesh);

   cMesh* pFlat_1x1_planeMesh_DEBUG = new cMesh();
   pFlat_1x1_planeMesh_DEBUG->meshName = "Flat_1x1_plane.ply";
   pFlat_1x1_planeMesh_DEBUG->bIsWireframe = true;
   pFlat_1x1_planeMesh_DEBUG->bDoNotLight = true;
   pFlat_1x1_planeMesh_DEBUG->bUseDebugColours = true;
   pFlat_1x1_planeMesh_DEBUG->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
   pFlat_1x1_planeMesh_DEBUG->orientation = pFlat_1x1_planeMesh->orientation;
   // note this does NOT have a physProps, so is ignored by the physics update loop
   pFlat_1x1_planeMesh_DEBUG->drawPosition = pFlat_1x1_planeMesh->drawPosition;
//   pFlat_1x1_planeMesh_DEBUG->drawPosition.y += 0.01f;   //  0,-10,0
   ::g_vec_pMeshesToDraw.push_back(pFlat_1x1_planeMesh_DEBUG);


    const float MAX_SPHERE_LOCATION = 30.0f;
    const float MAX_VELOCITY = 1.0f;

    // Make a bunch of spheres...
    const unsigned int NUMBER_OF_SPHERES = 1;
    for (unsigned int count = 0; count != NUMBER_OF_SPHERES; count++)
    {
        cMesh* pSphereMesh = new cMesh();
        pSphereMesh->meshName = "Sphere_1_unit_Radius.ply";
        //pSphereMesh->bIsWireframe = true;
        //pSphereMesh->bDoNotLight = true;

        pSphereMesh->friendlyName = "Sphere";

//        sphereMesh.physProps.velocity.y = 0.0f;
        sPhsyicsProperties* pSpherePhysProps = new sPhsyicsProperties();        // HEAP

        pSpherePhysProps->velocity.y = getRandomFloat(0.0f, MAX_VELOCITY);
        pSpherePhysProps->velocity.x = getRandomFloat(-MAX_VELOCITY, MAX_VELOCITY);
        pSpherePhysProps->velocity.z = getRandomFloat(-MAX_VELOCITY, MAX_VELOCITY);

        // Gravity on Earth is likely too fast to look good, so we'll make it smaller.
//        sphereMesh.physProps.acceleration.y = -9.81f;
        pSpherePhysProps->acceleration.y = (-9.81f / 5.0f);

        pSpherePhysProps->position.x = getRandomFloat(-MAX_SPHERE_LOCATION, MAX_SPHERE_LOCATION);
        pSpherePhysProps->position.z = getRandomFloat(-MAX_SPHERE_LOCATION, MAX_SPHERE_LOCATION);
        pSpherePhysProps->position.y = getRandomFloat(10.0f, MAX_SPHERE_LOCATION + 20.0f);

        pSphereMesh->pPhysProps = pSpherePhysProps;
        // Copy the physics position to the drawing position
        pSphereMesh->drawPosition = pSpherePhysProps->position;

        ::g_vec_pMeshesToDraw.push_back(pSphereMesh);


        //cMesh shpereMeshShadow_HACK;
        //shpereMeshShadow_HACK.meshName = "Sphere_1_unit_Radius.ply";
        //shpereMeshShadow_HACK.bIsWireframe = false;
        //shpereMeshShadow_HACK.bDoNotLight = true;
//        shpereMeshShadow_HACK.
//        shpereMeshShadow_HACK.friendlyName = "Sphere";


    }//for ( unsigned int count...

    cMesh* pDebugSphere = new cMesh();
    pDebugSphere->meshName = "Sphere_1_unit_Radius.ply";
    pDebugSphere->bIsWireframe = true;
    pDebugSphere->bDoNotLight = true;
    pDebugSphere->scale = 25.0f;
    pDebugSphere->pPhysProps = NULL;
    pDebugSphere->bIsVisible = false;
    pDebugSphere->friendlyName = "DEBUG_SPHERE";

    ::g_vec_pMeshesToDraw.push_back(pDebugSphere);



    return true;
}
