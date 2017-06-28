//
//  cube.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/18.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef cube_hpp
#define cube_hpp

#include "mesh.hpp"
#include <vector>
#include <GLFW/glfw3.h>

enum FaceRotationType {
    ROT_R = 0,
    ROT_R_NI,
    ROT_L,
    ROT_L_NI,
    ROT_U,
    ROT_U_NI,
    ROT_D,
    ROT_D_NI,
    ROT_F,
    ROT_F_NI,
    ROT_B,
    ROT_B_NI,
    ROT_MAX,
};

typedef struct _Act
{
    GLint       layer;
    GLboolean   clockwise;
} Act;

typedef struct _Coordinate2D
{
    int abscissa;
    int ordinate;
} Coordinate2D;

static const int rot_coef[][2] =
{
    [GL_FALSE] = {1, -1},
    [GL_TRUE]  = {-1, 1},
};

static const Act act_map[ROT_MAX] =
{
    [ROT_R]     = {2, GL_TRUE},
    [ROT_R_NI]  = {2, GL_FALSE},
    [ROT_L]     = {0, GL_FALSE},
    [ROT_L_NI]  = {0, GL_TRUE},
    [ROT_U]     = {5, GL_TRUE},
    [ROT_U_NI]  = {5, GL_FALSE},
    [ROT_D]     = {3, GL_FALSE},
    [ROT_D_NI]  = {3, GL_TRUE},
    [ROT_F]     = {8, GL_TRUE},
    [ROT_F_NI]  = {8, GL_FALSE},
    [ROT_B]     = {6, GL_FALSE},
    [ROT_B_NI]  = {6, GL_TRUE},
};

class Cube
{
public:
    Cube(Mesh* renderer, int order);
    Cube(){}

    void processInput(GLfloat deltaTime);

    void render(const glm::mat4& proj_view) const;

    void showCubeletInfo(int x, int y, int z) const;

    inline int Coor3D(int x, int y, int z) const
    {
        return x * m_order * m_order + y * m_order + z;
    }

    ~Cube();

    GLboolean keys[ROT_MAX];

private:
    void rotByLayer(GLint layer, GLboolean clock_wise, GLfloat step_len);
    void clearKeys();
    void updateCubeletIndex(GLint layer, GLboolean clock_wise);
    Coordinate2D getRotCoor(Coordinate2D p, GLboolean clock_wise);


    std::vector<glm::vec3> cubelet;
    std::vector<glm::mat4> m_rot_mat;

    Mesh* m_renderer;
    int   m_order;

    int counter;
};

#endif /* cube_hpp */
