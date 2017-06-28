//
//  cube.cpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/18.
//  Copyright © 2017年 EZ. All rights reserved.
//

#include "cube.hpp"
#include <iostream>
#include <stdio.h>

static const GLfloat GL_PI = glm::pi<GLfloat>();

Cube::Cube(Mesh* renderer, int order)
  : m_renderer(renderer), m_order(order)
{
    cubelet.resize(0);
    m_rot_mat.resize(0);

    float offset = -m_order / 2 + 0.5f * (~m_order & 0x1);

    for (int x = 0; x < m_order; x++)
    {
        for (int y = 0; y < m_order; y++)
        {
            for (int z = 0; z < m_order; z++)
            {
                m_rot_mat.push_back(glm::mat4(1.0));
                cubelet.push_back(glm::vec3(x + offset, y + offset, z + offset));
            }
        }
    }

    clearKeys();
}

void Cube::render(const glm::mat4& proj_view) const
{
    for (int x = 0; x < m_order; x++)
        for (int y = 0; y < m_order; y++)
            for (int z = 0; z < m_order; z++)
                m_renderer->draw(cubelet[Coor3D(x, y, z)], m_rot_mat[Coor3D(x, y, z)], proj_view);

}

void Cube::clearKeys()
{
    for (int i = 0; i < ROT_MAX; i++)
    {
        keys[i] = GL_FALSE;
    }
    counter = 0;
}

void Cube::processInput(GLfloat deltaTime)
{
    GLfloat rate = GL_PI / 2 / 30;
    if (keys[ROT_U])
    {
        rotByLayer(act_map[ROT_U].layer, act_map[ROT_U].clockwise, rate);
    }
    else if (keys[ROT_U_NI])
    {
        rotByLayer(act_map[ROT_U_NI].layer, act_map[ROT_U_NI].clockwise, rate);
    }
    else if (keys[ROT_D])
    {
        rotByLayer(act_map[ROT_D].layer, act_map[ROT_D].clockwise, rate);
    }
    else if (keys[ROT_D_NI])
    {
        rotByLayer(act_map[ROT_D_NI].layer, act_map[ROT_D_NI].clockwise, rate);
    }
    else if (keys[ROT_L])
    {
        rotByLayer(act_map[ROT_L].layer, act_map[ROT_L].clockwise, rate);
    }
    else if (keys[ROT_L_NI])
    {
        rotByLayer(act_map[ROT_L_NI].layer, act_map[ROT_L_NI].clockwise, rate);
    }
    else if (keys[ROT_R])
    {
        rotByLayer(act_map[ROT_R].layer, act_map[ROT_R].clockwise, rate);
    }
    else if (keys[ROT_R_NI])
    {
        rotByLayer(act_map[ROT_R_NI].layer, act_map[ROT_R_NI].clockwise, rate);
    }
    else if (keys[ROT_F])
    {
        rotByLayer(act_map[ROT_F].layer, act_map[ROT_F].clockwise, rate);
    }
    else if (keys[ROT_F_NI])
    {
        rotByLayer(act_map[ROT_F_NI].layer, act_map[ROT_F_NI].clockwise, rate);
    }
    else if(keys[ROT_B])
    {
        rotByLayer(act_map[ROT_B].layer, act_map[ROT_B].clockwise, rate);
    }
    else if (keys[ROT_B_NI])
    {
        rotByLayer(act_map[ROT_B_NI].layer, act_map[ROT_B_NI].clockwise, rate);
    }
    else
    {
        ;
    }

}

