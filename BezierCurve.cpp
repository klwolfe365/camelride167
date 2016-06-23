//
//  BezierCurve.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Tim on 6/8/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
    c1 = c2 = c3 = c4 = Vector3();
}

BezierCurve::BezierCurve(Vector3 c1, Vector3 c2, Vector3 c3, Vector3 c4)
{
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;
    this->c4 = c4;
}

Vector3 BezierCurve::getPoint(float t)
{
    float n = 1.0 - t;
    return  (c1 * (n * n * n)) +
            (c2 * (t * n * n * 3)) +
            (c3 * (t * t * n * 3)) +
            (c4 * (t * t * t));;
}

void BezierCurve::setControlPoints(Vector3 c1, Vector3 c2, Vector3 c3, Vector3 c4)
{
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;
    this->c4 = c4;
}