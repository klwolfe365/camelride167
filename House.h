//
//  House.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/8/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef CSE167_House_h
#define CSE167_House_h

#include <iostream>
#include "Drawable.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"

class House : public Drawable
{
public:

    House();
    ~House();
   
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    virtual void idle();
    
    virtual void myDraw(DrawData&);
};
#endif
