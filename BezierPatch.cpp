//
//  BezierPatch.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Tim on 6/8/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "BezierPatch.h"

BezierPatch::BezierPatch(BezierCurve c1, BezierCurve c2, BezierCurve c3, BezierCurve c4)
{
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;
    this->c4 = c4;
}

BezierPatch::BezierPatch(Vector3 cp1, Vector3 cp2, Vector3 cp3, Vector3 cp4,
                         Vector3 cp5, Vector3 cp6, Vector3 cp7, Vector3 cp8,
                         Vector3 cp9, Vector3 cp10, Vector3 cp11, Vector3 cp12,
                         Vector3 cp13, Vector3 cp14, Vector3 cp15, Vector3 cp16)
{
    this->c1 = BezierCurve(cp1, cp2, cp3, cp4);
    this->c2 = BezierCurve(cp5, cp6, cp7, cp8);
    this->c3 = BezierCurve(cp9, cp10, cp11, cp12);
    this->c4 = BezierCurve(cp13, cp14, cp15, cp16);
}

Vector3 BezierPatch::getPoint(float u, float v)
{
    if(this->u != u) {
        this->u = u;
        b = BezierCurve(c1.getPoint(u), c2.getPoint(u), c3.getPoint(u), c4.getPoint(u));
    }

    return b.getPoint(v);
}