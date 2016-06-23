//
//  Ground.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/14/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Ground.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Ground::Ground() : Geode(){}
Ground::~Ground(){}

void Ground::draw(Matrix4 c){
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(c.ptr());
    glDisable(GL_LIGHTING);
    glColor3f(0.35, .85, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-200, -3.5, -200);
    glVertex3f(-200, -3.5,  200);
    glVertex3f( 200, -3.5,  200);
    glVertex3f( 200, -3.5, -200);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

void Ground::update(){}