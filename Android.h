//
//  Android.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/11/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Android__
#define __CSE167_Spring_2015_Starter_Code__Android__

#include <stdio.h>
#include "Geode.h"
#include "Matrix4.h"
#include "MatrixTransform.h"
#include "Group.h"
#include "Texture.h"
#include "Cylinder.h"
#include "Sphere.h"

class Android : public Geode {

public:
    Texture* headS;
    Texture* headT;
    Texture* headB;
    Cylinder* head;
    Cylinder* torso;
    Cylinder* arm;
    Cylinder* leg;
    MatrixTransform* armSwingL = new MatrixTransform(Matrix4().setIdentity());
    MatrixTransform* armSwingR = new MatrixTransform(Matrix4().setIdentity());
    MatrixTransform* legSwingL = new MatrixTransform(Matrix4().setIdentity());
    MatrixTransform* legSwingR = new MatrixTransform(Matrix4().setIdentity());
    MatrixTransform* armMovement = new MatrixTransform(Matrix4().setIdentity());
    MatrixTransform* legMovement = new MatrixTransform(Matrix4().setIdentity());
    float rotAngleA = M_PI/180;
    float rotAngleL = M_PI/180;
    float deltaA = M_PI/90;
    float deltaL = M_PI/180;
    
    Group* root;
    Android();
    ~Android();
    
    virtual void draw(Matrix4 c);
    virtual void update();
    
    void setTextures(std::vector<Texture*> t);

};
#endif /* defined(__CSE167_Spring_2015_Starter_Code__Android__) */

