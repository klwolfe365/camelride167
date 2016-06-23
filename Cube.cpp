#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Vector4.h"
#include "Globals.h"



Cube::Cube(float size) : Geode()
{
    this->size = size;
}


Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}

float Cube::spinAmt = .0025;

void Cube::draw(DrawData& data)
{
    float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with these material
   // updateMaterial(Material(Color(0.0,1.0,0.0), Color::diffuseDefault(), Color::specularDefault(), Color::emissionMaterialDefault(), Color(0,1.0,0), 100));
   // material.apply();
    
    //Se the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(data.c.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    glBegin(GL_QUADS);

    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
    
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    //glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}


void Cube::update()
{
    //
}

void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    
    //toWorld = toWorld * rotation;
}

void Cube::idle(){
    spin(spinAmt);
}

void Cube::makeFace(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3, Color color){
    //v0 = toWorld*v0;
    //v1 = toWorld*v1;
   // v2 = toWorld*v2;
   // v3 = toWorld*v3;

    //Color c1 = Color::randomPastel();
   // Globals::rasterizer.rasterizeTriangle(v0, v1, v2, v0.toVector3(), v1.toVector3(), v2.toVector3(), color);
    //Globals::rasterizer.rasterizeTriangle(v0, v3, v2, v0.toVector3(), v3.toVector3(), v2.toVector3(), Color(.5*color[0], .5*color[1], .5*color[2]));
}

void Cube::myDraw(DrawData &data){
    
    float halfSize = size/2.0;
    if(Globals::part == 1){
        Vector4 vertex(-halfSize,  halfSize,  halfSize);
        //vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
    
        vertex.set(halfSize,  halfSize,  halfSize, 1);
        //vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
        
        vertex.set(halfSize, -halfSize,  halfSize, 1);
       // vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        //Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
        
        vertex.set(-halfSize, -halfSize,  halfSize, 1);
        //vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        //Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
    
        vertex.set(-halfSize,  halfSize, -halfSize, 1);
        //vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        //Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
        
        vertex.set(-halfSize, -halfSize, -halfSize, 1);
        //vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        //Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
    
    
        vertex.set(halfSize,  halfSize, -halfSize, 1);
        //vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
    
        vertex.set(halfSize, -halfSize, -halfSize, 1);
       // vertex = Globals::rasterizer.rasterizeVertex(toWorld*vertex);
        Globals::rasterizer.drawPoint(vertex, Color(1.0, 1.0, 1.0));
        
    }
    if(Globals::part >= 2){
    
        /*Front face*/
        Vector4 v0(-halfSize,  halfSize,  halfSize, 1);
        Vector4 v1(halfSize,  halfSize,  halfSize, 1);
        Vector4 v2(halfSize, -halfSize,  halfSize, 1);
        Vector4 v3(-halfSize, -halfSize,  halfSize, 1);
        makeFace(v0, v1, v2, v3, Color(.8, 0.0, .5));
        
        /*Left Face*/
        v0.set(-halfSize,  halfSize,   halfSize, 1);
        v1.set(-halfSize,  halfSize,  -halfSize, 1);
        v2.set(-halfSize, -halfSize,  -halfSize, 1);
        v3.set(-halfSize, -halfSize,   halfSize, 1);
        makeFace(v0, v1, v2, v3, Color(0, .5, .8));
        
        /*Right Face*/
        v0.set(halfSize,  halfSize,   halfSize, 1);
        v1.set(halfSize,  halfSize,  -halfSize, 1);
        v2.set(halfSize, -halfSize,  -halfSize, 1);
        v3.set(halfSize, -halfSize,   halfSize, 1);
        makeFace(v0, v1, v2, v3, Color(1.0, 0, 1.0));
        
        /*Back Face*/
        v0.set(-halfSize,  halfSize,  -halfSize, 1);
        v1.set(halfSize,   halfSize,  -halfSize, 1);
        v2.set(halfSize,  -halfSize,  -halfSize, 1);
        v3.set(-halfSize, -halfSize,  -halfSize, 1);
        makeFace(v0, v1, v2, v3, Color(0.0, 1.0, 1.0));
        
        /*Top Face*/
        v0.set(-halfSize, halfSize,   halfSize, 1);
        v1.set(halfSize,  halfSize,   halfSize, 1);
        v2.set(halfSize,  halfSize,  -halfSize, 1);
        v3.set(-halfSize, halfSize,  -halfSize, 1);
        makeFace(v0, v1, v2, v3, Color(.5, .9, 0));
        
        /*Bottom Face*/
        v0.set(-halfSize, -halfSize,  -halfSize, 1);
        v1.set(halfSize,  -halfSize,  -halfSize, 1);
        v2.set(halfSize,  -halfSize,   halfSize, 1);
        v3.set(-halfSize, -halfSize,   halfSize, 1);
        makeFace(v0, v1, v2, v3, Color(.9, .5, 0));

    
    }
    

    
    
}





