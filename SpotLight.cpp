//
//  SpotLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/1/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "SpotLight.h"

SpotLight::SpotLight() : Light() {
    diffuseColor = Color(0.0,0.8,0.8);
    //ambientColor = Color(.2,.2,.2);
    //specularColor = diffuseColor;
    position = Vector4(0.0,0.0,1.0,1.0);
    direction = Vector4(0.0,0.0,-1.0,1.0);
    
    angle = 25.0;
    cosine_exp = 1.0;
    //calculate specular reflectance
    //specularColor = Color(1.0,1.0,1.0);
    
    
}

SpotLight::~SpotLight(){}

void SpotLight::draw(DrawData&){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
   // glMultMatrixf(toWorld.ptr());
    glColor3f(0.0,0.8,0.8);
    glutSolidCone(1.0 * angle/100, 3.0, 20, 20);
    glPopMatrix();
    
}
void SpotLight::update(UpdateData&){}
void SpotLight::idle(){}

void SpotLight::myDraw(DrawData&){}