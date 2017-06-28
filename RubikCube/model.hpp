//
//  model.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/10.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <glm/glm.hpp>
#include <vector>

class Model
{
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
};

#endif /* model_hpp */
