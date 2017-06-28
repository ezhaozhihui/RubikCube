//
//  shader.cpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/6.
//  Copyright © 2017年 EZ. All rights reserved.
//

#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& fileName)
{
    m_program = glCreateProgram();
    m_shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);

    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

Shader::~Shader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

std::string Shader::loadShader(const std::string &fileName)
{
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

GLuint Shader::createShader(const std::string &text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        std::cerr << "Create shader failed" << std::endl;

    const GLchar* p[1];
    GLint lengths[1];

    p[0] = text.c_str();
    lengths[0] = static_cast<GLint>(text.length());

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    return shader;
}

void Shader::use()
{
    glUseProgram(m_program);
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram)
    {
        glGetProgramiv(shader, flag, &success);
    }
    else
    {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE)
    {
        if (isProgram)
        {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
        else
        {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, NULL, glm::value_ptr(matrix));
}
