//https://www.glfw.org/docs/latest/quick.html
//http://graphics.stanford.edu/data/3Dscanrep/

#include "OpenGLCommon.h"
//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include "cGlobal.h"

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

// HACK: These will be moved out of global soon.
// They are only here to allow the temporary debug thing to work;
glm::mat4 matProjection;    // "projection"
glm::mat4 matView;          // "view" or "camera"
GLuint shaderProgramID = 0;


cVAOManager* g_pMeshManager = NULL;


// Smart array of cMesh object
//std::vector<cMesh> g_vecMeshesToDraw;
//    ____       _       _                  _          __  __           _               
//   |  _ \ ___ (_)_ __ | |_ ___ _ __ ___  | |_ ___   |  \/  | ___  ___| |__   ___  ___ 
//   | |_) / _ \| | '_ \| __/ _ \ '__/ __| | __/ _ \  | |\/| |/ _ \/ __| '_ \ / _ \/ __|
//   |  __/ (_) | | | | | ||  __/ |  \__ \ | || (_) | | |  | |  __/\__ \ | | |  __/\__ \
//   |_|   \___/|_|_| |_|\__\___|_|  |___/  \__\___/  |_|  |_|\___||___/_| |_|\___||___/
//                                                                                      
std::vector< cMesh* > g_vec_pMeshesToDraw;

//std::vector<sPhsyicsProperties*> g_vecThingsThePhysicsThingPaysAtte;
// 
int g_selectedMesh = 0;

// Function signature
bool SaveVectorSceneToFile(std::string saveFileName);

bool LoadModels(void);

void DoPhysicUpdate(double deltaTime);

void DrawObject(cMesh* pCurrentMesh, glm::mat4 matModel,
                glm::mat4 matProjection, glm::mat4 matView,
                GLuint shaderProgramID);


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
            if ( ::g_selectedMesh > ::g_vec_pMeshesToDraw.size() )
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
                ::g_selectedMesh = ((int)::g_vec_pMeshesToDraw.size() - 1);
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
//    GLint mvp_location;// , vpos_location, vcol_location;

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

    // Creat the debug rendere
    ::g_pDebugRenderer = new cDebugRenderer();

    if ( ::g_pDebugRenderer->Initialize() )
    {
        std::cout << "Debug renderer initialized OK" << std::endl;
    }
    else
    {
        std::cout << "ERROR: Debug renderer because: " << ::g_pDebugRenderer->getLastError() << std::endl;
    } 

