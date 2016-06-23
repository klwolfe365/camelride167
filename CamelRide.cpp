//
//  CamelRide.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Tim on 6/9/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "CamelRide.h"
#include "Globals.h"

CamelRide::CamelRide() : Geode()
{
    root = new Group();
    rootTrans = new MatrixTransform();
    
    camel = &Globals::camel;
    camelTrans = new MatrixTransform();
    
    desert = Globals::terrain_desert;
    desertTrans = new MatrixTransform();
    
    sandstorm = Globals::sandstorm;
    sandstormTrans = new MatrixTransform();
    
    
    rootTrans->addChild(camelTrans);
    rootTrans->addChild(desertTrans);
    rootTrans->addChild(sandstormTrans);
    
    camelTrans->addChild(camel);
    desertTrans->addChild(desert);
    sandstormTrans->addChild(sandstorm);
    
    camelTrans->trans = Matrix4().makeScale(.20)*Matrix4().makeRotateX(-M_PI_2)*Matrix4().makeRotateZ(-M_PI_4)*Matrix4().makeTranslate(-250.0, 300.0, -100.0)*Matrix4().setIdentity();
    
    camel = &Globals::camel;
    Globals::camel.obj_color = new Color(Color::camel());
    
    Globals::sandstorm->initSystem();
    Globals::sandstorm->genSystem();
    
    centerDesert();
    
    
}

void CamelRide::draw(Matrix4 c)
{
    rootTrans->draw(c);
    moveCamel();
}

void CamelRide::update()
{
    
}

void CamelRide::centerDesert()
{
    Vector3 center = desert->coords[desert->width/2/(int)PORTION][(int)desert->height/2/(int)PORTION];
    Matrix4 rotate, translate, scale;
    rotate.makeRotateX(180);
    translate.makeTranslate(center * (-1.0 / 4.0));
    scale.makeScale(1.5);
    desertTrans->trans = Matrix4(0.6679, 0.0148, -0.7373, 0.0000,
                                 -0.6818, 0.3915, -0.6098, 0.0000,
                                 0.2810, 0.9146, 0.2729, 0.0000,
                                 -4.3865, 180.1131, 22.3811, 1.0000) * scale * rotate * translate;
    
    //desertTrans->trans = scale * rotate * translate;
}

void CamelRide::moveCamel()
{
    if(path > 1.0)
    {
        path = 0;
        reversePath = true;
    }
    if(path < -1.0)
    {
        path = 0;
        reversePath = false;
    }
    camelTrans->trans = camelTrans->trans * Matrix4().makeTranslate(0.0, 0.0, path * 25.0);
    reversePath ? path -= 0.1 : path += 0.1;
}

void CamelRide::moveSandstorm(float x, float y, float z)
{
    sandstormTrans->trans = sandstormTrans->trans * Matrix4().makeTranslate(x, y, z);
}

void CamelRide::rotateSandstorm(Vector3 rot_axis, float angle)
{
    sandstormTrans->trans = Matrix4().makeRotateArbitrary(rot_axis, angle) * sandstormTrans->trans;
}
