//
//  DirectionalLight.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__DirectionalLight__
#define __CSE167_Spring_2015_Starter_Code__DirectionalLight__

#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Light.h"
#include "Drawable.h"

class DirectionalLight : public Light{

public:
    DirectionalLight();
    ~DirectionalLight();
    
    Vector4 direction;

    virtual void draw(Matrix4 c);
    virtual void update();
    virtual void idle();
    
    virtual void myDraw(DrawData&);
    

};


#endif /* defined(__CSE167_Spring_2015_Starter_Code__DirectionalLight__) */
