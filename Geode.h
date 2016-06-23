//
//  Geode.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Geode__
#define __CSE167_Spring_2015_Starter_Code__Geode__

#include <stdio.h>
#include "Node.h"
#include "Matrix4.h"

class Geode : public Node
{
public:
    Geode();
    ~Geode();
    
    Vector3 center;
    
    virtual void draw(Matrix4 c);
    virtual void update();
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Geode__) */
