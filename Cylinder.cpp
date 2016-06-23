//
//  Cylinder.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Cylinder.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Vector4.h"
#include <math.h>

Cylinder::Cylinder(float h, float r) : Geode(){
    this->h = h;
    this->r = r;
}

Cylinder::~Cylinder(){};

void Cylinder::draw(Matrix4 c){
    glDisable(GL_LIGHTING);
    //material.apply();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    // Reset and transform the matrix.
    
    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);
    
    float theta = 2*M_PI/100;
    for(float i = 0; i < 2*M_PI; i += theta){
        //Create points to add to point container
        cylinTop->bind();
        glBegin(GL_TRIANGLES);
        
        glTexCoord2f((i+theta)/(2*M_PI), 0);
        glVertex3f(r*sin(i+theta), h, r*cos(i+theta));
        glTexCoord2f(.5, .5);
        glVertex3f(0, h, 0);
        glTexCoord2f(i/(2*M_PI), 0);
        glVertex3f(r*sin(i), h, r*cos(i));
        
        glEnd();
        
        surfaceText->bind();
        glBegin(GL_QUADS);
        /*Base of quad*/
        glTexCoord2f(i/(2*M_PI), 1);
        glVertex3f(r*sin(i), 0, r*cos(i));
        glTexCoord2f((i+theta)/(2*M_PI), 1);
        glVertex3f(r*sin(i+theta), 0, r*cos(i+theta));
        
        /*Top of quad*/
        glTexCoord2f((i+theta)/(2*M_PI), 0);
        glVertex3f(r*sin(i+theta), h, r*cos(i+theta));
        glTexCoord2f(i/(2*M_PI), 0);
        glVertex3f(r*sin(i), h, r*cos(i));

        glEnd();
        
        cylinBot->bind();
        glBegin(GL_TRIANGLES);
        
        glTexCoord2f((i+theta)/(2*M_PI), 0);
        glVertex3f(r*sin(i+theta), 0, r*cos(i+theta));
        glTexCoord2f(.5, .5);
        glVertex3f(0, 0, 0);
        glTexCoord2f(i/(2*M_PI), 0);
        glVertex3f(r*sin(i), 0, r*cos(i));
        
        glEnd();
    }
    
    glPopMatrix();
    glEnable(GL_LIGHTING);


}
void Cylinder::update(){}
void Cylinder::idle(){}
void Cylinder::myDraw(DrawData& data){}

void Cylinder::setTextures(Texture* surface, Texture* top, Texture* bot){
    surfaceText = surface;
    cylinTop = top;
    cylinBot = bot;
}

