//
//  Ground.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/14/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Ground__
#define __CSE167_Spring_2015_Starter_Code__Ground__

#include <stdio.h>
#include "Geode.h"
#include "Matrix4.h"

class Ground : public Geode {

public:
    Ground();
    ~Ground();
    
    void draw(Matrix4 c);
    void update();
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Ground__) */
