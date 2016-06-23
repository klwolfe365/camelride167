//
//  Skybox.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/6/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Skybox.h"
//#include "Globals.h"

Skybox::Skybox(float size) : Geode(){
    this->size = size;
}

Skybox::~Skybox(){}

//pass the size of cube in ctor and then in globals have skybox -- pass the size; init in window set the textures for the skybox
void Skybox::draw(Matrix4 c){
    float halfSize = size/2.0;
    glDisable(GL_LIGHTING);
    //material.apply();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    // Reset and transform the matrix.
   
    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);
    
    // Render the front quad
    front->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 1);
    glVertex3f(  halfSize, -halfSize, -halfSize );
    glTexCoord2f(1, 1);
    glVertex3f( -halfSize, -halfSize, -halfSize );
    glTexCoord2f(1, 0);
    glVertex3f( -halfSize,  halfSize, -halfSize );
    glTexCoord2f(0, 0);
    glVertex3f(  halfSize,  halfSize, -halfSize );
    glEnd();
    
    // Render the left quad
    left->bind();
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0, 1);
    glVertex3f(  halfSize, -halfSize,  halfSize );
    glTexCoord2f(1, 1);
    glVertex3f(  halfSize, -halfSize, -halfSize );
    glTexCoord2f(1, 0);
    glVertex3f(  halfSize,  halfSize, -halfSize );
    glTexCoord2f(0, 0);
    glVertex3f(  halfSize,  halfSize,  halfSize );
    glEnd();
    
    // Render the back quad
    back->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f( -halfSize, -halfSize,  halfSize );
    glTexCoord2f(1, 1);
    glVertex3f(  halfSize, -halfSize,  halfSize );
    glTexCoord2f(1, 0);
    glVertex3f(  halfSize,  halfSize,  halfSize );
    glTexCoord2f(0, 0);
    glVertex3f( -halfSize,  halfSize,  halfSize );
    
    glEnd();
    
    // Render the right quad
    right->bind();
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0, 1);
    glVertex3f( -halfSize, -halfSize, -halfSize );
    glTexCoord2f(1, 1);
    glVertex3f( -halfSize, -halfSize,  halfSize );
    glTexCoord2f(1, 0);
    glVertex3f( -halfSize,  halfSize,  halfSize );
    glTexCoord2f(0, 0);
    glVertex3f( -halfSize,  halfSize, -halfSize );
    glEnd();
    
    // Render the top quad
    top->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0, 0);
    glVertex3f( -halfSize,  halfSize, -halfSize );
    glTexCoord2f(0, 1);
    glVertex3f( -halfSize,  halfSize,  halfSize );
    glTexCoord2f(1, 1);
    glVertex3f(  halfSize,  halfSize,  halfSize );
    glTexCoord2f(1, 0);
    glVertex3f(  halfSize,  halfSize, -halfSize );
    glEnd();
    
    // Render the bottom quad
    bottom->bind();
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0, 1);
    glVertex3f( -halfSize, -halfSize, -halfSize );
    glTexCoord2f(0, 0);
    glVertex3f( -halfSize, -halfSize,  halfSize );
    glTexCoord2f(1, 0);
    glVertex3f(  halfSize, -halfSize,  halfSize );
    glTexCoord2f(1, 1);
    glVertex3f(  halfSize, -halfSize, -halfSize );
    glEnd();
    
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

void Skybox::update(){}

//void Skybox::idle(){}

//void Skybox::myDraw(DrawData& data){}

