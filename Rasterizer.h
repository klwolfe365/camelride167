//
//  Rasterizer.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/14/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef CSE167_Rasterizer_h
#define CSE167_Rasterizer_h

#include <stdio.h>
#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"



class Rasterizer{

public:
    
    static float lx, ux, ly, uy;
    static float alpha, beta, gamma;
    static float theta;

    static Matrix4* d;
    static Matrix4* p;
    
    
    
    //float r, g,b;
    
    Rasterizer();
    ~Rasterizer();
    
    void clearBuffer();
    Vector4 rasterizeVertex(Vector4 vertex);
    void drawPoint(Vector4 vertex, Color c);
   // void rasterizeVertex(float x, float y, float z, float r, float g, float b);
    void rasterize(void);
    void computeBoundingBox(Vector4 v0, Vector4 v1, Vector4 v2);
    void setBaryCoords(Vector4 p, Vector4 a, Vector4 b, Vector4 c);
    bool zBuffer(int x, int y, Vector4 v0, Vector4 v1, Vector4 v2);
    Color getColor(Vector3 v0, Vector3 v1, Vector3 v2);
    void rasterizeTriangle(Vector4 v0, Vector4 v1, Vector4 v2, Vector3 na, Vector3 nb, Vector3 nc, Color c);
    
    void reshape(int new_width, int new_height);
    void display();
    static void update_p();
    static void update_d();

};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__Rasterizer__) */
