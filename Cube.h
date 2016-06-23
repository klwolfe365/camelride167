#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
#include "Geode.h"

class Cube : public Geode
{
    
public:
    
    float size;
    static float spinAmt;
    
    Cube(float);
    virtual ~Cube(void);
    
    virtual void draw(DrawData&);
    //virtual void update(UpdateData&);
    virtual void update();
    
    void spin(float);
    virtual void idle();
    
    void makeFace(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3, Color color);
    virtual void myDraw(DrawData&);
    
};

#endif

