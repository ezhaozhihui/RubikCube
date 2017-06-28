//
//  mesh.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/10.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <GL/glew.h>
#include <string>
#include "model.hpp"
#include "shader.hpp"


struct Vertex
{
public:
    Vertex(const glm::vec3& pos, const glm::vec3& color)
    {
        this->pos = pos;
        this->color = color;
    }

    glm::vec3* GetPos() { return &pos; }
    glm::vec3* GetColor() { return &color; }

private:
    glm::vec3 pos;
    glm::vec3 color;
};

enum MeshBufferPositions
{
    POSITION_VB = 0,
    COLOR_VB,
};

class Mesh
{
public:
    Mesh(Shader& shader);
    void importData(Vertex* side_vertices, unsigned int numSideVertices);

    void draw(const glm::vec3& position, const glm::mat4& rot_mat, const glm::mat4& proj_view);

    virtual ~Mesh();

private:
    static const unsigned int NUM_BUFFERS = 2;

    void initMesh(const Model& model);

    GLuint m_vao;
    GLuint m_vbos[NUM_BUFFERS];

    Model m_model;
    Shader shader;
};

#endif /* mesh_hpp */