//    cShaderManager ShaderThing;
    cShaderManager* pShaderThing = new cShaderManager();
    pShaderThing->setBasePath("assets/shaders");

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
    /*GLuint*/ shaderProgramID = pShaderThing->getIDFromFriendlyName("shader01");

    ::g_pMeshManager = new cVAOManager();

    ::g_pMeshManager->setBasePath("assets/models");

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
    ::g_pMeshManager->LoadModelIntoVAO("Flat_Grid_100x100.ply",
                                   gridDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << gridDrawingInfo.numberOfVertices << " vertices" << std::endl;

    sModelDrawInfo sphereDrawingInfo;
    ::g_pMeshManager->LoadModelIntoVAO("Sphere_1_unit_Radius.ply",
                                   sphereDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << sphereDrawingInfo.numberOfVertices << " vertices" << std::endl;


    // 
//    LoadModels();


//    glm::vec3 cameraEye = glm::vec3(10.0, 5.0, -15.0f);
    float yaxisRotation = 0.0f;

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {

        // Switch the "main" shader
//        shaderProgramID = pShaderThing->getIDFromFriendlyName("shader01");
//        glUseProgram(shaderProgramID);

        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // While drawing a pixel, see if the pixel that's already there is closer or not?
        glEnable(GL_DEPTH_TEST);
        // (Usually) the default - does NOT draw "back facing" triangles
        glCullFace(GL_BACK);

goto BYPASS;
{
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

        // *********************************************************************
        // Draw all the objects
        for ( unsigned int index = 0; index != ::g_vec_pMeshesToDraw.size(); index++ )
        {
            cMesh* pCurrentMesh = ::g_vec_pMeshesToDraw[index];

            if (pCurrentMesh->bIsVisible)
            {

                glm::mat4 matModel = glm::mat4(1.0f);   // Identity matrix

                DrawObject(pCurrentMesh, matModel, matProjection, matView, shaderProgramID);
            }//if (pCurrentMesh->bIsVisible)

        }//for ( unsigned int index
        // *********************************************************************

}
BYPASS:
 
        // Time per frame (more or less)
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
//        std::cout << deltaTime << std::endl;
        lastTime = currentTime;

        const float MAX_LINE_POSITION = 1000.0f;

        glm::vec3 lineStart = glm::vec3(getRandomFloat(-MAX_LINE_POSITION, MAX_LINE_POSITION),
                                    getRandomFloat(-MAX_LINE_POSITION, MAX_LINE_POSITION),
                                    getRandomFloat(-MAX_LINE_POSITION, MAX_LINE_POSITION));

        glm::vec3 lineEnd = glm::vec3(getRandomFloat(-MAX_LINE_POSITION, MAX_LINE_POSITION),
                                    getRandomFloat(-MAX_LINE_POSITION, MAX_LINE_POSITION),
                                    getRandomFloat(-MAX_LINE_POSITION, MAX_LINE_POSITION));

        glm::vec4 lineColour = glm::vec4(getRandomFloat(0.0f, 1.0f),
                                     getRandomFloat(0.0f, 1.0f),
                                     getRandomFloat(0.0f, 1.0f),
                                     1.0f);

        ::g_pDebugRenderer->AddLine(lineStart, lineEnd, lineColour);

        ::g_pDebugRenderer->RenderDebugObjects(deltaTime, matView, matProjection);


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

    // Delete everything


    glfwDestroyWindow(window);




    glfwTerminate();
    exit(EXIT_SUCCESS);
}




void DrawObject(cMesh* pCurrentMesh, glm::mat4 matModelParent, 
                glm::mat4 matProjection, glm::mat4 matView,
                GLuint shaderProgramID)
{

    //         mat4x4_identity(m);
    glm::mat4 matModel = matModelParent;



    // Translation
    glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
                                            glm::vec3(pCurrentMesh->drawPosition.x,
                                                      pCurrentMesh->drawPosition.y,
                                                      pCurrentMesh->drawPosition.z));


       // Rotation matrix generation
    glm::mat4 matRotateX = glm::rotate(glm::mat4(1.0f),
                                       pCurrentMesh->orientation.x, // (float)glfwGetTime(),
                                       glm::vec3(1.0f, 0.0, 0.0f));


    glm::mat4 matRotateY = glm::rotate(glm::mat4(1.0f),
                                       pCurrentMesh->orientation.y, // (float)glfwGetTime(),
                                       glm::vec3(0.0f, 1.0, 0.0f));

    glm::mat4 matRotateZ = glm::rotate(glm::mat4(1.0f),
                                       pCurrentMesh->orientation.z, // (float)glfwGetTime(),
                                       glm::vec3(0.0f, 0.0, 1.0f));

       // Scaling matrix
    glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
                                    glm::vec3(pCurrentMesh->scale,
                                              pCurrentMesh->scale,
                                              pCurrentMesh->scale));
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



   //mat4x4_mul(mvp, p, m);
    glm::mat4 mvp = matProjection * matView * matModel;

    glUseProgram(shaderProgramID);

    GLint mvp_location = glGetUniformLocation(shaderProgramID, "MVP");
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
    if (pCurrentMesh->bIsWireframe)
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

    if (pCurrentMesh->bDoNotLight)
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
    if (::g_pMeshManager->FindDrawInfoByModelName(pCurrentMesh->meshName, modelInfo))
    {
        // Found it!!!

        glBindVertexArray(modelInfo.VAO_ID); 		//  enable VAO (and everything else)
        glDrawElements(GL_TRIANGLES,
                       modelInfo.numberOfIndices,
                       GL_UNSIGNED_INT,
                       0);
        glBindVertexArray(0); 			            // disable VAO (and everything else)

    }

    return;
}
