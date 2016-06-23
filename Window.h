#ifndef CSE167_Window_h
#define CSE167_Window_h
#include "Vector3.h"
#include "MatrixTransform.h"
#include "Android.h"
#include "BezierCurve.h"
#include "BezierPatch.h"
#include "Terrain.h"

#ifdef __APPLE__

#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Window	  // OpenGL output window related routines
{
    
    static void testBezierCurve(BezierCurve b)
    {
        glMatrixMode(GL_MODELVIEW);
        
        glPushMatrix();
        glPointSize(2.0f);
        glEnable(GL_POINT_SPRITE);
        //glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_FALSE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        
        glBegin(GL_POINTS);
        // glBegin(GL_POINTS);
        for(float t = 0.0; t < 1.0; t += 0.01){
            glColor3f(1.0, 1.0, 1.0);
            glVertex3fv(b.getPoint(t).ptr());
        }
        glEnd();
        glDisable(GL_POINT_SPRITE);
        glPopMatrix();
    }
    
    static void testBezierPatch(BezierPatch b, Matrix4 toWorld)
    {
        float red, green, blue;
        red = 237.0 / 256.0;
        green = 201.0 / 256.0;
        blue = 175.0 / 256.0;
        
        glMatrixMode(GL_MODELVIEW);
        
        glPushMatrix();
        glMultMatrixf(toWorld.ptr());
        glPointSize(2.0f);
        glEnable(GL_POINT_SPRITE);
        //glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_FALSE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        
        glBegin(GL_POINTS);
        // glBegin(GL_POINTS);
        for(float u = 0.0; u <= 1.0; u += 0.005) {
            for(float v = 0.0; v <= 1.0; v += 0.005){
                glColor3f(red, green, blue);
                glVertex3fv(b.getPoint(u, v).ptr());
            }
        }
        glEnd();
        glDisable(GL_POINT_SPRITE);
        glPopMatrix();
    }
    
    static void testDesert(Matrix4 toWorld, Terrain* t)
    {
        t->draw(toWorld);
    }
    
public:
    
    static int width, height; // window size
    static Group root;
    static Group terr;
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processNormalKeys(unsigned char key, int x, int y);
    static void processFuncKeys(int key, int x, int y);
    static void processMouse(int button, int state, int x, int y);
    static void processMouseMovement(int x, int y);
    static void processPassiveMouse(int x, int y);
    
    static Vector3 trackballMapping(Vector3 point);
    static void setUpArmy();
    
    
};

#endif

