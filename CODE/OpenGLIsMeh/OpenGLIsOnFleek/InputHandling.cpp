#include "GLWF_CallBacks.h"

#include <string>
#include <iostream>
#include <vector>
#include "cMesh.h"

extern int g_selectedMesh;// = 0;
extern std::vector< cMesh* > g_vec_pMeshesToDraw;
extern glm::vec3 g_cameraEye;

bool SaveVectorSceneToFile(std::string saveFileName);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
    if (mods == GLFW_MOD_SHIFT)
    {
        // Shift key ONLY is down
    }

    // & will "mask" off the mod leaving the shift
    if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
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
        if (key == GLFW_KEY_PAGE_UP)
        {
            ::g_selectedMesh++;
            if (::g_selectedMesh > ::g_vec_pMeshesToDraw.size())
            {
                ::g_selectedMesh = 0;
            }
            std::cout << "Selcted model: " << ::g_selectedMesh << std::endl;
        }
        if (key == GLFW_KEY_PAGE_DOWN)
        {
            ::g_selectedMesh--;
            if (::g_selectedMesh < 0)
            {
                ::g_selectedMesh = ((int)::g_vec_pMeshesToDraw.size() - 1);
            }
            std::cout << "Selcted model: " << ::g_selectedMesh << std::endl;
        }
    }
    else
    {
        // Shift key is NOT down

        if (key == GLFW_KEY_A && action)
        {
            ::g_cameraEye.x -= CAMERA_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_D && action)
        {
            ::g_cameraEye.x += CAMERA_MOVEMENT_SPEED;
        }

        if (key == GLFW_KEY_W && action)
        {
            ::g_cameraEye.z += CAMERA_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_S && action)
        {
            ::g_cameraEye.z -= CAMERA_MOVEMENT_SPEED;
        }


        if (key == GLFW_KEY_Q && action)
        {
            ::g_cameraEye.y -= CAMERA_MOVEMENT_SPEED;
        }
        if (key == GLFW_KEY_E && action)
        {
            ::g_cameraEye.y += CAMERA_MOVEMENT_SPEED;
        }

    }// if ( ( mods & GLFW_MOD_SHIFT ) == GLFW_MOD_SHIFT )



    return;
}

