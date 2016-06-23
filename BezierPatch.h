//
//  BezierPatch.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Tim on 6/8/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__BezierPatch__
#define __CSE167_Spring_2015_Starter_Code__BezierPatch__

#include <stdio.h>
#include "BezierCurve.h"

class BezierPatch
{
public:
    BezierCurve c1, c2, c3, c4;
    BezierCurve b;
    float u;
    
    BezierPatch(BezierCurve c1, BezierCurve c2, BezierCurve c3, BezierCurve c4);
    BezierPatch(Vector3, Vector3, Vector3, Vector3,
                Vector3, Vector3, Vector3, Vector3,
                Vector3, Vector3, Vector3, Vector3,
                Vector3, Vector3, Vector3, Vector3);
    
    Vector3 getPoint(float u, float v);
};


#endif /* defined(__CSE167_Spring_2015_Starter_Code__BezierPatch__) */