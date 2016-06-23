//
//  PointLight.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__PointLight__
#define __CSE167_Spring_2015_Starter_Code__PointLight__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Drawable.h"
#include "Light.h"
#include "Vector3.h"



class PointLight : public Light {
    
public:
    Vector4 coneDirection;
    Vector4 rayDirection;
    float lighSurfaceAngle;
    float x = 0;
    float y = 100;
    float z = 900;
    float k = 350;
    float h = 1024.0/2.0;;
    float delta = 10;
    float a = -.0005;
    Vector3 white = Vector3(1.0,1.0,1.0);
    Vector3 yellow = Vector3(1.0,1.0,0.0);
    
    
    PointLight();
    ~PointLight();
        
    //Draw point light as a sphere
    
    virtual void draw(Matrix4 c);
    virtual void update();
    virtual void idle();
    
    virtual void myDraw(DrawData&);
    
    
    
};


#endif /* defined(__CSE167_Spring_2015_Starter_Code__PointLight__) */
