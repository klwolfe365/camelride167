#include "House.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Globals.h"


House::House(){
    // This data structure defines a simple house
  
  
  
}

House::~House(){}

void House::draw(DrawData& data){
    // your vertex array needs to have this many entries
  //  int nVerts = 42;
    
    float vertices[] = {
            -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face 12
            -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
            4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
            4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
            4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
            -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face12*6
            
            -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
            -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
            4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
            -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
            4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall

        
        // These are the RGB colors corresponding to the vertices, in the same order
    float colors[] = {
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
            
            0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
            0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
            1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
            0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
            0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red
    
        // The index data stores the connectivity of the triangles;
        // index 0 refers to the first triangle defined above
    int indices[] = {
            0,2,3,    0,1,2,      // front face
            4,6,7,    4,5,6,      // left face
            8,10,11,  8,9,10,     // back face
            12,14,15, 12,13,14,   // right face
            16,18,19, 16,17,18,   // top face
            20,22,23, 20,21,22,   // bottom face
            
            24,26,27, 24,25,26,   // grass
            28,29,30,             // front attic wall
            31,33,34, 31,32,33,   // left slope
            35,37,38, 35,36,37,   // right slope
            39,40,41};            // rear attic wall
    
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());

    //MAKE THE HOUSE
    glBegin(GL_TRIANGLES);
    
    int len = 20*3;
    int index = -1;
    
    for(int i = 0; i < len; i++){
        index = 3*indices[i];
        
        glColor3f(colors[index], colors[index+1], colors[index+2]);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(vertices[index], vertices[index+1], vertices[index+2]);
    }
    
    glEnd();
    
    glPopMatrix();
}
void House::update(UpdateData& data){}
void House::idle(){}



void House::myDraw(DrawData& data){
    float vertices[] = {
        -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face 12
        -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
        4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
        4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
        4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
        -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face12*6
        
        -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
        -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
        4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
        -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
        4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall
    
    
    // These are the RGB colors corresponding to the vertices, in the same order
    float colors[] = {
        1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
        0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
        1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
        0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
        0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
        0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
        
        0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
        0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
        1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
        0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
        0,0,1, 0,0,1, 0,0,1};              // rear attic wall is red
    
    // The index data stores the connectivity of the triangles;
    // index 0 refers to the first triangle defined above
    int indices[] = {
        0,2,3,    0,1,2,      // front face
        4,6,7,    4,5,6,      // left face
        8,10,11,  8,9,10,     // back face
        12,14,15, 12,13,14,   // right face
        16,18,19, 16,17,18,   // top face
        20,22,23, 20,21,22,   // bottom face
        
        24,26,27, 24,25,26,   // grass
        28,29,30,             // front attic wall
        31,33,34, 31,32,33,   // left slope
        35,37,38, 35,36,37,   // right slope
        39,40,41};  // rear attic wall
    
    
    int index = -1;
    if(Globals::part == 1){
        for(int i = 0; i < 60; i++){
            index = 3*indices[i];
            Vector4 vertex(vertices[index], vertices[index+1], vertices[index+2], 1);
            vertex = toWorld*vertex;
            Color c(1,1,1);
        
            //if(Globals::part==1){
            vertex = Globals::rasterizer.rasterizeVertex(vertex);
           
            Globals::rasterizer.drawPoint(vertex, c);
            //}
        }
    }
        
    if(Globals::part>=2){
        for(int i = 0; i < 60; i+=3){
            index = indices[i];
            Vector4 v0(vertices[3*index], vertices[3*index+1], vertices[3*index+2], 1);
            v0 = toWorld*v0;
            Color c(colors[3*index], colors[3*index+1], colors[3*index+2]);
            //Color c = Color::randomBrightPastel();
            index = indices[i+1];
            Vector4 v1(vertices[3*index], vertices[3*index+1], vertices[3*index+2], 1);
            v1 = toWorld * v1;
            index = indices[i+2];
            Vector4 v2(vertices[3*index], vertices[3*index+1], vertices[3*index+2], 1);
            v2 = toWorld*v2;
            //How I are rasterize TRYangles :'(
            Globals::rasterizer.rasterizeTriangle(v0, v1, v2, v0.toVector3(), v1.toVector3(), v2.toVector3(), c);
    }
}


}


