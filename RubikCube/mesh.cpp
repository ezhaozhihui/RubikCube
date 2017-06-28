//
//  mesh.cpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/10.
//  Copyright © 2017年 EZ. All rights reserved.
//

#include "mesh.hpp"
#include "defs.hpp"
#include <iostream>

void Mesh::draw(const glm::vec3& position, const glm::mat4& rot_mat, const glm::mat4& proj_view)
{

    this->shader.use();

    glm::mat4 trans_mat;
    trans_mat = glm::translate(trans_mat, glm::vec3(position));
    this->shader.setMatrix4("model", rot_mat * trans_mat);
    this->shader.setMatrix4("projection_view", proj_view);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_model.positions.size()));
    glBindVertexArray(0);
}

Mesh::Mesh(Shader& shader)
{
    this->shader = shader;

    const float delta = 0.1f;
    const glm::vec3 offset = glm::vec3(0.5f, 0.5f, 0.5f);

    glm::vec3 vertices[] =
    {
        glm::vec3(0.0f, 0.0f, 0.0f) - offset, // 0
        glm::vec3(1.0f, 0.0f, 0.0f) - offset, // 1
        glm::vec3(1.0f, 1.0f, 0.0f) - offset, // 2
        glm::vec3(0.0f, 1.0f, 0.0f) - offset, // 3
        glm::vec3(0.0f, 0.0f, 1.0f) - offset, // 4
        glm::vec3(1.0f, 0.0f, 1.0f) - offset, // 5
        glm::vec3(1.0f, 1.0f, 1.0f) - offset, // 6
        glm::vec3(0.0f, 1.0f, 1.0f) - offset, // 7

        // back
        glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3( delta,  delta, 0.0) - offset,
        glm::vec3(1.0f, 0.0f, 0.0f) + glm::vec3(-delta,  delta, 0.0) - offset,
        glm::vec3(1.0f, 1.0f, 0.0f) + glm::vec3(-delta, -delta, 0.0) - offset,
        glm::vec3(0.0f, 1.0f, 0.0f) + glm::vec3( delta, -delta, 0.0) - offset,

        // front
        glm::vec3(0.0f, 0.0f, 1.0f) + glm::vec3( delta,  delta, 0.0) - offset, // 4 12
        glm::vec3(1.0f, 0.0f, 1.0f) + glm::vec3(-delta,  delta, 0.0) - offset, // 5 13
        glm::vec3(1.0f, 1.0f, 1.0f) + glm::vec3(-delta, -delta, 0.0) - offset, // 6 14
        glm::vec3(0.0f, 1.0f, 1.0f) + glm::vec3( delta, -delta, 0.0) - offset, // 7 15

        // top
        glm::vec3(1.0f, 1.0f, 0.0f) + glm::vec3(-delta, 0.0,  delta) - offset, // 2 16
        glm::vec3(0.0f, 1.0f, 0.0f) + glm::vec3( delta, 0.0,  delta) - offset, // 3 17
        glm::vec3(0.0f, 1.0f, 1.0f) + glm::vec3( delta, 0.0, -delta) - offset, // 7 18
        glm::vec3(1.0f, 1.0f, 1.0f) + glm::vec3(-delta, 0.0, -delta) - offset, // 6 19

        // bottom
        glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3( delta, 0.0,  delta) - offset, // 0 20
        glm::vec3(1.0f, 0.0f, 0.0f) + glm::vec3(-delta, 0.0,  delta) - offset, // 1 21
        glm::vec3(1.0f, 0.0f, 1.0f) + glm::vec3(-delta, 0.0, -delta) - offset, // 5 22
        glm::vec3(0.0f, 0.0f, 1.0f) + glm::vec3( delta, 0.0, -delta) - offset, // 4 23

        // left
        glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0,  delta,  delta) - offset, // 0 24
        glm::vec3(0.0f, 1.0f, 0.0f) + glm::vec3(0.0, -delta,  delta) - offset, // 3 25
        glm::vec3(0.0f, 1.0f, 1.0f) + glm::vec3(0.0, -delta, -delta) - offset, // 7 26
        glm::vec3(0.0f, 0.0f, 1.0f) + glm::vec3(0.0,  delta, -delta) - offset, // 4 27
        
        // right
        glm::vec3(1.0f, 0.0f, 0.0f) + glm::vec3(0.0,  delta,  delta) - offset, // 1 28
        glm::vec3(1.0f, 1.0f, 0.0f) + glm::vec3(0.0, -delta,  delta) - offset, // 2 29
        glm::vec3(1.0f, 1.0f, 1.0f) + glm::vec3(0.0, -delta, -delta) - offset, // 6 30
        glm::vec3(1.0f, 0.0f, 1.0f) + glm::vec3(0.0,  delta, -delta) - offset, // 5 31
    };

    Vertex unit_cube[] =
    {
        // back
        Vertex(vertices[0], color[BLACK]),
        Vertex(vertices[8], color[BLACK]),
        Vertex(vertices[1], color[BLACK]),

        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[8], color[BLACK]),
        Vertex(vertices[9], color[BLACK]),

        Vertex(vertices[9], color[BLACK]),
        Vertex(vertices[10], color[BLACK]),
        Vertex(vertices[1], color[BLACK]),

        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[10], color[BLACK]),
        Vertex(vertices[2], color[BLACK]),

        Vertex(vertices[10], color[BLACK]),
        Vertex(vertices[11], color[BLACK]),
        Vertex(vertices[3], color[BLACK]),

        Vertex(vertices[10], color[BLACK]),
        Vertex(vertices[3], color[BLACK]),
        Vertex(vertices[2], color[BLACK]),

        Vertex(vertices[3], color[BLACK]),
        Vertex(vertices[11], color[BLACK]),
        Vertex(vertices[0], color[BLACK]),

        Vertex(vertices[0], color[BLACK]),
        Vertex(vertices[11], color[BLACK]),
        Vertex(vertices[8], color[BLACK]),

        Vertex(vertices[8], color[RED]),
        Vertex(vertices[11], color[RED]),
        Vertex(vertices[9], color[RED]),

        Vertex(vertices[11], color[RED]),
        Vertex(vertices[10], color[RED]),
        Vertex(vertices[9], color[RED]),

        // front
        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[12], color[BLACK]),

        Vertex(vertices[12], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[13], color[BLACK]),

        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[13], color[BLACK]),

        Vertex(vertices[13], color[BLACK]),
        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[14], color[BLACK]),

        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[14], color[BLACK]),

        Vertex(vertices[14], color[BLACK]),
        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[15], color[BLACK]),

        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[15], color[BLACK]),

        Vertex(vertices[15], color[BLACK]),
        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[12], color[BLACK]),

        Vertex(vertices[12], color[ORANGE]),
        Vertex(vertices[13], color[ORANGE]),
        Vertex(vertices[14], color[ORANGE]),
        Vertex(vertices[14], color[ORANGE]),
        Vertex(vertices[15], color[ORANGE]),
        Vertex(vertices[12], color[ORANGE]),

        // top
        Vertex(vertices[2], color[BLACK]),
        Vertex(vertices[3], color[BLACK]),
        Vertex(vertices[16], color[BLACK]),

        Vertex(vertices[16], color[BLACK]),
        Vertex(vertices[3], color[BLACK]),
        Vertex(vertices[17], color[BLACK]),

        Vertex(vertices[3], color[BLACK]),
        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[17], color[BLACK]),

        Vertex(vertices[17], color[BLACK]),
        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[18], color[BLACK]),

        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[18], color[BLACK]),

        Vertex(vertices[18], color[BLACK]),
        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[19], color[BLACK]),

        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[2], color[BLACK]),
        Vertex(vertices[19], color[BLACK]),

        Vertex(vertices[19], color[BLACK]),
        Vertex(vertices[2], color[BLACK]),
        Vertex(vertices[16], color[BLACK]),

        Vertex(vertices[16], color[GREEN]),
        Vertex(vertices[17], color[GREEN]),
        Vertex(vertices[18], color[GREEN]),
        Vertex(vertices[18], color[GREEN]),
        Vertex(vertices[19], color[GREEN]),
        Vertex(vertices[16], color[GREEN]),

        // bottom
        Vertex(vertices[0], color[BLACK]),
        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[20], color[BLACK]),

        Vertex(vertices[20], color[BLACK]),
        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[21], color[BLACK]),

        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[21], color[BLACK]),

        Vertex(vertices[21], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[22], color[BLACK]),

        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[22], color[BLACK]),

        Vertex(vertices[22], color[BLACK]),
        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[23], color[BLACK]),

        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[0], color[BLACK]),
        Vertex(vertices[23], color[BLACK]),

        Vertex(vertices[23], color[BLACK]),
        Vertex(vertices[0], color[BLACK]),
        Vertex(vertices[20], color[BLACK]),

        Vertex(vertices[20], color[BLUE]),
        Vertex(vertices[21], color[BLUE]),
        Vertex(vertices[22], color[BLUE]),
        Vertex(vertices[22], color[BLUE]),
        Vertex(vertices[23], color[BLUE]),
        Vertex(vertices[20], color[BLUE]),

        // left
        Vertex(vertices[0], color[BLACK]),
        Vertex(vertices[24], color[BLACK]),
        Vertex(vertices[3], color[BLACK]),

        Vertex(vertices[24], color[BLACK]),
        Vertex(vertices[25], color[BLACK]),
        Vertex(vertices[3], color[BLACK]),

        Vertex(vertices[3], color[BLACK]),
        Vertex(vertices[25], color[BLACK]),
        Vertex(vertices[7], color[BLACK]),

        Vertex(vertices[25], color[BLACK]),
        Vertex(vertices[26], color[BLACK]),
        Vertex(vertices[7], color[BLACK]),

        Vertex(vertices[7], color[BLACK]),
        Vertex(vertices[26], color[BLACK]),
        Vertex(vertices[4], color[BLACK]),

        Vertex(vertices[26], color[BLACK]),
        Vertex(vertices[27], color[BLACK]),
        Vertex(vertices[4], color[BLACK]),

        Vertex(vertices[4], color[BLACK]),
        Vertex(vertices[27], color[BLACK]),
        Vertex(vertices[0], color[BLACK]),

        Vertex(vertices[27], color[BLACK]),
        Vertex(vertices[24], color[BLACK]),
        Vertex(vertices[0], color[BLACK]),

        Vertex(vertices[24], color[WHITE]),
        Vertex(vertices[26], color[WHITE]),
        Vertex(vertices[25], color[WHITE]),
        Vertex(vertices[27], color[WHITE]),
        Vertex(vertices[26], color[WHITE]),
        Vertex(vertices[24], color[WHITE]),

        // right
        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[2], color[BLACK]),
        Vertex(vertices[28], color[BLACK]),

        Vertex(vertices[28], color[BLACK]),
        Vertex(vertices[2], color[BLACK]),
        Vertex(vertices[29], color[BLACK]),

        Vertex(vertices[2], color[BLACK]),
        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[29], color[BLACK]),

        Vertex(vertices[29], color[BLACK]),
        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[30], color[BLACK]),

        Vertex(vertices[6], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[30], color[BLACK]),

        Vertex(vertices[30], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[31], color[BLACK]),

        Vertex(vertices[5], color[BLACK]),
        Vertex(vertices[1], color[BLACK]),
        Vertex(vertices[28], color[BLACK]),

        Vertex(vertices[28], color[BLACK]),
        Vertex(vertices[31], color[BLACK]),
        Vertex(vertices[5], color[BLACK]),

        Vertex(vertices[28], color[YELLOW]),
        Vertex(vertices[29], color[YELLOW]),
        Vertex(vertices[30], color[YELLOW]),
        Vertex(vertices[30], color[YELLOW]),
        Vertex(vertices[31], color[YELLOW]),
        Vertex(vertices[28], color[YELLOW]),
    };

    importData(unit_cube, sizeof(unit_cube)/sizeof(Vertex));
}

void Mesh::importData(Vertex* side_vertices, unsigned int numSideVertices)
{
    for (unsigned int i = 0; i < numSideVertices; i++) {
        m_model.positions.push_back(*side_vertices[i].GetPos());
        m_model.colors.push_back(*side_vertices[i].GetColor());
    }

    initMesh(m_model);
    //std::cout << m_valid_vb[0] << ", " << m_valid_vb[1] << std::endl;
}

Mesh::~Mesh()
{

}

void Mesh::initMesh(const Model &model)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(NUM_BUFFERS, m_vbos);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[COLOR_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.colors.size() * sizeof(model.colors[0]), &model.colors[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindVertexArray(0);
}