void Cube::rotByLayer(GLint layer, GLboolean clock_wise, GLfloat step_len)
{
    int x, y, z;
    glm::mat4 delta_mat;
    glm::mat4 identity(1.0);

    GLfloat step = clock_wise ? -step_len : step_len;

    if (layer >= 0 && layer < m_order)
    {
        for (y = 0; y < m_order; y++)
            for (z = 0; z < m_order; z++)
            {
                delta_mat = glm::rotate(identity, step, glm::vec3(1.0, 0.0, 0.0));
                m_rot_mat[Coor3D(layer, y, z)] = delta_mat * m_rot_mat[Coor3D(layer, y, z)];
            }
    }
    else if (layer >= m_order && layer < 2 * m_order)
    {
        for (x = 0; x < m_order; x++)
            for (z = 0; z < m_order; z++)
            {
                delta_mat = glm::rotate(identity, step, glm::vec3(0.0, 1.0, 0.0));
                m_rot_mat[Coor3D(x, layer - m_order, z)] = delta_mat * m_rot_mat[Coor3D(x, layer - m_order, z)]; 
            }
    }
    else if (layer >= 2 * m_order && layer < 3 * m_order)
    {
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                delta_mat = glm::rotate(identity, step, glm::vec3(0.0, 0.0, 1.0));
                m_rot_mat[Coor3D(x, y, layer - 2*m_order)] = delta_mat * m_rot_mat[Coor3D(x, y, layer - 2*m_order)];
            }
    }
    else
    {
        std::cerr << "Error: Face Rotation Not Supported" << std::endl;
    }

    counter++;
    if (counter + 1 > GL_PI / 2 / step_len)
    {
        clearKeys();
        updateCubeletIndex(layer, clock_wise);
        //showCubeletInfo(0, 2, 2);
        //showCubeletInfo(1, 2, 2);
        //showCubeletInfo(2, 2, 2);
    }
}

Cube::~Cube()
{

}

void Cube::updateCubeletIndex(GLint layer, GLboolean clock_wise)
{
    std::vector<glm::vec3> tmp;
    std::vector<glm::mat4> tmp1;
    tmp.resize(0);
    tmp1.resize(0);
    Coordinate2D src, dst;
    int x, y, index = 0;
    if (layer >= 0 && layer < m_order)
    {
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                src.abscissa = x; src.ordinate = y;
                dst = getRotCoor(src, clock_wise);
                tmp.push_back(cubelet[Coor3D(layer, dst.abscissa, dst.ordinate)]);
                tmp1.push_back(m_rot_mat[Coor3D(layer, dst.abscissa, dst.ordinate)]);
            }
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                m_rot_mat[Coor3D(layer, x, y)] = tmp1[index];
                cubelet[Coor3D(layer, x, y)] = tmp[index++];
            }

        index = 0;
    }
    else if (layer >= m_order && layer < 2 * m_order)
    {
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                src.abscissa = x; src.ordinate = y;
                dst = getRotCoor(src, clock_wise);
                tmp.push_back(cubelet[Coor3D(dst.ordinate, layer - m_order, dst.abscissa)]);
                tmp1.push_back(m_rot_mat[Coor3D(dst.ordinate, layer - m_order, dst.abscissa)]);
            }
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                m_rot_mat[Coor3D(y, layer - m_order, x)] = tmp1[index];
                cubelet[Coor3D(y, layer - m_order, x)] = tmp[index++];
            }

        index = 0;
    }
    else if (layer >= 2 * m_order && layer < 3 * m_order)
    {
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                src.abscissa = x; src.ordinate = y;
                dst = getRotCoor(src, clock_wise);
                tmp.push_back(cubelet[Coor3D(dst.abscissa, dst.ordinate, layer - 2 * m_order)]);
                tmp1.push_back(m_rot_mat[Coor3D(dst.abscissa, dst.ordinate, layer - 2 * m_order)]);
            }
        for (x = 0; x < m_order; x++)
            for (y = 0; y < m_order; y++)
            {
                m_rot_mat[Coor3D(x, y, layer - 2 * m_order)] = tmp1[index];
                cubelet[Coor3D(x, y, layer - 2 * m_order)] = tmp[index++];
            }

        index = 0;
    }
}

Coordinate2D Cube::getRotCoor(Coordinate2D p, GLboolean clock_wise)
{
    Coordinate2D res;

    float offset = (float)(m_order - 1) / 2;

    res.abscissa = rot_coef[clock_wise][0] * (p.ordinate - offset) + offset;
    res.ordinate = rot_coef[clock_wise][1] * (p.abscissa - offset) + offset;

    return res;
}

void Cube::showCubeletInfo(int x, int y, int z) const
{
    glm::vec3 pos = cubelet[Coor3D(x, y, z)];
    //glm::mat4 rot = m_rot_mat[Coor3D(x, y, z)];

    printf("index[%d, %d, %d] map [%f %f %f]\n", x, y, z, pos.x, pos.y, pos.z);
    //std::cout << "position = " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
#if 0
    std::cout << rot[0][0] << ", " << rot[0][1] << ", " << rot[0][2] << std::endl
    << rot[1][0] << ", " << rot[1][1] << ", " << rot[1][2] << std::endl
    << rot[2][0] << ", " << rot[2][1] << ", " << rot[2][2] << std::endl;
#endif
}
