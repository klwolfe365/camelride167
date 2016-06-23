//
//  Terrain.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/14/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Terrain.h"
#include "Cylinder.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Globals.h"
#include "Shader.h"
#include "BezierPatch.h"

#define COLOR_R 237.0 / 256.0
#define COLOR_G 201.0 / 256.0
#define COLOR_B 175.0 / 256.0

Terrain::Terrain() : Node(){
    
    terrain_color = Color(COLOR_R, COLOR_G, COLOR_B);
    
    draw_bezier = false;
    map_texture = NULL;
    num_vert = num_ind = 0;
    width = WIDTH;
    height = HEIGHT;
    height_map = (unsigned char*)malloc( width * width * sizeof(unsigned char));
    
    for(int i = 0; i < width*height; i++)
        height_map[i] = 0;
    //num_ind = generateIndices(height_map, width, height);
    draw_bezier = false;
}

Terrain::Terrain(const char * ppmFile) : Terrain()
{
    init(ppmFile);
    draw_bezier = true;
}

Terrain::~Terrain(){}

bool Terrain::init(const char * ppmFile){
    height_map = Texture::loadPPM(ppmFile, width, height);
    /*
     Create a 1024*1024 array of vertex coordinates (Vector3). Populate the
     array as follows: the x values should correspond to the array's x index,
     the z values to the y index. For example: Vector3[x][y].x = x,
     Vector3[x][y].z = y. The y value should be the corresponding value from
     the height map array (Vector3[x][y].y = heightmap[x][y]).
     */
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            coords[x][y] = Vector3(x, height_map[3*(x*height + y)], y);
            if((coords[x][y])[1] > max_height)
                max_height = (coords[x][y])[1];
        }
    }
    
    setNormals();
    update_levels(0);
    return true;
}

void Terrain::draw(Matrix4 c)
{
    draw_bezier ? drawNormal(c) : drawBezier(c);
}

void Terrain::drawNormal(Matrix4 c){
    //glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    
    //    Globals::shader->bind();
    //    GLint loc = glGetUniformLocationARB(Globals::shader->getPid(), "water_level");
    //    glUniform1f(loc, Shader::water_level);
    //   // GLint col = glGetAttribLocationARB(Globals::shader->getPid(), "gl_Color");
    //    GLint bandLoc = glGetUniformLocationARB(Globals::shader->getPid(), "band_width");
    //    glUniform1f(bandLoc, Shader::band_width);
    
    // glDisable(GL_LIGHTING);
    for(int h = 0; h < (height/PORTION) - 1; h++){
        glBegin(GL_TRIANGLE_STRIP);
        for(int w = 0; w < (width/PORTION); w++){
            Vector3 curr = coords[w][h+1];
            Vector3 n;
            
            Vector3 prev = coords[w][h];
            n = normal[w][h+1];
            glColor3f(terrain_color[0], terrain_color[1], terrain_color[2]);
            glNormal3f(n[0],n[1],n[2]);
            
            glVertex3f(prev[0], prev[1], prev[2]);
            glVertex3f(curr[0], curr[1], curr[2]);
            
        }
        glEnd();
    }
    //Globals::shader->unbind();
    glPopMatrix();
    //glEnable(GL_LIGHTING);
}

void Terrain::drawBezier(Matrix4 c)
{
    //glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    
    //    Globals::shader->bind();
    //    GLint loc = glGetUniformLocationARB(Globals::shader->getPid(), "water_level");
    //    glUniform1f(loc, Shader::water_level);
    // // GLint col = glGetAttribLocationARB(Globals::shader->getPid(), "gl_Color");
    //    GLint bandLoc = glGetUniformLocationARB(Globals::shader->getPid(), "band_width");
    //    glUniform1f(bandLoc, Shader::band_width);
    
    //    glDisable(GL_LIGHTING);
    
    int indexW, indexH;
    for(int h = 0; h < (height/PORTION) - 4; h += 3){
        for(int w = 0; w < (width/PORTION) - 4; w += 3){
            BezierPatch p = BezierPatch(coords[w][h], coords[w+1][h], coords[w+2][h], coords[w+3][h],
                                        coords[w][h+1], coords[w+1][h+1], coords[w+2][h+1], coords[w+3][h+1],
                                        coords[w][h+2], coords[w+1][h+2], coords[w+2][h+2], coords[w+3][h+2],
                                        coords[w][h+3], coords[w+1][h+3], coords[w+2][h+3], coords[w+3][h+3]);
            
            for(float u = 0.0; u <= 1.0 - BEZ_ACC; u += BEZ_ACC)
            {
                glBegin(GL_TRIANGLE_STRIP);
                for(float v = 0.0; v <= 1.0; v += BEZ_ACC)
                {
                    glColor3f(terrain_color[0], terrain_color[1], terrain_color[2]);
                    glVertex3fv(p.getPoint(u, v).ptr());
                    glVertex3fv(p.getPoint(u + BEZ_ACC, v).ptr());
                    indexW = w + (int)(BEZ_POINTS*u);
                    indexH = h + (int)(BEZ_POINTS*v);
                    glNormal3fv(normal_bezier[indexW][indexH+1].ptr());
                }
                glEnd();
            }
        }
    }
    
    //Globals::shader->unbind();
    glPopMatrix();
    //glEnable(GL_LIGHTING);
}

