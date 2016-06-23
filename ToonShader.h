//
//  ToonShader.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/31/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__ToonShader__
#define __CSE167_Spring_2015_Starter_Code__ToonShader__

#include <stdio.h>
#include "Matrix4.h"
#include "Node.h"

class ToonShader : public Node{
public:
    ToonShader();
    ~ToonShader();

    bool init(const char * ppmFile);
    void draw(Matrix4 c);
    void update();

    void heighten(int y);
    void setNormals();
    void update_levels(float y);
    Vector4 getColor(float y);
    float getLevel(float y);

};
#endif /* defined(__CSE167_Spring_2015_Starter_Code__ToonShader__) */
