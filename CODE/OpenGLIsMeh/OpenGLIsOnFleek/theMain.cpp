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

glm::vec3 cameraEye = glm::vec3(0.0, 0.0, +10.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);


// Smart array of cMesh object
std::vector<cMesh> g_vecMeshesToDraw;
// 
int g_selectedMesh = 0;

// Function signature
bool SaveVectorSceneToFile(std::string saveFileName);


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

    const float CAMERA_MOVEMENT_SPEED = 0.1f;
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

        if (key == GLFW_KEY_A )
        {
            ::g_vecMeshesToDraw[::g_selectedMesh].position.x -= OBJECT_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_D )
        {
            ::g_vecMeshesToDraw[::g_selectedMesh].position.x += OBJECT_MOVEMENT_SPEED;
        }

        if (key == GLFW_KEY_W )
        {
            ::g_vecMeshesToDraw[::g_selectedMesh].position.z += OBJECT_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_S )
        {
            ::g_vecMeshesToDraw[::g_selectedMesh].position.z -= OBJECT_MOVEMENT_SPEED;
        }


        if (key == GLFW_KEY_Q )
        {
            ::g_vecMeshesToDraw[::g_selectedMesh].position.y -= OBJECT_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_E )
        {
            ::g_vecMeshesToDraw[::g_selectedMesh].position.y += OBJECT_MOVEMENT_SPEED;
        }

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
                ::g_selectedMesh = (::g_vecMeshesToDraw.size() - 1);
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




