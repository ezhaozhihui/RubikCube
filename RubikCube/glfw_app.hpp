//
//  glfw_app.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/23.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef glfw_app_hpp
#define glfw_app_hpp

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <string>

class GLFWApp
{
public:
    GLFWApp(const std::string& titile, GLint window_width, GLint window_height);
    virtual ~GLFWApp();

    void start();
    void glfwloop();

    virtual void onKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
    virtual void onError(int error, const char* desc);
    virtual void onResize(GLFWwindow* window, GLint width, GLint height);
    virtual void glLoop() = 0;

    GLFWwindow* window() const;
private:
    GLFWwindow* m_window;
};

class GLFWAppManager
{
public:
    static GLFWApp* _app;

    static void onKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (_app) _app->onKeyboard(window, key, scancode, action, mods);
    }

    static void onError(int error, const char* desc)
    {
        if (_app) _app->onError(error, desc);
    }

    static void onResize(GLFWwindow* window, GLint width, GLint height)
    {
        if (_app) _app->onResize(window, width, height);
    }

public:
    static void start_app(GLFWApp* app);
};



template<typename T , typename... ARGS , typename = typename std::enable_if<std::is_base_of<GLFWApp,T>::value>::type>
std::unique_ptr<T> make_app(ARGS&&... args)
{
    std::unique_ptr<T> app{ new T{ std::forward<ARGS>(args)...} };

    GLFWAppManager::start_app(app.get());

    return app;
}
#endif /* glfw_app_hpp */
