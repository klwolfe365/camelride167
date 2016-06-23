//
//  DirectionalLight.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/30/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light() {
    diffuseColor = Color(2.0,2.0,2.0);
    //specularColor = Color(1.0,1.0,1.0);
    //bindID = 1;
    position = Vector4(1.0,1.0,1.0,0);
}

//method that when 1 pressed, display light --> extend drawable
    //display: glEnable
DirectionalLight::~DirectionalLight(){
    
    
}


void DirectionalLight::draw(Matrix4 c){
      
}
void DirectionalLight::update(){}
void DirectionalLight::idle(){}

void DirectionalLight::myDraw(DrawData&){}
































/*
 GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat mat_shininess[] = { 50.0 };
 GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
 glClearColor (0.0, 0.0, 0.0, 0.0);
 */

/*void DirectionalLight::draw(DrawData&){
    Vector4 specular(1.0,1.0,1.0,1.0);
    Vector4 position(1.0,1.0,1.0,0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);


}




void DirectionalLight::update(UpdateData&){}
void DirectionalLight::idle(){}
void DirectionalLight::myDraw(DrawData&){}*/