// The format for the original bunny with only XYZ
//bool LoadTheFile_PlyXYZ(std::string theFileName)
//{
////    property float x
////    property float y
////    property float z
//
//    //sVertexPlyFile p;       p.x = 0.0f;     p.y = 1.0f; p.z = 2.0f;
//    //std::cout << p.x;
//
//    //sVertexPlyFile q;
//    //std::cout << "Type in the x: ";
//    //std::cin >> q.x;
//
//    // Input Filestream 
//    std::ifstream theBunnyFile("bun_zipper_res2_xyz.ply");
//    if ( ! theBunnyFile.is_open() )
//    {
//        // didn't open the file.
//        return false;
//    }
//
//    std::string temp;
//    while (theBunnyFile >> temp)
//    {
//        if (temp == "vertex")
//        {
//            break;
//        }
//    };
//    //element vertex 8171
//    theBunnyFile >> g_numberOfVertices;
//
//
//    while (theBunnyFile >> temp)
//    {
//        if (temp == "face")
//        {
//            break;
//        }
//    };
//    //element vertex 8171
//    theBunnyFile >> g_numberOfTriangles;
//
//    while (theBunnyFile >> temp)
//    {
//        if (temp == "end_header")
//        {
//            break;
//        }
//    };
//
//
//    // Allocate enough space to hold the vertices
////    sVertex vertices[8171];                 // Stack
//
////    sVertex x;      // STACK based variable (on the stack)
////    sVertex* px;    // Pointer variable.
//
////    int y = 5;
////
////    int* py = new int();
////    *py = 5;
//
//
//    // Dynamically allocate memory on the heap;
//    sVertexPlyFile* pTheVerticesFile = new sVertexPlyFile[g_numberOfVertices];
//
//    // -0.036872 0.127727 0.00440925 
//    for ( unsigned int index = 0; index != g_numberOfVertices; index++ )
//    {
//        sVertexPlyFile tempVertex;
//        theBunnyFile >> tempVertex.x;                //std::cin >> a.x;
//        theBunnyFile >> tempVertex.y;                //std::cin >> a.y;
//        theBunnyFile >> tempVertex.z;                //std::cin >> a.z;
//
//        pTheVerticesFile[index] = tempVertex;
//    }
//
//
//    sTrianglePlyFile* pTheTriangles = new sTrianglePlyFile[g_numberOfTriangles];
//
//    // 3 3495 3549 3548 
//    for ( unsigned int index = 0; index != g_numberOfTriangles; index++ )
//    {
//        sTrianglePlyFile tempTriangle;
//
//        unsigned int discard;
//        theBunnyFile >> discard;            // 3
//        theBunnyFile >> tempTriangle.v0;                //std::cin >> a.x;
//        theBunnyFile >> tempTriangle.v1;                //std::cin >> a.y;
//        theBunnyFile >> tempTriangle.v2;                //std::cin >> a.z;
//
//        pTheTriangles[index] = tempTriangle;
//    }
//
//
//    // Now allocate the array that the shader is going to use
////    g_NumberOfVerticesToDraw = 6;
////    pVertices = new sVertex[g_NumberOfVerticesToDraw];
////
////    pVertices[0] = { -0.6f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f };
////    pVertices[1] = { 0.6f, -0.4f, 0.0f,   0.0f, 1.0f, 0.0f };
////    pVertices[2] = { 0.f,  0.6f, 0.0f,   0.0f, 0.0f, 1.0f };
////    pVertices[3] = { 0.4f, -0.4f, 0.0f,   0.0f, 1.0f, 0.0f };
////    pVertices[4] = { 1.6f, -0.4f, 0.0f,   0.0f, 0.0f, 1.0f };
////    pVertices[5] = { 1.0f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f };
//
////    g_NumberOfVerticesToDraw = g_numberOfVertices;
////    pVertices = new sVertex[g_NumberOfVerticesToDraw];
////
////    // Copy from the array we filled from the file to the array that that 
////    //  shader (video card) will use...
////
////    for (unsigned int index = 0; index != g_numberOfVertices; index++)
////    {
////        // Left is the array going to the video
////        // Right is the array from the file
////        pVertices[index].x = pTheVerticesFile[index].x;
////        pVertices[index].y = pTheVerticesFile[index].y;
////        pVertices[index].z = pTheVerticesFile[index].z;
////
////        pVertices[index].r = 1.0f;
////        pVertices[index].g = 1.0f;
////        pVertices[index].b = 1.0f;
////    }
//// 
//    g_NumberOfVerticesToDraw = g_numberOfTriangles * 3;
//    pVertices = new sVertex[g_NumberOfVerticesToDraw];
//
//    unsigned int vertIndex = 0;
//    for (unsigned int triIndex = 0; triIndex != g_numberOfTriangles; triIndex++)
//    {
//        // 3 1582 1581 2063 
//        pVertices[vertIndex + 0].x =  pTheVerticesFile[ pTheTriangles[triIndex].v0 ].x;
//        pVertices[vertIndex + 0].y =  pTheVerticesFile[ pTheTriangles[triIndex].v0 ].y;
//        pVertices[vertIndex + 0].z =  pTheVerticesFile[ pTheTriangles[triIndex].v0 ].z;
//
//        pVertices[vertIndex + 0].r = 1.0f;
//        pVertices[vertIndex + 0].g = 0.0f;
//        pVertices[vertIndex + 0].b = 0.0f;
//
//        pVertices[vertIndex + 1].x =  pTheVerticesFile[ pTheTriangles[triIndex].v1 ].x;
//        pVertices[vertIndex + 1].y =  pTheVerticesFile[ pTheTriangles[triIndex].v1 ].y;
//        pVertices[vertIndex + 1].z =  pTheVerticesFile[ pTheTriangles[triIndex].v1 ].z;
//
//        pVertices[vertIndex + 1].r = 0.0f;
//        pVertices[vertIndex + 1].g = 1.0f;
//        pVertices[vertIndex + 1].b = 0.0f;
//
//        pVertices[vertIndex + 2].x =  pTheVerticesFile[ pTheTriangles[triIndex].v2 ].x;
//        pVertices[vertIndex + 2].y =  pTheVerticesFile[ pTheTriangles[triIndex].v2 ].y;
//        pVertices[vertIndex + 2].z =  pTheVerticesFile[ pTheTriangles[triIndex].v2 ].z;
//
//        pVertices[vertIndex + 2].r = 0.0f;
//        pVertices[vertIndex + 2].g = 0.0f;
//        pVertices[vertIndex + 2].b = 1.0f;
//
//        vertIndex += 3;
//    }
//
//    // Manipulate the mode
//    for (unsigned int vertIndex = 0; vertIndex != g_NumberOfVerticesToDraw; vertIndex++)
//    {
//        // Translation in space (aka adding)
////        pVertices[vertIndex].x += 0.0f;
////        pVertices[vertIndex].y -= 0.1f;
////        pVertices[vertIndex].z = 0.0f;
//
//        // Scale the model
////        pVertices[vertIndex].x *= 10.0f;
////        pVertices[vertIndex].y *= 10.f;
////        pVertices[vertIndex].z *= 10.0f;
//
//        // Rotate the model around the x axis
////        pVertices[vertIndex].x *= 10.0f;
////        pVertices[vertIndex].y *= 10.f;
////        pVertices[vertIndex].z *= 10.0f;
//
//    }
//
//
//    // 1. Found extents (lowest and highest axis)
//    // 2. Got the delta (difference) of those two
//    // 3. Made an array with high-low range for each stripe
//    // 4. Compare each vertex with this array (step 3), change colour
//
//    // 1. Make an array or RGB stripes (width, etc.)
//    // 2. Divide x by spacing (including remainder) by number of colours
//    //    in array. 
//    // 3. Compare each vertex and colour 
//
//    return true;
//}

