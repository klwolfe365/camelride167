#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"
#include "Geode.h"
#include "Color.h"

struct Face
{
    //3 sets of indices to vertices and normals
    //vertices
    int vs[3];
    //normals
    int ns[3];
    //textCoords
    int ts[3];
};

class OBJObject : public Geode
{
    
protected:
    
    //Storage vectors
    std::vector<Vector3*>* vertices;
    std::vector<Vector3*>* normals;
    std::vector<Vector3*>* texcoords;
    std::vector<Vector3*>* rgbs;
    std::vector<Face>* faces;
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    
public:
    Color * obj_color;
    OBJObject(std::string);
    virtual ~OBJObject(void);
    
    virtual void draw(Matrix4 c);
    
    virtual void update();
    virtual void idle();
    
    virtual void myDraw(DrawData&);
   // void updateMaterial(Material m);
    
};

#endif
