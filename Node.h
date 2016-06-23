//
//  Node.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Node__
#define __CSE167_Spring_2015_Starter_Code__Node__

#include <stdio.h>
#include "Matrix4.h"
#include "DrawData.h"

class Node
{
public:    
    Node();
    ~Node();
    
    virtual void draw(Matrix4 c);
    virtual void update();
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Node__) */
