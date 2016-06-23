#ifndef CSE167_RenderData_h
#define CSE167_RenderData_h

#include <iostream>
#include "Matrix4.h"
#include "Material.h"

class DrawData
{
    
public:
    Matrix4 c;
    Material material;
    //Payload
    //Place any objects here that you want to pass to a draw() call
    
    DrawData(void);
    ~DrawData(void);
    
};

#endif
