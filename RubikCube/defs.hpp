//
//  defs.hpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/6/11.
//  Copyright © 2017年 EZ. All rights reserved.
//

#ifndef defs_h
#define defs_h

static glm::vec3 color[] =
{
    {0.953f , 0.0f   , 0.0f}   , // red
    {0.024f , 0.980f , 0.0f}   , // green
    {0.400f , 0.412f , 1.0f} , // blue
    {0.997f , 1.0f   , 0.275f}  , // yellow
    {0.992f , 0.384f , 0.0f}   , // orange
    {0.900f , 0.900f , 0.900f} , // white
    {0.196f , 0.196f , 0.196f}  , // black
};

enum Color
{
    RED = 0,
    GREEN = 1,
    BLUE = 2,
    YELLOW = 3,
    ORANGE = 4,
    WHITE = 5,
    BLACK = 6,
};

#endif /* defs_h */
