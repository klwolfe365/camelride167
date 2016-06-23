#ifndef CSE167_Light_h
#define CSE167_Light_h

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include "Drawable.h"
#include "Node.h"
#include <vector>

class Light : public Node
{
    
protected:
    
    int bindID = -1;
    
public:
    
    Vector4 position;
    Vector4 direction;
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    
    float angle;
    float cosine_exp;
    
public:
    
    Light();
    virtual ~Light(void);
    
    void bind(int, Matrix4 c);
    void unbind(void);
    
    virtual void draw(Matrix4 c);
    virtual void update();
    virtual void idle();
    
    virtual void myDraw(DrawData&);
    
};

#endif
