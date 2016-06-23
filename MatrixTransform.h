//
//  MatrixTransform.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__MatrixTransform__
#define __CSE167_Spring_2015_Starter_Code__MatrixTransform__

#include <stdio.h>
#include "Group.h"
#include "Matrix4.h"
#include "DrawData.h"

class MatrixTransform : public Group
{
public:
    Matrix4 trans;
    MatrixTransform();
    MatrixTransform(Matrix4 t);
    ~MatrixTransform();
    virtual void draw(Matrix4 c);
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__MatrixTransform__) */
