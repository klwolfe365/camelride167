//
//  Group.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/7/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Group.h"
Group::Group() : Node(){}

Group::~Group(){}

void Group::addChild(Node* toAdd){
    nodes.push_back(toAdd);
}
void Group::removeChild(Node* toRemove){
    nodes.remove(toRemove);
}

void Group::draw(Matrix4 c){
    for(std::list<Node*>::iterator i = nodes.begin(); i!= nodes.end(); i++)
        (*i)->draw(c);
}
void Group::update(){
    for(std::list<Node*>::iterator i = nodes.begin(); i!= nodes.end(); i++)
        (*i)->update();
}