// For the bathtub model that has normals and colours
//bool LoadTheFile_Ply_XYZ_N_RGBA(std::string theFileName)
//{
////    property float x
////    property float y
////    property float z
//
//    //sVertexPlyFile p;       p.x = 0.0f;     p.y = 1.0f; p.z = 2.0f;
//    //std::cout << p.x;
//
//    //sVertexPlyFile q;
//    //std::cout << "Type in the x: ";
//    //std::cin >> q.x;
//
//    // Input Filestream 
//    std::ifstream theBunnyFile("bathtub.ply");
//    if (!theBunnyFile.is_open())
//    {
//        // didn't open the file.
//        return false;
//    }
//
//    std::string temp;
//    while (theBunnyFile >> temp)
//    {
//        if (temp == "vertex")
//        {
//            break;
//        }
//    };
//    //element vertex 8171
//    theBunnyFile >> g_numberOfVertices;
//
//
//    while (theBunnyFile >> temp)
//    {
//        if (temp == "face")
//        {
//            break;
//        }
//    };
//    //element vertex 8171
//    theBunnyFile >> g_numberOfTriangles;
//
//    while (theBunnyFile >> temp)
//    {
//        if (temp == "end_header")
//        {
//            break;
//        }
//    };
//
//
//    // Allocate enough space to hold the vertices
////    sVertex vertices[8171];                 // Stack
//
////    sVertex x;      // STACK based variable (on the stack)
////    sVertex* px;    // Pointer variable.
//
////    int y = 5;
////
////    int* py = new int();
////    *py = 5;
//
//
//    // Dynamically allocate memory on the heap;
//    sVertexPlyFile* pTheVerticesFile = new sVertexPlyFile[g_numberOfVertices];
//
//    // -0.036872 0.127727 0.00440925 
//    for (unsigned int index = 0; index != g_numberOfVertices; index++)
//    {
//        sVertexPlyFile tempVertex;
//        theBunnyFile >> tempVertex.x;                //std::cin >> a.x;
//        theBunnyFile >> tempVertex.y;                //std::cin >> a.y;
//        theBunnyFile >> tempVertex.z;                //std::cin >> a.z;
//
//        theBunnyFile >> tempVertex.nx;
//        theBunnyFile >> tempVertex.ny;
//        theBunnyFile >> tempVertex.nz;
//
//        theBunnyFile >> tempVertex.r;       tempVertex.r /= 255.0f;
//        theBunnyFile >> tempVertex.g;       tempVertex.g /= 255.0f;
//        theBunnyFile >> tempVertex.b;       tempVertex.b /= 255.0f;
//        theBunnyFile >> tempVertex.a;       tempVertex.a /= 255.0f;
//
//
//        pTheVerticesFile[index] = tempVertex;
//    }
//
//
//    sTrianglePlyFile* pTheTriangles = new sTrianglePlyFile[g_numberOfTriangles];
//
//    // 3 3495 3549 3548 
//    for (unsigned int index = 0; index != g_numberOfTriangles; index++)
//    {
//        sTrianglePlyFile tempTriangle;
//
//        unsigned int discard;
//        theBunnyFile >> discard;            // 3
//        theBunnyFile >> tempTriangle.v0;                //std::cin >> a.x;
//        theBunnyFile >> tempTriangle.v1;                //std::cin >> a.y;
//        theBunnyFile >> tempTriangle.v2;                //std::cin >> a.z;
//
//        pTheTriangles[index] = tempTriangle;
//    }
//
//
//    // Now allocate the array that the shader is going to use
////    g_NumberOfVerticesToDraw = 6;
////    pVertices = new sVertex[g_NumberOfVerticesToDraw];
////
////    pVertices[0] = { -0.6f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f };
////    pVertices[1] = { 0.6f, -0.4f, 0.0f,   0.0f, 1.0f, 0.0f };
////    pVertices[2] = { 0.f,  0.6f, 0.0f,   0.0f, 0.0f, 1.0f };
////    pVertices[3] = { 0.4f, -0.4f, 0.0f,   0.0f, 1.0f, 0.0f };
////    pVertices[4] = { 1.6f, -0.4f, 0.0f,   0.0f, 0.0f, 1.0f };
////    pVertices[5] = { 1.0f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f };
//
////    g_NumberOfVerticesToDraw = g_numberOfVertices;
////    pVertices = new sVertex[g_NumberOfVerticesToDraw];
////
////    // Copy from the array we filled from the file to the array that that 
////    //  shader (video card) will use...
////
////    for (unsigned int index = 0; index != g_numberOfVertices; index++)
////    {
////        // Left is the array going to the video
////        // Right is the array from the file
////        pVertices[index].x = pTheVerticesFile[index].x;
////        pVertices[index].y = pTheVerticesFile[index].y;
////        pVertices[index].z = pTheVerticesFile[index].z;
////
////        pVertices[index].r = 1.0f;
////        pVertices[index].g = 1.0f;
////        pVertices[index].b = 1.0f;
////    }
//// 
//    g_NumberOfVerticesToDraw = g_numberOfTriangles * 3;
//    pVertices = new sVertex[g_NumberOfVerticesToDraw];
//
//    unsigned int vertIndex = 0;
//    for (unsigned int triIndex = 0; triIndex != g_numberOfTriangles; triIndex++)
//    {
//        // 3 1582 1581 2063 
//        pVertices[vertIndex + 0].x = pTheVerticesFile[pTheTriangles[triIndex].v0].x;
//        pVertices[vertIndex + 0].y = pTheVerticesFile[pTheTriangles[triIndex].v0].y;
//        pVertices[vertIndex + 0].z = pTheVerticesFile[pTheTriangles[triIndex].v0].z;
//
//        pVertices[vertIndex + 0].r = pTheVerticesFile[pTheTriangles[triIndex].v0].r;
//        pVertices[vertIndex + 0].g = pTheVerticesFile[pTheTriangles[triIndex].v0].g;
//        pVertices[vertIndex + 0].b = pTheVerticesFile[pTheTriangles[triIndex].v0].b;
//
//        pVertices[vertIndex + 1].x = pTheVerticesFile[pTheTriangles[triIndex].v1].x;
//        pVertices[vertIndex + 1].y = pTheVerticesFile[pTheTriangles[triIndex].v1].y;
//        pVertices[vertIndex + 1].z = pTheVerticesFile[pTheTriangles[triIndex].v1].z;
//
//        pVertices[vertIndex + 1].r = pTheVerticesFile[pTheTriangles[triIndex].v1].r;
//        pVertices[vertIndex + 1].g = pTheVerticesFile[pTheTriangles[triIndex].v1].g;
//        pVertices[vertIndex + 1].b = pTheVerticesFile[pTheTriangles[triIndex].v1].b;
//
//        pVertices[vertIndex + 2].x = pTheVerticesFile[pTheTriangles[triIndex].v2].x;
//        pVertices[vertIndex + 2].y = pTheVerticesFile[pTheTriangles[triIndex].v2].y;
//        pVertices[vertIndex + 2].z = pTheVerticesFile[pTheTriangles[triIndex].v2].z;
//
//        pVertices[vertIndex + 2].r = pTheVerticesFile[pTheTriangles[triIndex].v2].r;
//        pVertices[vertIndex + 2].g = pTheVerticesFile[pTheTriangles[triIndex].v2].g;
//        pVertices[vertIndex + 2].b = pTheVerticesFile[pTheTriangles[triIndex].v2].b;
//
//        vertIndex += 3;
//    }
//
//    return true;
//}


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

    cVAOManager* pMeshManager = new cVAOManager();

    sModelDrawInfo bunnyDrawingInfo;
    pMeshManager->LoadModelIntoVAO("bun_zipper_res2_xyz_n_rgba.ply",
                                   bunnyDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << bunnyDrawingInfo.numberOfVertices << " vertices" << std::endl;

    sModelDrawInfo bathtubDrawingInfo;
    pMeshManager->LoadModelIntoVAO("bathtub_xyz_n_rgba.ply",
                                   bathtubDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << bathtubDrawingInfo.numberOfVertices << " vertices" << std::endl;

    sModelDrawInfo terrainDrawingInfo;
    pMeshManager->LoadModelIntoVAO("Terrain_xyz_n_rgba.ply",
                                   terrainDrawingInfo, shaderProgramID);
    std::cout << "Loaded: " << terrainDrawingInfo.numberOfVertices << " vertices" << std::endl;

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



//    GLint vpos_location = glGetAttribLocation(shaderProgramID, "vPos");
//    GLint vcol_location = glGetAttribLocation(shaderProgramID, "vCol");
//
////    int sizeofsVertex = sizeof(sVertex);
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location,
//                          3,                        // 2 floats 
//                          GL_FLOAT, 
//                          GL_FALSE,         
//                          sizeof(sVertex),                   //  sizeof(vertices[0]),
//                          (void*) offsetof(sVertex, x) );    //  (void*)0);
//
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 
//                          3, 
//                          GL_FLOAT, 
//                          GL_FALSE,
//                          sizeof(sVertex),                  //  sizeof(vertices[0]),
//                          (void*) offsetof(sVertex, r));    //  (void*)(sizeof(float) * 2));


    // bun_zipper_res2_xyz_n_rgba.ply
    // bathtub_xyz_n_rgba.ply

    // Add some models to the "scene"
    cMesh bunny1;   
    bunny1.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
    bunny1.position = glm::vec3(-1.0f, 0.0f, 0.0f);
    bunny1.scale = 10.0f;
    bunny1.orientation.x = glm::radians(45.0f);

    cMesh bunny2;
    bunny2.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
    bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
    bunny2.scale = 7.5f;
    bunny2.orientation.y = glm::radians(135.0f);

    cMesh bathtub;
    bathtub.meshName = "bathtub_xyz_n_rgba.ply";
    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
    bathtub.scale = 0.25f;

    cMesh terrain;
    terrain.meshName = "Terrain_xyz_n_rgba.ply";
    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
    terrain.scale = 1.0f;
    terrain.position.y = -25.0f;

//    // Smart array of cMesh object
//    std::vector<cMesh> vecMeshesToDraw;
    g_vecMeshesToDraw.push_back(bunny1);
    g_vecMeshesToDraw.push_back(bunny2);
    g_vecMeshesToDraw.push_back(bathtub);
    g_vecMeshesToDraw.push_back(terrain);



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


            double currentTime = glfwGetTime();
            double deltaTime = currentTime - lastTime;
    //        std::cout << deltaTime << std::endl;
            lastTime = currentTime;


            // Translation
            glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f),
                                                    glm::vec3(currentMesh.position.x,
                                                              currentMesh.position.y,
                                                              currentMesh.position.z));


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
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL /*GL_LINE*/ /*GL_POINT*/);
    //        glPointSize(10.0f);

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


