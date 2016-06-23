#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Drawable.h"
#include "Vector3.h"
#include "Window.h"
#include "Geode.h"

class Sphere : public Geode
{
    
public:
    
    double radius;
    int slices, stacks;
    static Vector3 velocity;
    static float gravity;


    
    Sphere(double, int, int);
    
    virtual void draw(Matrix4);
    virtual void update();
    void runPhysics(float dt);
    //virtual void idle();
    
};

#endif
