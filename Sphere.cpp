#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks) : Geode()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    
    //velocity.identity();
}
float Sphere::gravity = 4.9;
Vector3 Sphere::velocity(.2,-.3,0);


void Sphere::draw(Matrix4 c)
{
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(c.ptr());
    
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(radius, slices, stacks);
    
    glPopMatrix();
}


void Sphere::update()
{
    //
}

/*void Sphere::runPhysics(float dt)
{//height1/depth = tan
    Matrix4 move;
    //if(velocity[1] > 0)
   // velocity[1] = velocity[1]-.1*gravity;
    
    move.makeTranslate(velocity[0], velocity[1], velocity[2]);
    c = c * move;
    if((c.get(3,1)-radius)>6.25 || (c.get(3,1)+radius)<-6.25){
        velocity[1] = -1 * velocity[1];
        
    }
    if((toWorld.get(3,0)-radius)>6.25 || (toWorld.get(3,0)+radius)<-6.25)
        velocity[0] = -1 * velocity[0];
    
    
}
*/
/*void Sphere::idle(){
    Sphere::runPhysics(toWorld.get(3,1));
}*/

