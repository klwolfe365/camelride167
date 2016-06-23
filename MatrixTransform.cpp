//
//  MatrixTransform.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "MatrixTransform.h"

MatrixTransform::MatrixTransform() : Group()
{
    trans.identity();
}

MatrixTransform::MatrixTransform(Matrix4 t) : Group(){
    trans = t;
}

MatrixTransform::~MatrixTransform(){}

void MatrixTransform::draw(Matrix4 c){
    Matrix4 c_new = c*trans;
    Group::draw(c_new);
}