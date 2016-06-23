#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Light::Light() : Node()
{
    ambientColor = Color::ambientDefault();
    diffuseColor = Color::diffuseDefault();
    specularColor = Color::specularDefault();
    
    constantAttenuation = 1.0;
    linearAttenuation = 0.0;
    quadraticAttenuation = 0.00;
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id, Matrix4 c)
{
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the bindID
    bindID = id;
    glPushMatrix();
    glMultMatrixf(c.ptr());

    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor.ptr());
    
    //Configure the attenuation properties of the light
    //Constant Attenuation
    //Linear Attenuation
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
       //Position the light
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());
    //Setup spotlight direction, angle, and exponent here
    if(bindID == 3){
        direction.set(-1*position.get(0),-1*position.get(1), -1*position.get(2), position.get(3));
        glLightf(GL_LIGHT0 + bindID, GL_SPOT_CUTOFF, angle);
        glLightf(GL_LIGHT0 + bindID, GL_SPOT_EXPONENT, cosine_exp);
        glLightfv(GL_LIGHT0 + bindID, GL_SPOT_DIRECTION, direction.ptr());

    }
    glPopMatrix();
    glFlush();
  //  glPopMatrix();
}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}

void Light::draw(Matrix4 c){}
void Light::update(){}
void Light::idle(){}

void Light::myDraw(DrawData&){}
