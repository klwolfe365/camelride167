//
//  Rasterizer.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Karen Wolfe on 4/14/15.
//  Copyright (c) 2015 RexWest. All rights reserved.
//

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Rasterizer.h"
#include "Globals.h"
#include <iostream>
#include <math.h>


static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* zbuf = new float[window_width*window_height];


float Rasterizer::lx = 0;
float Rasterizer::ux = 0;
float Rasterizer::ly = 0;
float Rasterizer::uy = 0;

float Rasterizer::alpha = 0.0;
float Rasterizer::beta = 0.0;
float Rasterizer::gamma = 0.0;

float Rasterizer::theta = M_PI/3;

Matrix4 *Rasterizer::d = new Matrix4((window_width*1.0)/2.0, 0.0, 0.0, 0.0,
                                     0.0, (window_height*1.0)/2.0, 0.0, 0.0,
                                     0.0, 0.0, .5, 0.0,
                                     (window_width*1.0)/2.0, (window_height*1.0)/2.0, .5, 1.0 );
Matrix4 *Rasterizer::p = new Matrix4(1.0/(((window_width*1.0)/window_height)*tan(Rasterizer::theta/2.0)), 0.0, 0.0, 0.0,
                                     0.0, 1.0/tan(Rasterizer::theta/2.0), 0.0, 0.0,
                                     0.0, 0.0, (1.0+1000.0)/(1.0-1000.0), -1.0,
                                     0.0, 0.0, 2.0*(1000.0)/(1.0-1000.0), 0.0);



using namespace std;

Rasterizer::Rasterizer(){
    //update_d();
    //update_p();
}
Rasterizer::~Rasterizer(){}


void loadData()
{
    // put code to load data model here
}

// Clear frame buffer
void Rasterizer::clearBuffer()
{
    
    Color clearColor = {0.0, 0.0, 0.0};   // clear color: black
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = clearColor[0];
        pixels[i*3+1] = clearColor[1];
        pixels[i*3+2] = clearColor[2];
    }
    for(int i = 0; i<window_width*window_height; i++)
        zbuf[i] = FLT_MAX;
}

// Draw a point into the frame buffer
Vector4 Rasterizer::rasterizeVertex(Vector4 vertex){
    vertex = (*p)*(Globals::camera.getInverseMatrix()*vertex);
    vertex = vertex.dehomogenize();
    vertex = (*d)*vertex;
    return vertex;
}

void Rasterizer::drawPoint(Vector4 vertex, Color c)
{
    int x = vertex[0];
    int y = vertex[1];
    if (x > window_width || x < 0 || y > window_height || y < 0 || vertex[2]>1 || vertex[2]<0)
        return;
    
    int offset = y*window_width*3 +x*3;
    pixels[offset]   = c[0];
    pixels[offset+1] = c[1];
    pixels[offset+2] = c[2];
    //std::cout << "wer iz mi vretxe? :'(" << std::endl;
    
}

void Rasterizer::computeBoundingBox(Vector4 v0, Vector4 v1, Vector4 v2)
{
    /*Rasterizer::ux = 0;
    Rasterizer::lx = 0;
    Rasterizer::uy = 0;
    Rasterizer::ly = 0;
    if(v0[2] > 0 || v1[2] > 0 || v2[2] > 0)
        return;
    */
   // Rasterizer::ux = max(v0[0], v1[0]);
    Rasterizer::ux = max(max(v0[0], v1[0]), v2[0]);
    if(Rasterizer::ux >= window_width)
        Rasterizer::ux = window_width;
    //Rasterizer::lx = min(v0[0], v1[0]);
    Rasterizer::lx = min(min(v0[0], v1[0]), v2[0]);
    if(Rasterizer::lx <= 0)
        Rasterizer::lx = 0;
    
   // Rasterizer::uy = max(v0[1], v1[1]);
    Rasterizer::uy = max(max(v0[1], v1[1]), v2[1]);
    if(Rasterizer::uy >= window_height)
        Rasterizer::uy = window_height;
    //Rasterizer::ly = min(v0[1], v1[1]);
    Rasterizer::ly = min(min(v0[1], v1[1]), v2[1]);
    if(Rasterizer::ly <= 0)
        Rasterizer::ly = 0;
    
    /*TODO*/
}

void Rasterizer::setBaryCoords(Vector4 p, Vector4 a, Vector4 b, Vector4 c){
    Vector3 p0 = p.toVector3();
    Vector3 pA = a.toVector3();
    Vector3 pB = b.toVector3();
    Vector3 pC = c.toVector3();
    //Vector3 temp((pA.scale(alpha)) + (pB.scale(beta)) + (pC.scale(gamma)));
    
    p0[2]=0;
    pA[2]=0;
    pB[2]=0;
    pC[2]=0;
    
    Vector3 na = (pC-pB).cross((p0-pB));
    Vector3 nb = (pA-pC).cross((p0-pC));
    Vector3 nc = (pB-pA).cross((p0-pA));
    Vector3 n0 = (pB-pA).cross((pC-pA));
    
    float denom = n0.magnitude()*n0.magnitude()*1.0;
    
    Rasterizer::alpha = (n0.dot(na))/denom;
    Rasterizer::beta = (n0.dot(nb))/denom;
    Rasterizer::gamma = (n0.dot(nc))/denom;

}

