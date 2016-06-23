//
//  ParticleSystem.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 6/2/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#include "ParticleSystem.h"
#include "Globals.h"
#include "Window.h"


/**
 * Height = Z * tan(fov/2) -----> fov = 60.0; z =1
 * width = height * aspect_ratio -------> aspect_ratio = width/height
 **/
Vector3 ParticleSystem::accel = Vector3(0, GRAVITY, 0);
int ParticleSystem::view_w = Window::width * ((double)Window::width/(double)Window::height);
int ParticleSystem::view_h = tan(60.0/2);
ParticleSystem::ParticleSystem() : Geode(){
    g = std::default_random_engine();
    x_distrib = std::normal_distribution<double>(-Window::width/8, Window::width/8);
    y_distrib = std::normal_distribution<double>(-Window::height/8, Window::height/8);
    
    this->initSystem();
}
ParticleSystem::ParticleSystem(Vector3 pos, float life){}
ParticleSystem::~ParticleSystem(){}

void ParticleSystem::initSystem(){
    std::normal_distribution<double> c(0.75,1.0);
    std::default_random_engine cg = std::default_random_engine();
    double shade;
    for(int p = 0; p < MAX_PARTICLE_NUM; p++){
        shade = c(cg);
        Particles[p].position = new Vector3(0.0f, 0.0f, 1.0f);
        Particles[p].velocity = new Vector3(Globals::wind_speed, -5.0f, 0.0f);
        Particles[p].color = Color(Color::lightBrown()).makeShade(shade);
        Particles[p].a = 1.0f;
        Particles[p].lifetime = MAX_PARTICLE_LIFETIME;
        Particles[p].age = 0;
        Particles[p].size = 3.0f;
        Particles[p].alive = false;
    }
}

void ParticleSystem::genSystem(){
    for(int p = 0; p < MAX_PARTICLE_NUM; p++){
        if(!Particles[p].alive){
            randomize_particle(Particles[p]);
            

            Particles[p].alive = true;
           // return;
        }
    }
}

void ParticleSystem::randomize_particle(Particle p){
    p.age = 0.0f;
    p.position->set(x_distrib(g),  y_distrib(g), 10.0);
    //int r = rand() % 10 + 20;
    
    //std::cout << "y: " << y << std::endl;
    //p.velocity->set(0.0, -5.0,  0.0);
    
    

}

void ParticleSystem::draw(Matrix4 c){
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(c.ptr());
    glPointSize(2.0f);
    sand_text->bind();
    glEnable(GL_POINT_SPRITE);
    //glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_FALSE);
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    
    glBegin(GL_POINTS);
   // glBegin(GL_POINTS);
    for(int p = 0; p < MAX_PARTICLE_NUM; p++){
        if(Particles[p].alive && (Particles[p].velocity->get(0) != 0)){
           
            //glColor3fv(Color::randomBrightPastel().ptr());
            glColor3fv(Particles[p].color.ptr());
            glVertex3fv(Particles[p].position->ptr());
            //glutSolidSphere(1.0,20,20);
        }    }
    glEnd();
    glDisable(GL_POINT_SPRITE);
    sand_text->unbind();
    glPopMatrix();

}

void ParticleSystem::update(){
    for(int p = 0; p < MAX_PARTICLE_NUM; p++){
        if(Particles[p].age < 0)
            continue;
        if((Particles[p].age > Particles[p].lifetime) || !(Particles[p].alive)){
            randomize_particle(Particles[p]);
            Particles[p].alive = true;
        }
        Particles[p].age++;
        
        Vector3 vel = accel * Globals::updateData.dt + *Particles[p].velocity;
        Vector3 pos = vel * Globals::updateData.dt + *Particles[p].position;
        Particles[p].velocity->set(Globals::wind_speed, vel[1], vel[2]);
        Particles[p].position->set(pos[0], pos[1], pos[2]);
    
        if(pos[0] > Window::width/8 || pos[0] < -Window::width/8 ||
           pos[1] > Window::height/8 || pos[1] < -Window::height/8)
            Particles[p].alive = false;
        
//        if(p == 0){
//            Particles[p].velocity->print("v");
//            Particles[p].position->print("p");
//        }
    }
}

void ParticleSystem::idle(){}

GLfloat ParticleSystem::randomVelocity(){
    int dir = rand() % 2 ? 1 : -1;
    float mag = ((float)rand() / RAND_MAX) * 0.5;
    return mag * dir;
}

int ParticleSystem::find_unused_particle(){
    for(int i = prev_particle; i < max_particles; i++){
        if(Particles[i].age < 0){
            prev_particle = i;
            return i;
        }
    }
    for(int i = 0; i < prev_particle; i++){
        if(Particles[i].age < 0){
            prev_particle = i;
            return i;
        }
    }
    /* All particles used, reset to beginning */
    return 0;
}

void ParticleSystem::myDraw(DrawData& data){}

