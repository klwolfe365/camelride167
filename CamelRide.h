//
//  CamelRide.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Tim on 6/9/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__CamelRide__
#define __CSE167_Spring_2015_Starter_Code__CamelRide__

#include <stdio.h>
#include "Group.h"
#include "Geode.h"
#include "Terrain.h"
#include "ParticleSystem.h"
#include "MatrixTransform.h"
#include "Matrix4.h"
#include "BezierCurve.h"

class CamelRide : public Geode {
    
public:
    float path = 0.0;
    int controlPointIdx = 0;
    bool reversePath = false;
    
    Group* root;
    MatrixTransform* rootTrans;
    
    Geode* camel;
    MatrixTransform *camelTrans;
    
    Terrain *desert;
    MatrixTransform *desertTrans;
    
    ParticleSystem *sandstorm;
    MatrixTransform *sandstormTrans;
    
    BezierCurve b;
    
    CamelRide();
    ~CamelRide();
    
    virtual void draw(Matrix4 c);
    virtual void update();
    
    void centerDesert();
    void moveCamel();
    
    BezierCurve getCurve;
    
    Vector3 getCurveToPoint(Vector3 currPoint, Vector3 newPoint);
    
    void moveSandstorm(float x, float y, float z);
    void rotateSandstorm(Vector3 rot_axis, float angle);
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__CamelRide__) */