bool Rasterizer::zBuffer(int x, int y, Vector4 v0, Vector4 v1, Vector4 v2){
    Vector3 p0 = v0.toVector3();
    Vector3 p1 = v1.toVector3();
    Vector3 p2 = v2.toVector3();
    Vector3 temp = p0.scale(alpha) + p1.scale(beta) + p2.scale(gamma);
    Vector4 p = temp.toVector4(1);
    if(p[2]<0.0 || p2[2]>1.0)
        return false;
    
    if(p[2]<=zbuf[(y*window_width) + x]){
        zbuf[(y*window_width) + x] = p[2];
        return true;
    }
    return false;
}

Color Rasterizer::getColor(Vector3 na, Vector3 nb, Vector3 nc){
    na=na.normalize();
    nb=nb.normalize();
    nc=nc.normalize();
    Vector3 temp = na.scale(alpha) + nb.scale(beta) + nc.scale(gamma);
    
    return Color((temp[0]+1)/2.0, (temp[1]+1)/2.0, (temp[2]+1)/2.0);
}

//drawpoint after at the end
void Rasterizer::rasterizeTriangle(Vector4 v0, Vector4 v1, Vector4 v2, Vector3 na, Vector3 nb, Vector3 nc, Color c)
{
    //Vecterz
    v0 = Rasterizer::rasterizeVertex(v0);
    v1 = Rasterizer::rasterizeVertex(v1);
    v2 = Rasterizer::rasterizeVertex(v2);
    computeBoundingBox(v0, v1, v2);
    
    for(int x = Rasterizer::lx; x <= Rasterizer::ux; x++){
        for(int y = Rasterizer::ly; y <= Rasterizer::uy; y++){
            //Barycentric coordinates
            setBaryCoords(Vector4(x,y,0), v0, v1, v2);
            if(0<=Rasterizer::alpha && Rasterizer::alpha<=1 && 0<= Rasterizer::beta && Rasterizer::beta<=1 && 0<=Rasterizer::gamma && Rasterizer::gamma<=1){
                int offset = y*window_width*3 + x*3;
                if(Globals::part ==4)
                    c = getColor(na, nb, nc);
                if(Globals::part >= 3){
                    if(Rasterizer::zBuffer(x, y, v0, v1, v2)){
                        pixels[offset] = c[0];
                        pixels[offset+1] = c[1];
                        pixels[offset+2] = c[2];
                    }
                }
                else{
                    pixels[offset] = c[0];
                    pixels[offset+1] = c[1];
                    pixels[offset+2] = c[2];
                }
            }
        }
    }
}

void Rasterizer::rasterize()
{
    // Put your main rasterization loop here
    // It should go over the data model and call rasterizeTriangle for every triangle in it
    
    // example: draw diagonal line:
    //std::cout << "rsateirz" << std::endl;
    /*for (int i=0; i<min(window_width,window_height); ++i)
    {
        drawPoint(Vector4(1,1,1,1), Color(1.0, 0.0, 0.0));
    }*/

}

// Called whenever the window size changes
void Rasterizer::reshape(int new_width, int new_height)
{
    
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    delete[] zbuf;
    pixels = new float[window_width * window_height * 3];
    zbuf = new float[window_width * window_height];
    
    Rasterizer::update_d();
    Rasterizer::update_p();
}

void keyboard(unsigned char key, int, int)
{
    cerr << "Key pressed: " << key << endl;
}

void Rasterizer::display()
{
   // rasterize();
    //std::cout << "ar w eevn dspling?" << std::endl;
    
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
    
}

/*int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("CSE 167 Project 3");
    
    loadData();
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
}*/

void Rasterizer::update_p(){
    
     //float aspect = window_width/window_height;
    p->set(1.0/(((window_width*1.0)/window_height)*tan(Rasterizer::theta/2.0)), 0.0, 0.0, 0.0,
           0.0, 1.0/tan(Rasterizer::theta/2.0), 0.0, 0.0,
           0.0, 0.0, (1.0+1000.0)/(1.0-1000.0), -1.0,
           0.0, 0.0, 2.0*(1000.0)/(1.0-1000.0), 0.0);
}

void Rasterizer::update_d(){
    //correct setting for x1-x0(window_width) and y1-y0(window_height)
    d->set((window_width*1.0)/2.0, 0.0, 0.0, 0.0,
           0.0, (window_height*1.0)/2.0, 0.0, 0.0,
           0.0, 0.0, .5, 0.0,
           (window_width*1.0)/2.0, (window_height*1.0)/2.0, .5, 1.0);
}