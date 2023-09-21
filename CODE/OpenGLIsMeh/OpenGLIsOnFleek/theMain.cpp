//https://www.glfw.org/docs/latest/quick.html
//http://graphics.stanford.edu/data/3Dscanrep/

#include "OpenGLCommon.h"
//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>      // C++ file IO (secret: it's a wraper for the c IO)
#include <sstream>      // like a string builder
#include <vector>       // Aka a "smart array"


//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "Basic Shader Manager/cShaderManager.h"
#include "cVAOManager/cVAOManager.h"

#include "cMesh.h"

glm::vec3 cameraEye = glm::vec3(0.0, 5.0, +90.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 5.0f, 0.0f);
glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);


cVAOManager* pMeshManager = new cVAOManager();


// Smart array of cMesh object
std::vector<cMesh> g_vecMeshesToDraw;
//std::vector<sPhsyicsProperties*> g_vecThingsThePhysicsThingPaysAtte;
// 
int g_selectedMesh = 0;

// Function signature
bool SaveVectorSceneToFile(std::string saveFileName);

void DoPhysicUpdate(double deltaTime);

// https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float getRandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// This callback is from the "typing" windows system
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_F10 && action)
    {
        // Save the scene to a file
        SaveVectorSceneToFile("myscene.txt");
    }

    const float CAMERA_MOVEMENT_SPEED = 1.0f;
    const float OBJECT_MOVEMENT_SPEED = 0.01f;

    // Is the shift key down
    if ( mods == GLFW_MOD_SHIFT )
    {
        // Shift key ONLY is down
    }

    // & will "mask" off the mod leaving the shift
    if ( ( mods & GLFW_MOD_SHIFT ) == GLFW_MOD_SHIFT )
    {
        // Shift key down (ignores other keys)

//        if (key == GLFW_KEY_A )
//        {
//            ::g_vecMeshesToDraw[::g_selectedMesh].physProps.position.x -= OBJECT_MOVEMENT_SPEED;
//        }
//        if (key == GLFW_KEY_D )
//        {
//            ::g_vecMeshesToDraw[::g_selectedMesh].physProps.position.x += OBJECT_MOVEMENT_SPEED;
//        }
//
//        if (key == GLFW_KEY_W )
//        {
//            ::g_vecMeshesToDraw[::g_selectedMesh].physProps.position.z += OBJECT_MOVEMENT_SPEED;
//        }
//        if (key == GLFW_KEY_S )
//        {
//            ::g_vecMeshesToDraw[::g_selectedMesh].physProps.position.z -= OBJECT_MOVEMENT_SPEED;
//        }
//
//
//        if (key == GLFW_KEY_Q )
//        {
//            ::g_vecMeshesToDraw[::g_selectedMesh].physProps.position.y -= OBJECT_MOVEMENT_SPEED;
//        }
//        if (key == GLFW_KEY_E )
//        {
//            ::g_vecMeshesToDraw[::g_selectedMesh].physProps.position.y += OBJECT_MOVEMENT_SPEED;
//        }

        // Select another model
        if ( key == GLFW_KEY_PAGE_UP )
        {
            ::g_selectedMesh++;
            if ( ::g_selectedMesh > ::g_vecMeshesToDraw.size() )
            {
                ::g_selectedMesh = 0;
            }
            std::cout << "Selcted model: " << ::g_selectedMesh << std::endl;
        }
        if ( key == GLFW_KEY_PAGE_DOWN )
        {
            ::g_selectedMesh--;
            if (::g_selectedMesh < 0 )
            {
                ::g_selectedMesh = ((int)::g_vecMeshesToDraw.size() - 1);
            }
            std::cout << "Selcted model: " << ::g_selectedMesh << std::endl;
        }
    }
    else
    {
        // Shift key is NOT down

        if ( key == GLFW_KEY_A && action )
        {
            cameraEye.x -= CAMERA_MOVEMENT_SPEED;
        }
        if ( key == GLFW_KEY_D && action )
        {
            cameraEye.x += CAMERA_MOVEMENT_SPEED;
        }

        if ( key == GLFW_KEY_W && action )
        {
            cameraEye.z += CAMERA_MOVEMENT_SPEED;
        }
        if ( key == GLFW_KEY_S && action )
        {
            cameraEye.z -= CAMERA_MOVEMENT_SPEED;
        }    
    

        if ( key == GLFW_KEY_Q && action )
        {
            cameraEye.y -= CAMERA_MOVEMENT_SPEED;
        }
        if ( key == GLFW_KEY_E && action )
        {
            cameraEye.y += CAMERA_MOVEMENT_SPEED;
        }     

    }// if ( ( mods & GLFW_MOD_SHIFT ) == GLFW_MOD_SHIFT )
 


    return;
}



