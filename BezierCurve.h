//
//  BezierCurve.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Tim on 6/8/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__BezierCurve__
#define __CSE167_Spring_2015_Starter_Code__BezierCurve__

#include <stdio.h>
#include "Vector3.h"

class BezierCurve
{
private:
    
public:
    Vector3 c1;
    Vector3 c2;
    Vector3 c3;
    Vector3 c4;
    Vector3 b1, b2;
    
    BezierCurve();
    BezierCurve(Vector3 c1, Vector3 c2, Vector3 c3, Vector3 c4);
    
    Vector3 getPoint(float t);
    void setControlPoints(Vector3 c1, Vector3 c2, Vector3 c3, Vector3 c4);
    
};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__BezierCurve__) */
