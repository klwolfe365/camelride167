//
//  SpotLight.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/1/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//




#ifndef __CSE167_Spring_2015_Starter_Code__SpotLight__
#define __CSE167_Spring_2015_Starter_Code__SpotLight__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Drawable.h"
#include "Light.h"



class SpotLight : public Light {
    
public:
    Vector4 coneDirection;
    Vector4 rayDirection;
    float lighSurfaceAngle;
    
    
    SpotLight();
    ~SpotLight();
    
    //Draw point light as a sphere
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    virtual void idle();
    
    virtual void myDraw(DrawData&);
    
    
    
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__SpotLight__) */
