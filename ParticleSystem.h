//
//  ParticleSystem.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 6/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef __CSE167_Spring_2015_Starter_Code__ParticleSystem__
#define __CSE167_Spring_2015_Starter_Code__ParticleSystem__

#include <stdio.h>
#include <vector>
#include <ctime>
#include <random>
#include "Vector3.h"
#include "Matrix4.h"
#include "Color.h"
#include "Geode.h"
#include "Texture.h"



#define MAX_PARTICLE_NUM 100000
#define MAX_PARTICLE_LIFETIME 10000
#define GRAVITY -9.8f

class ParticleSystem : public Geode {
public:
    std::default_random_engine g;
    std::normal_distribution<double> x_distrib;
    std::normal_distribution<double> y_distrib;
    static int view_w;
    static int view_h;
    
    static Vector3 accel;
    Texture * sand_text;
    const static int max_particles = 100000;
    int prev_particle = 0;
    struct Particle{
        Vector3 * position;
        Vector3 * velocity;
        Color color;
        float a;
        float lifetime, age, size, weight;
        bool alive;
    };
    Particle Particles[max_particles];
    
    ParticleSystem();
    ParticleSystem(Vector3 pos, float life);
    ~ParticleSystem();
    
    void initSystem();
    void genSystem();
    void randomize_particle(Particle p);
    
    virtual void draw(Matrix4 c);
    virtual void update();
    virtual void idle();
    
    GLfloat randomVelocity();
    //void collisionCheck();
    int find_unused_particle();
    
    virtual void myDraw(DrawData&);

};

#endif /* defined(__CSE167_Spring_2015_Starter_Code__ParticleSystem__) */
