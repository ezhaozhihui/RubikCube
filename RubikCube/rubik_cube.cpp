//
//  rubik_cube.cpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/23.
//  Copyright © 2017年 EZ. All rights reserved.
//

#include "rubik_cube.hpp"

void RubikCube::onKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (mods == GLFW_MOD_SHIFT)
    {
        if (key == GLFW_KEY_U && action == GLFW_PRESS)
        {
            cube->keys[ROT_U] = GL_TRUE;
        }
        else if (key == GLFW_KEY_D && action == GLFW_PRESS)
        {
            cube->keys[ROT_D] = GL_TRUE;
        }
        else if (key == GLFW_KEY_L && action == GLFW_PRESS)
        {
            cube->keys[ROT_L] = GL_TRUE;
        }
        else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        {
            cube->keys[ROT_R] = GL_TRUE;
        }
        else if (key == GLFW_KEY_F && action == GLFW_PRESS)
        {
            cube->keys[ROT_F] = GL_TRUE;
        }
        else if (key == GLFW_KEY_B && action == GLFW_PRESS)
        {
            cube->keys[ROT_B] = GL_TRUE;
        }

    }
    else
    {
        if (key == GLFW_KEY_U && action == GLFW_PRESS)
        {
            cube->keys[ROT_U_NI] = GL_TRUE;
        }
        else if (key == GLFW_KEY_D && action == GLFW_PRESS)
        {
            cube->keys[ROT_D_NI] = GL_TRUE;
        }
        else if (key == GLFW_KEY_L && action == GLFW_PRESS)
        {
            cube->keys[ROT_L_NI] = GL_TRUE;
        }
        else if (key == GLFW_KEY_R && action == GLFW_PRESS)
        {
            cube->keys[ROT_R_NI] = GL_TRUE;
        }
        else if (key == GLFW_KEY_F && action == GLFW_PRESS)
        {
            cube->keys[ROT_F_NI] = GL_TRUE;
        }
        else if (key == GLFW_KEY_B && action == GLFW_PRESS)
        {
            cube->keys[ROT_B_NI] = GL_TRUE;
        }
    }

}

void RubikCube::glLoop()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cube->processInput(0.0f);
    cube->render(camera->getProjView());
}
