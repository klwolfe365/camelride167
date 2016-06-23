#include "OBJObject.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include "Globals.h"
#include "Shader.h"
#include "Color.h"
#include <sstream>
#include <fstream>

#define deleteVector(__vect__) do {\
iter = __vect__->begin();\
end = __vect__->end();\
while(iter != end) delete (*(iter++));\
delete __vect__;\
} while(false)

//Vector3 OBJObject::

OBJObject::OBJObject(std::string filename) : Geode()
{
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->texcoords = new std::vector<Vector3*>();
    this->rgbs = new std::vector<Vector3*>();
    this->faces = new std::vector<Face>();
    this->obj_color = new Color(Color::white());
    
    parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    std::vector<Vector3*>::iterator iter;
    std::vector<Vector3*>::iterator end;
    
    deleteVector(vertices);
    deleteVector(rgbs);
    deleteVector(normals);
    deleteVector(texcoords);
    
    delete faces;
}

void OBJObject::draw(Matrix4 c)
{
    //material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(c.ptr());
    Color color = Color(*obj_color);
    
    Globals::shader->bind();
    GLint bandLoc = glGetUniformLocationARB(Globals::shader->getPid(), "lightDir");
    glUniform3f(bandLoc, Shader::lightDir[0], Shader::lightDir[1], Shader::lightDir[2]);
    GLint colLoc = glGetUniformLocationARB(Globals::shader->getPid(), "color");
    glUniform4f(colLoc, color[0], color[1], color[2], 1);

    
    
    glBegin(GL_TRIANGLES);
    //Loop through the faces
    for(int f = 0; f < faces->size(); f++){
        Face face = faces->at(f);
        //For each face:
        //  Draw them as triplets:
        for(int i = 0; i < 3; i++){
            //  Look up the vertices, normals (if they exists), and texcoords (if they exist)
            Vector3* vertex = vertices->at(face.vs[i]);
           // Vector3* color = rgbs->at(face.vs[i]);
            Vector3* norm = normals->at(face.ns[i]);
                        //glColor3f(color->get(0), color->get(1), color->get(2));
            glNormal3f(norm->get(0), norm->get(1), norm->get(2));
            glVertex3f(vertex->get(0), vertex->get(1), vertex->get(2));            
        }
    //      glTex(texcoords->at(face.ts[0]))
    //      glNorm(normals->at(face.ns[0]))
    //      glVert(vertices->at(face.vs[0]))
    //      Etc.
    //
    }
    
    
    glEnd();
    Globals::shader->unbind();

    
    glPopMatrix();
}

void OBJObject::update()
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    std::vector<std::string> faceTokens;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 50000 == 0)
            std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);

        if(tokens.size() == 0) {
            continue;
        }
        //std::cout << token << std::endl;
        //If first token is a v then it has to be a vertex
        if((tokens.at(0).compare("\n") == 0) || tokens.at(0).compare("#") == 0){
            continue;
        }
        else if(tokens.at(0).compare("v") == 0)
        {
            //std::cout << "v" << std::endl;


            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            vertices->push_back(new Vector3(x, y, z));

            //std::cout << x << '\t' << y << '\t' << z << std::endl;
            //RGB values of vertex
            float r = .95;
            float g = .95;
            float b = .95;
            if(tokens.size()>3*sizeof(int)){
                r = std::stof(tokens.at(4));
                g = std::stof(tokens.at(5));
                b = std::stof(tokens.at(6));
            }
            
            rgbs->push_back(new Vector3(r, g, b));
            
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
           // std::cout << "vn" << std::endl;

            //Parse the normal line
            float xn = std::stof(tokens.at(1));
            float yn = std::stof(tokens.at(2));
            float zn = std::stof(tokens.at(3));
            Vector3* n = new Vector3(xn, yn, zn);
            *n = n->normalize();
            normals->push_back(n);
            //std::cout << normals->size() << std::endl;

            //std::cout << n->get(0) << '\t' << n->get(1) << '\t' << n->get(2) << std::endl;
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face face;
            //std::cout << "face" << std::endl;
            
            //Parse the face line
            for(int i = 1; i < 4; i++){
                faceTokens.clear();
                faceTokens = split(tokens.at(i), '/', faceTokens);
                face.vs[i-1] = std::stof(faceTokens.at(0))-1;
                face.ns[i-1] = std::stof(faceTokens.at(2))-1;
                //face.ts[i-1] = std::stof(faceTokens.at());
                //std::cout << face.vs[i-1] << '\t' << face.ns[i-1] << '\t' << face.ts[i-1] << std::endl;
            }
            
            faces->push_back(face);

        }
        else if(tokens.at(0).compare("how does I are c++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
        
    }
    
    std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void OBJObject::idle(){}

void OBJObject::myDraw(DrawData& data)
{
    /* material.apply();
     
     glMatrixMode(GL_MODELVIEW);
     
     glPushMatrix();
     glMultMatrixf(toWorld.ptr());
     
     glBegin(GL_TRIANGLES);
     //Loop through the faces
     for(int f = 0; f < faces->size(); f++){
     Face face = faces->at(f);
     //For each face:
     //  Draw them as triplets:
     for(int i = 0; i < 3; i++){
     //  Look up the vertices, normals (if they exists), and texcoords (if they exist)
     Vector3* vertex = vertices->at(face.vs[i]);
     Vector3* color = rgbs->at(face.vs[i]);
     Vector3* norm = normals->at(face.ns[i]);
     
     glColor3f(color->get(0), color->get(1), color->get(2));
     glNormal3f(norm->get(0), norm->get(1), norm->get(2));
     glVertex3f(vertex->get(0), vertex->get(1), vertex->get(2));
     }
*/
    Color color;
    for(int f = 0; f < faces->size(); f++){
        if((f%120) == 0)
            color = Color::randomBrightPastel();
        Face face = faces->at(f);
        //For each face:
        //  Draw them as triplets:
        if(Globals::part==1){
            for(int i = 0; i < 3; i++){
            //  Look up the vertices, normals (if they exists), and texcoords (if they exist)
                Vector3* v = vertices->at(face.vs[i]);
                Vector4 vertex(v->get(0), v->get(1), v->get(2), 1);
            //Vector4 vertex= v->toVector4(1);
           // Color color(1.0,1.0,1.0);
           // Vector3* norm = normals->at(face.ns[i]);
                //vertex = toWorld*vertex;
            
                vertex = Globals::rasterizer.rasterizeVertex(vertex);
                Globals::rasterizer.drawPoint(vertex, Color(1,1,1));
            }
        }
        else if(Globals::part>=2){
            Vector3* v = vertices->at(face.vs[0]);
            Vector3* v1 = vertices->at(face.vs[1]);
            Vector3* v2 = vertices->at(face.vs[2]);
            
            Vector4 vertex0(v->get(0), v->get(1), v->get(2), 1);
            Vector4 vertex1(v1->get(0), v1->get(1), v1->get(2), 1);
            Vector4 vertex2(v2->get(0), v2->get(1), v2->get(2), 1);
            
           /* vertex0 = toWorld*vertex0;
            vertex1 = toWorld*vertex1;
            vertex2 = toWorld*vertex2;*/
            
                
            Globals::rasterizer.rasterizeTriangle(vertex0, vertex1, vertex2, *(normals->at(face.ns[0])), *(normals->at(face.ns[1])), *(normals->at(face.ns[2])), color);
        }
        
    }

}


