//
//  rubik_cube.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/23.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef rubik_cube_hpp
#define rubik_cube_hpp

#include "glfw_app.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "cube.hpp"

class RubikCube : public GLFWApp
{
public:
    template <typename... ARGS>
    RubikCube(ARGS&&... args)
    : GLFWApp{ std::forward<ARGS>(args)... }
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        shader = new Shader("../../../RubikCube/cube");
        renderer = new Mesh(*shader);
        cube = new Cube(renderer, 3);

        camera = new Camera(glm::vec3(5.0, 4.0, 7.0), 70.0, (float)800/(float)600, 0.1, 100.0);
    }

    virtual void onKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    virtual void glLoop() override;

private:

    Shader* shader;
    Mesh* renderer;
    Cube* cube;

    Camera* camera;
};

#endif /* rubik_cube_hpp */
