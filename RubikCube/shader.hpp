//
//  shader.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/6.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <string>
#include "GL/glew.h"
#include "camera.hpp"

class Shader {
public:
    Shader(const std::string& fileName);
    Shader() {}

    void use();

    void setMatrix4(const GLchar* name, const glm::mat4& matrix);
    

    virtual ~Shader();

private:
    static const unsigned int NUM_SHADERS = 2;
    static const unsigned int NUM_UNIFORMS = 3;

    std::string loadShader(const std::string& fileName);
    GLuint createShader(const std::string& text, unsigned int type);

    void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif /* shader_hpp */
