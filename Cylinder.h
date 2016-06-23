//
//  Cylinder.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Cylinder__
#define __CSE167_Spring_2015_Starter_Code__Cylinder__

#include <stdio.h>
#include "Drawable.h"
#include "Texture.h"
#include "Geode.h"


class Cylinder : public Geode
{
public:

    float h;
    float r;
    Texture* surfaceText;
    Texture* cylinTop;
    Texture* cylinBot;
    
    Cylinder(float, float);
    virtual ~Cylinder(void);
    
    virtual void draw(Matrix4 c);
    virtual void update();
    
    virtual void idle();
    virtual void myDraw(DrawData&);
    
    void setTextures(Texture* surface, Texture* top, Texture* bot);
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Cylinder__) */