int main(void)
{
    std::cout << "About to blow you mind with OpenGL!" << std::endl;

    GLFWwindow* window;
//    GLuint vertex_buffer; //, vertex_shader, fragment_shader;//v , program;
    GLint mvp_location;// , vpos_location, vcol_location;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);


//    if (!LoadTheFile_PlyXYZ("Hey"))
    // if (!LoadTheFile_Ply_XYZ_N_RGBA("Hey"))
    // {

    //    std::cout << "Error: didn't load the file." << std::endl;
    //    std::cout << "How sad." << std::endl;
    //    return -1;
    //}


    // NOTE: OpenGL error checks have been omitted for brevity

//    glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//
////    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    unsigned int size_of_sVertex = sizeof(sVertex);
////    unsigned int number_of_bytes_in_array = size_of_sVertex * NUM_OF_VERTICES;
//    unsigned int number_of_bytes_in_array = size_of_sVertex * g_NumberOfVerticesToDraw;
//
////    glBufferData(GL_ARRAY_BUFFER, number_of_bytes_in_array, vertices, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, number_of_bytes_in_array, pVertices, GL_STATIC_DRAW);

//    cShaderManager ShaderThing;
    cShaderManager* pShaderThing = new cShaderManager();

    cShaderManager::cShader vertexShader;
    vertexShader.fileName = "vertexShader01.glsl";

    cShaderManager::cShader fragmentShader;
    fragmentShader.fileName = "fragmentShader01.glsl";

    if ( ! pShaderThing->createProgramFromFile("shader01", vertexShader, fragmentShader ) )
    {
        std::cout << "Error: Couldn't compile or link:" << std::endl;
        std::cout << pShaderThing->getLastError();
        return -1;
    }


//
    GLuint shaderProgramID = pShaderThing->getIDFromFriendlyName("shader01");

    //cVAOManager* pMeshManager = new cVAOManager();

    //sModelDrawInfo bunnyDrawingInfo;
    //pMeshManager->LoadModelIntoVAO("bun_zipper_res2_xyz_n_rgba.ply",
    //                               bunnyDrawingInfo, shaderProgramID);
    //std::cout << "Loaded: " << bunnyDrawingInfo.numberOfVertices << " vertices" << std::endl;

    //sModelDrawInfo bathtubDrawingInfo;
    //pMeshManager->LoadModelIntoVAO("bathtub_xyz_n_rgba.ply",
    //                               bathtubDrawingInfo, shaderProgramID);
    //std::cout << "Loaded: " << bathtubDrawingInfo.numberOfVertices << " vertices" << std::endl;

    //sModelDrawInfo terrainDrawingInfo;
    //pMeshManager->LoadModelIntoVAO("Terrain_xyz_n_rgba.ply",
    //                               terrainDrawingInfo, shaderProgramID);
    //std::cout << "Loaded: " << terrainDrawingInfo.numberOfVertices << " vertices" << std::endl;

    sModelDrawInfo gridDrawingInfo;
    pMeshManager->LoadModelIntoVAO("Flat_Grid_100x100.ply",
                                   gridDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << gridDrawingInfo.numberOfVertices << " vertices" << std::endl;

    sModelDrawInfo sphereDrawingInfo;
    pMeshManager->LoadModelIntoVAO("Sphere_1_unit_Radius.ply",
                                   sphereDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << sphereDrawingInfo.numberOfVertices << " vertices" << std::endl;

//    sModelDrawInfo BOPModel;
//    pMeshManager->LoadModelIntoVAO("BirdOfPrey_xyz_n_rgba.ply",
//                                   BOPModel, shaderProgramID);
//

    // Load and compile shader part

//    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//    glCompileShader(vertex_shader);
//
//    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//    glCompileShader(fragment_shader);
//
//    GLuint program = glCreateProgram();
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//    glLinkProgram(program);

// 

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
//    cMesh terrain;
//    terrain.meshName = "Terrain_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    terrain.scale = 1.0f;
//    terrain.position.y = -25.0f;
//
////    // Smart array of cMesh object
////    std::vector<cMesh> vecMeshesToDraw;
//    g_vecMeshesToDraw.push_back(bunny1);
//    g_vecMeshesToDraw.push_back(bunny2);
//    g_vecMeshesToDraw.push_back(bathtub);
//    g_vecMeshesToDraw.push_back(terrain);



    cMesh gridGroundMesh;
    gridGroundMesh.meshName = "Flat_Grid_100x100.ply";
    gridGroundMesh.bIsWireframe = true;
    gridGroundMesh.bDoNotLight = true;
    // note this does NOT have a physProps, so is ignored by the physics update loop
    gridGroundMesh.drawPosition.y = 0.0f;   //  0,-10,0
    gridGroundMesh.friendlyName = "Ground";
    ::g_vecMeshesToDraw.push_back(gridGroundMesh);

    const float MAX_SPHERE_LOCATION = 30.0f;
    const float MAX_VELOCITY = 1.0f;

    // Make a bunch of spheres...
    const unsigned int NUMBER_OF_SPHERES = 1;
    for ( unsigned int count = 0; count != NUMBER_OF_SPHERES; count++ )
    {
        cMesh sphereMesh;
        sphereMesh.meshName = "Sphere_1_unit_Radius.ply";
        sphereMesh.bIsWireframe = true;
        sphereMesh.bDoNotLight = true;

        sphereMesh.friendlyName = "Sphere";

//        sphereMesh.physProps.velocity.y = 0.0f;
        sPhsyicsProperties* pSpherePhysProps = new sPhsyicsProperties();        // HEAP

        pSpherePhysProps->velocity.y = getRandomFloat(0.0f, MAX_VELOCITY);
        pSpherePhysProps->velocity.x = getRandomFloat(-MAX_VELOCITY, MAX_VELOCITY);
        pSpherePhysProps->velocity.z = getRandomFloat(-MAX_VELOCITY, MAX_VELOCITY);

        // Gravity on Earth is likely too fast to look good, so we'll make it smaller.
//        sphereMesh.physProps.acceleration.y = -9.81f;
        pSpherePhysProps->acceleration.y = (-9.81f/5.0f);

        pSpherePhysProps->position.x = getRandomFloat(-MAX_SPHERE_LOCATION, MAX_SPHERE_LOCATION);
        pSpherePhysProps->position.z = getRandomFloat(-MAX_SPHERE_LOCATION, MAX_SPHERE_LOCATION);
        pSpherePhysProps->position.y = getRandomFloat(10.0f, MAX_SPHERE_LOCATION + 20.0f);

        sphereMesh.pPhysProps = pSpherePhysProps;
        // Copy the physics position to the drawing position
        sphereMesh.drawPosition = pSpherePhysProps->position;

        ::g_vecMeshesToDraw.push_back(sphereMesh);


        //cMesh shpereMeshShadow_HACK;
        //shpereMeshShadow_HACK.meshName = "Sphere_1_unit_Radius.ply";
        //shpereMeshShadow_HACK.bIsWireframe = false;
        //shpereMeshShadow_HACK.bDoNotLight = true;
//        shpereMeshShadow_HACK.
//        shpereMeshShadow_HACK.friendlyName = "Sphere";


    }//for ( unsigned int count...

    cMesh debugSphere;
    debugSphere.meshName = "Sphere_1_unit_Radius.ply";
    debugSphere.bIsWireframe = true;
    debugSphere.bDoNotLight = true;
    debugSphere.pPhysProps = NULL;
    debugSphere.friendlyName = "DEBUG_SPEERE";

    g_vecMeshesToDraw.push_back(debugSphere);


//    glm::vec3 cameraEye = glm::vec3(10.0, 5.0, -15.0f);
    float yaxisRotation = 0.0f;

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
//        mat4x4 m, p, mvp;
        glm::mat4 matModel;         // "model" or "world" matrix
        glm::mat4 matProjection;    // "projection"
        glm::mat4 matView;          // "view" or "camera"
        glm::mat4 mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // While drawing a pixel, see if the pixel that's already there is closer or not?
        glEnable(GL_DEPTH_TEST);
        // (Usually) the default - does NOT draw "back facing" triangles
        glCullFace(GL_BACK);


        //uniform vec3 directionalLightColour;
        // rgb are the rgb of the light colour
        //uniform vec4 directionalLight_Direction_power;
        GLint lightColour_UL = glGetUniformLocation(shaderProgramID, "directionalLightColour");
        GLint lightDirectionPower_UL = glGetUniformLocation(shaderProgramID, "directionalLight_Direction_power");

        glUniform3f(lightColour_UL, 1.0f, 1.0f, 1.0f);  // White light
//        glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
        // Down, to the right (+ve X) and along +ve z, too
        glm::vec3 lightDirection = glm::vec3(1.0f, -1.0f, 1.0f);
        lightDirection = glm::normalize(lightDirection);

        float lightBrightness = 1.0f;       
        glUniform4f(lightDirectionPower_UL, lightDirection.x, lightDirection.y, lightDirection.z,
                    lightBrightness);





        // *********************************************************************
        // Draw all the objects
        for ( unsigned int index = 0; index != g_vecMeshesToDraw.size(); index++ )
        {

            cMesh currentMesh = g_vecMeshesToDraw[index];

        //         mat4x4_identity(m);
            matModel = glm::mat4(1.0f);



            // Translation
            glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
                                                    glm::vec3(currentMesh.drawPosition.x,
                                                              currentMesh.drawPosition.y,
                                                              currentMesh.drawPosition.z));


               // Rotation matrix generation
            glm::mat4 matRotateX = glm::rotate(glm::mat4(1.0f),
                                               currentMesh.orientation.x, // (float)glfwGetTime(),
                                               glm::vec3(1.0f, 0.0, 0.0f));


            glm::mat4 matRotateY = glm::rotate(glm::mat4(1.0f),
                                               currentMesh.orientation.y, // (float)glfwGetTime(),
                                               glm::vec3(0.0f, 1.0, 0.0f));

            glm::mat4 matRotateZ = glm::rotate(glm::mat4(1.0f),
                                               currentMesh.orientation.z, // (float)glfwGetTime(),
                                               glm::vec3(0.0f, 0.0, 1.0f));

               // Scaling matrix
            glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
                                            glm::vec3(currentMesh.scale, 
                                                      currentMesh.scale, 
                                                      currentMesh.scale));
            //--------------------------------------------------------------

            // Combine all these transformation
            matModel = matModel * matTranslate;

            matModel = matModel * matRotateX;
            matModel = matModel * matRotateY;
            matModel = matModel * matRotateZ;

            matModel = matModel * matScale;

    //        m = m * rotateZ;
    //        m = m * rotateY;
    //        m = m * rotateZ;

            //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            matProjection = glm::perspective(0.6f,
                                             ratio,
                                             0.1f,
                                             1000.0f);

    //        glm::vec3 cameraEye = glm::vec3(0.0, 0.0, -4.0f);
    //        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    //        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    //        cameraEye.z += 0.001f;

            matView = glm::lookAt(cameraEye,
                                  cameraTarget,
                                  upVector);

           //mat4x4_mul(mvp, p, m);
            mvp = matProjection * matView * matModel;

            glUseProgram(shaderProgramID);

            mvp_location = glGetUniformLocation(shaderProgramID, "MVP");
            //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

            // Also calculate and pass the "inverse transpose" for the model matrix
            glm::mat4 matModel_InverseTranspose = glm::inverse(glm::transpose(matModel));
            // uniform mat4 matModel_IT;
            GLint matModel_IT_UL = glGetUniformLocation(shaderProgramID, "matModel_IT");
            glUniformMatrix4fv(matModel_IT_UL, 1, GL_FALSE, glm::value_ptr(matModel_InverseTranspose));


            //uniform vec3 modelOffset;
//            GLint modelOffset_UL = glGetUniformLocation(shaderProgramID, "modelOffset");

//            glUniform3f(modelOffset_UL, -0.1f, 0.0f, 0.0f);

    //        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT /*GL_LINE*/ /*GL_FILL*/);
            if ( currentMesh.bIsWireframe )
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else 
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

    //        glPointSize(10.0f);


            // uniform bool bDoNotLight;
            GLint bDoNotLight_UL = glGetUniformLocation(shaderProgramID, "bDoNotLight");

            if ( currentMesh.bDoNotLight )
            {
                // Set uniform to true
                glUniform1f(bDoNotLight_UL, (GLfloat)GL_TRUE);
            }
            else
            {
                // Set uniform to false;
                glUniform1f(bDoNotLight_UL, (GLfloat)GL_FALSE);
            }



 //           glDrawArrays(GL_TRIANGLES, 0, g_NumberOfVerticesToDraw);

            sModelDrawInfo modelInfo;
            if ( pMeshManager->FindDrawInfoByModelName(currentMesh.meshName, modelInfo) )
            {
                // Found it!!!

                glBindVertexArray(modelInfo.VAO_ID); 		//  enable VAO (and everything else)
                glDrawElements(GL_TRIANGLES, 
                                modelInfo.numberOfIndices, 
                                GL_UNSIGNED_INT, 
                                0);
                glBindVertexArray(0); 			            // disable VAO (and everything else)

            }


        }//for ( unsigned int index
        // *********************************************************************

        // Time per frame (more or less)
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
//        std::cout << deltaTime << std::endl;
        lastTime = currentTime;

        // 
        DoPhysicUpdate(deltaTime);


        glfwSwapBuffers(window);
        glfwPollEvents();

        // Update the title screen
        std::stringstream ssTitle;
        ssTitle << "Camera (x,y,z): "
            << cameraEye.x << ", "
            << cameraEye.y << ", "
            << cameraEye.z << ")";
//        glfwSetWindowTitle(window, "HEY!");

        std::string theTitle = ssTitle.str();

        glfwSetWindowTitle(window, theTitle.c_str() );


    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


