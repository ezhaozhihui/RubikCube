//
//  glfw_app.cpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/23.
//  Copyright © 2017年 EZ. All rights reserved.
//

#include "glfw_app.hpp"

GLFWApp::GLFWApp(const std::string& title, GLint window_width, GLint window_height)
{
    if (!glfwInit())
        throw std::runtime_error
    {
        "Unable to initialize glfw runtime"
    };

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(window_width, window_height, title.c_str(), nullptr, nullptr);

    if (!m_window)
        throw std::runtime_error
    {
        "Unable to create glfw window"
    };

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();
}

GLFWApp::~GLFWApp()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void GLFWApp::start()
{
    glfwloop();
}

void GLFWApp::glfwloop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        this->glLoop();

        glfwSwapBuffers(m_window);
    }
}

GLFWwindow* GLFWApp::window() const
{
    return m_window;
}

void GLFWApp::onKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{

}

void GLFWApp::onError(int error, const char *desc)
{

}

void GLFWApp::onResize(GLFWwindow *window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}

GLFWApp* GLFWAppManager::_app = 0;
void GLFWAppManager::start_app(GLFWApp* app)
{
    _app = app;

    glfwSetKeyCallback(_app->window(), onKeyboard);
    glfwSetFramebufferSizeCallback(_app->window(), onResize);
    glfwSetErrorCallback(onError);
}
