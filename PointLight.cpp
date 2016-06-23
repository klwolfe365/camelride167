//
//  PointLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "PointLight.h"

PointLight::PointLight() : Light() {
    diffuseColor = Color(1.0,1.0,1.0);
    //ambientColor = Color(.2,.2,.2);
    //ambientColor = diffuseColor;
    //specularColor = diffuseColor;
    position = Vector4(1024.0/2.0,100.0,150.0,1.0);

}

PointLight::~PointLight(){}

void PointLight::draw(Matrix4 c){
   /* glPushMatrix();
    glLoadIdentity();*/
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(c.ptr());
    glColor3f(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
    
    //glTranslated(position[0], position[1], position[2]);
    glutSolidSphere(25.0, 20, 20);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}
void PointLight::update(){
    x +=delta;
    z -= delta;
    if(x > 1024 || x < 0)
        delta = -1 *delta;
    y = a*(x-h)*(x-h)+k;
    position = Vector4(x, y, z, 1.0);
    //position = Vector4(x, y, z, 1.0);
    float y_fact = 1.0-((y)/(h));
    if(y_fact > 1)
        y_fact = 1;
    float w_fact = (y)/(h);
    if(w_fact > 1)
        w_fact = 1;
    Vector3 c = white.scale(w_fact) + yellow.scale(y_fact);
    diffuseColor = Color(c[0],c[1],c[2]);
}

void PointLight::idle(){}

void PointLight::myDraw(DrawData&){}
