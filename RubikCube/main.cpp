//
//  main.cpp
//  RubikCube
//
//  Created by 赵智慧 on 2017/5/31.
//  Copyright © 2017年 EZ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include "rubik_cube.hpp"

int main(int argc, const char * argv[]) {

    auto app = make_app<RubikCube>("RubikCube", 800, 600);

    app->start();

    return 0;
}
