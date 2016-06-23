//
//  Skybox.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/6/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Skybox__
#define __CSE167_Spring_2015_Starter_Code__Skybox__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "Drawable.h"
#include "Geode.h"
#include "Texture.h"

class Skybox : public Geode {
public:
    float size;
    Texture* front;
    Texture* back;
    Texture* top;
    Texture* bottom;
    Texture* left;
    Texture* right;
    
    Skybox(float);
    
    ~Skybox();
    
    virtual void draw(Matrix4 c);
    virtual void update();
    //virtual void idle();
    
    //virtual void myDraw();

};
#endif /* defined(__CSE167_Spring_2015_Starter_Code__Skybox__) */