void Terrain::update(){}

void Terrain::heighten(int y){
    int scaleFact = .1;
    if(y<0){
        scaleFact *= -1;
    }
    max_height = 0;
    
    
    for(int w = 0; w < width; w++){
        for(int h = 0; h< height; h++){
            (coords[w][h])[1] += height_map[3*(w*width+h)+1]*scaleFact;
            if((coords[w][h])[1] > max_height)
                max_height = (coords[w][h])[1];
        }
    }
    setNormals();
}

void Terrain::setNormals(){
    setNormalsBezier();
    
    for(int r = 1; r < width - 1; r++){
        for(int c = 0; c < height - 1; c++){
            normal[r][c] = (coords[r][c+1]-coords[r][c]).cross(coords[r-1][c]-coords[r][c]);
            normal[r][c] = (normal[r][c]).normalize()*-1;
        }
    }
    for(int i = 0; i < width - 2; i++){
        normal[0][i] = (coords[1][i] - coords[0][i]).cross(coords[0][i+1]-coords[0][i]);
        normal[0][i] = (normal[0][i]).normalize();
        normal[i][height - 1] = (coords[i-1][height - 1] - coords[i][height - 1]).cross(coords[i][height - 1]-coords[i][height -1]);
        normal[i][height - 1] = (normal[i][height - 1]).normalize();
        
    }
}

void Terrain::setNormalsBezier()
{
    Vector3 v1, v2, v3, v4;
    int indexW, indexH;
    
    for(int h = 0; h < (height/PORTION) - 4; h += 3){

        for(int w = 0; w < (width/PORTION) - 4; w += 3){
            
            BezierPatch p = BezierPatch(coords[w][h], coords[w+1][h], coords[w+2][h], coords[w+3][h],
                                        coords[w][h+1], coords[w+1][h+1], coords[w+2][h+1], coords[w+3][h+1],
                                        coords[w][h+2], coords[w+1][h+2], coords[w+2][h+2], coords[w+3][h+2],
                                        coords[w][h+3], coords[w+1][h+3], coords[w+2][h+3], coords[w+3][h+3]);
            
            for(float u = 0.0; u <= 1.0 - BEZ_ACC; u += BEZ_ACC)
            {
                for(float v = 0.0; v <= 1.0 - BEZ_ACC; v += BEZ_ACC)
                {
                    v1 = p.getPoint(u, v);
                    v2 = p.getPoint(u, v+1);
                    v3 = p.getPoint(u+1, v);
                    v4 = p.getPoint(u+1, v+1);
                    indexW = w + (int)(BEZ_POINTS*u);
                    indexH = h + (int)(BEZ_POINTS*v);
                    normal_bezier[indexW][indexH] = (v2-v1).cross(v3-v1).normalize();
                    normal_bezier[indexW][indexH+1] = (v3-v4).cross(v2-v4).normalize();
                }
            }
        }
    }

}

//right cross above
//end row above to left

void Terrain::update_levels(float y){
    if(y>0)
        Shader::water_level += 5;
    else if (y < 0)
        Shader::water_level -= 5;
    Shader::band_width = (max_height-Shader::water_level)/4;
}

Vector4 Terrain::getColor(float y){
    float level = (y - Shader::water_level)/band_height;
    Vector4 color;
    /*Water Level*/
    if(y <= Shader::water_level)
        return Vector4(0.0,0.0,1.0);
    /*Das beach yah*/
    else if(level < .2)
        return Vector4(1.0,1.0,0.0);
    else if(level < 1.0)
        return Vector4(0.0,1.0,0.0);
    else if(level < 1.8)
        return Vector4(0.2,0.2,0.2);
    else
        return Vector4(1.0,1.0,1.0);
}

float Terrain::getLevel(float y){
    float level = (y - Shader::water_level)/Shader::band_width;
    /*Water Level*/
    if(y <= Shader::water_level)
        return 1.0;
    /*Das beach yah*/
    else if(level < .2)
        return 1.0;
    else if(level < 1.0)
        return 2.0;
    else if(level < 1.8)
        return 3.0;
    else
        return 4.0;
}

void Terrain::setBezierMode(bool draw_bezier)
{
    if(this->draw_bezier != draw_bezier)
    {
        this->draw_bezier = draw_bezier;
        draw_bezier ? setNormalsBezier() : setNormals();
    }
}