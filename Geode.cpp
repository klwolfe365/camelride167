//
//  Geode.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Geode.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Geode::Geode() : Node(){}
Geode::~Geode(){}

void Geode::draw(Matrix4 c){
    center = c.getTransVector();
    this->draw(c);
}

void Geode::update(){
    this->update();
}
