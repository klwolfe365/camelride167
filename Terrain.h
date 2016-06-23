//
//  Terrain.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/14/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifndef __CSE167_Spring_2015_Starter_Code__Terrain__
#define __CSE167_Spring_2015_Starter_Code__Terrain__

#include <stdio.h>
#include "Vector3.h"
#include "Texture.h"
#include "Node.h"
#include "Color.h"

#define HEIGHT 1024
#define WIDTH 1024

#define BEZ_POINTS 4.0
#define BEZ_ACC 1.0 / BEZ_POINTS  //value t gets incremented by
#define PORTION 4.0              // 1/PORTION of the terrain will be drawn
#define DEFAULT_BEZIER 0        // 0 means bezier will not be the default

class Terrain : public Node{
public:
    unsigned char* height_map;
    Vector3 coords[WIDTH][HEIGHT];
    Vector3 normal[WIDTH][HEIGHT];
    Vector3 normal_bezier[WIDTH * (int)BEZ_POINTS/4][HEIGHT * (int)BEZ_POINTS/4];
    int num_vert;
    int num_ind;
    int width;
    int height;
    float max_height;
    float band_height;
    bool draw_bezier;
    Texture * map_texture;
    Color terrain_color;

    Terrain();
    Terrain(const char * ppmFile);
    ~Terrain();
    
    bool init(const char * ppmFile);
    void draw(Matrix4 c);
    void drawNormal(Matrix4 c);
    void drawBezier(Matrix4 c);
    
    void update();
    
    void heighten(int y);
    void setNormals();
    void setNormalsBezier();
    void update_levels(float y);
    Vector4 getColor(float y);
    float getLevel(float y);
    //ex*heitmap y
    
    void setBezierMode(bool draw_bezier);
    
};
#endif /* defined(__CSE167_Spring_2015_Starter_Code__Terrain__) */