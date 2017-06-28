//
//  camera.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/12.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class Camera
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        this->pos = pos;
        this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
        this->up = glm::vec3(0.0f, 1.0f, 0.0f);
        this->projection = glm::perspective(fov, aspect, zNear, zFar);
    }

    inline glm::mat4 getProjView() const
    {
        return projection * glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), up);
    }

    //void MoveForward(float amt)
    //{
    //	pos += forward * amt;
    //}

    //void MoveRight(float amt)
    //{
    //	pos += glm::cross(up, forward) * amt;
    //}

    //void Pitch(float angle)
    //{
    //	glm::vec3 right = glm::normalize(glm::cross(up, forward));

    //	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
    //	up = glm::normalize(glm::cross(forward, right));
    //}

    //void RotateY(float angle)
    //{
    //	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

    //	glm::mat4 rotation = glm::rotate(angle, UP);

    //	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
    //	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
    //}
    
protected:
private:
    glm::mat4 projection;
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;
};


#endif /* camera_h */
