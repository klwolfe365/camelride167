//
//  Android.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 5/11/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "Android.h"
#include "Node.h"

Android::Android() : Geode(){
    root = new Group;
    /** Android body parts **/
    head = new Cylinder(2.5, 1.0);
    torso = new Cylinder(4.0, 2.0);
    
    
    Sphere* armJoint = new Sphere(0.5, 15, 15);
    arm = new Cylinder(3.0, 0.5);
    arm->Cylinder::setTextures(headS, headT, headB);
    Sphere* legJoint = new Sphere(.5, 15, 15);
    leg = new Cylinder(3.0, 0.5);
    leg->Cylinder::setTextures(headS, headT, headB);

    /*Head positioning*/
    Matrix4 headMatrix = Matrix4().makeTranslate(0.0, 4.0, 0);
    Matrix4 bRot = Matrix4().makeRotateY(M_PI);
    MatrixTransform * rot = new MatrixTransform(bRot);
    MatrixTransform * headTrans = new MatrixTransform(headMatrix);
    
    /*Arm positioning*/
    Matrix4 lArmJointPos = Matrix4().makeTranslate(-2.5, 3.5, 0.0);
    MatrixTransform* laj = new MatrixTransform(lArmJointPos);
    
    Matrix4 rArmJointPos = Matrix4().makeTranslate(2.5, 3.5, 0.0);
    MatrixTransform* raj = new MatrixTransform(rArmJointPos);
    
    Matrix4 armTM = Matrix4().makeTranslate(0, -3.00, 0);
    MatrixTransform * armTrans = new MatrixTransform(armTM);
    armTrans->addChild(arm);
    laj->addChild(armTrans);
    laj->addChild(armJoint);
    raj->addChild(armTrans);
    raj->addChild(armJoint);
    Matrix4 swingAL = Matrix4().makeRotateX(rotAngleA);
    armSwingL = new MatrixTransform(swingAL);
    Matrix4 swingAR = Matrix4().makeRotateX(-rotAngleA);
    armSwingR = new MatrixTransform(swingAR);
    armSwingL->addChild(laj);
    armSwingR->addChild(raj);
    armMovement->addChild(armSwingL);
    armMovement->addChild(armSwingR);
    root->addChild(armMovement);
    
    Matrix4 lLegJointPos = Matrix4().makeTranslate(-1.5, -0.45, 0);
    MatrixTransform* llj = new MatrixTransform(lLegJointPos);
    Matrix4 rLegJointPos = Matrix4().makeTranslate( 1.5, -0.45, 0);
    MatrixTransform* rlj = new MatrixTransform(rLegJointPos);
    Matrix4 legPosMatrix = Matrix4().makeTranslate(0, -3.0, 0);
    MatrixTransform* legTrans = new MatrixTransform(legPosMatrix);
    legTrans->addChild(leg);
    llj->addChild(legTrans);
    llj->addChild(legJoint);
    rlj->addChild(legTrans);
    rlj->addChild(legJoint);
    Matrix4 swingLL = Matrix4().makeRotateX(rotAngleL);
    Matrix4 swingLR = Matrix4().makeRotateX(-rotAngleL);
    legSwingL = new MatrixTransform(swingLL);
    legSwingR = new MatrixTransform(swingLR);
    legSwingL->addChild(llj);
    legSwingR->addChild(rlj);
    legMovement->addChild(legSwingL);
    legMovement->addChild(legSwingR);
    root->addChild(legMovement);
    
    /*****************************************************************
     General Schematic for body part attachment:
     
     Limb position Matrix       - translation matrix
        --> MatrixTransform
        --> attach/addChild     - limb (cylinder)
     Joint position Matrix      - translation matrix
        --> MatrixTransform
        -->attach/addChild      - limb MatrixTransform
        -->attach/addChild      - joint (sphere)
     Rotation matrix            - makeRotateX
        --> MatrixTransform     - limb swing
        --> attach/addChild     - joint MatrixTransform
     root->addChild             - limbSwing
    
     limb       - cylinder
     translate  - translation matrix relative to joint
                    -jointPos.addChild(armTranslation) --laj
     joint      - sphere
     rotate     - armSwing(swing)
                    -armMovement.addChild(armSwing)
     translate  - armMovement(armTrans)
                    root.addChild(armMovement)
     body       - root
     *****************************************************************/

    
       /* Head Setup */
    headTrans->addChild(head);
    rot->addChild(headTrans);

    root->addChild(rot);
    root->addChild(torso);
    

}

Android::~Android(){}

void Android::draw(Matrix4 c){
    root->draw(c);
}

void Android::update(){
    root->removeChild(armMovement);
    armMovement->removeChild(armSwingL);
    armMovement->removeChild(armSwingR);
    Matrix4 swingAL = (((Matrix4().makeTranslate(0.0, 3.5, 0.0))))*((Matrix4().makeRotateX(rotAngleA))*(Matrix4().makeTranslate(0.0, -3.5, 0.0)));
    Matrix4 swingAR = (((Matrix4().makeTranslate(0.0, 3.5, 0.0))))*((Matrix4().makeRotateX(-rotAngleA))*(Matrix4().makeTranslate(0.0, -3.5, 0.0)));
    armSwingL->trans = swingAL;
    armSwingR->trans = swingAR;
    armMovement->addChild(armSwingL);
    armMovement->addChild(armSwingR);
    root->addChild(armMovement);
    
    root->removeChild(legMovement);
    legMovement->removeChild(legSwingL);
    legMovement->removeChild(legSwingR);
    Matrix4 swingLL = (((Matrix4().makeTranslate(0.0, -.45, 0.0))))*((Matrix4().makeRotateX(rotAngleL))*(Matrix4().makeTranslate(0.0, .45, 0.0)));
    Matrix4 swingLR = (((Matrix4().makeTranslate(0.0, -.45, 0.0))))*((Matrix4().makeRotateX(-rotAngleL))*(Matrix4().makeTranslate(0.0, .45, 0.0)));
    legSwingL->trans = swingLL;
    legSwingR->trans = swingLR;
    legMovement->addChild(legSwingL);
    legMovement->addChild(legSwingR);
    root->addChild(legMovement);

    
    if(rotAngleA >= M_PI_2/2 || rotAngleA <= -1*M_PI_2/2){
        deltaA = -1 * deltaA;
    }
    if(rotAngleL >= M_PI_2/4 || rotAngleL <= -1*M_PI_2/4){
        deltaL = -1 * deltaL;
    }
    rotAngleA += deltaA;
    rotAngleL += deltaL;
}

void Android::setTextures(std::vector<Texture*> t){
    Texture * h = t.front();
    t.erase(t.begin());
    Texture * topT = t.front();
    t.erase(t.begin());
    Texture * bot = t.front();
    t.erase(t.begin());
    head->setTextures(h, topT, bot);
    
    h = t.front();
    torso->setTextures(h, h, h);
    arm->setTextures(h, h, h);
    leg->setTextures(h, h, h);
}
