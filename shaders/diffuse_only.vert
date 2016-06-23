#version 120

varying vec4 position;
varying vec3 normal;
uniform float water_level;
uniform float band_width;
varying vec3 color;

void main()
{
    //Transform the normal into world coordinates
    normal = normalize(gl_NormalMatrix * gl_Normal);
    position = gl_Vertex;
    float level = (position.y - water_level)/band_width;

    if(position.y < water_level){
        position.y = water_level;
        color = vec3(0.0,0.0,1.0);
        normal = vec3(0,1,0);
    }
    else if(level < .2)
        color = vec3(1.0,1.0,0.0);
    else if(level < 1.0)
        color = vec3(0.0,1.0,0.0);
    else if(level < 1.8)
        color = vec3(0.2,0.2,0.2);
    else
        color = vec3(1.0,1.0,1.0);

    
        //Transform the vertex into world coordinates
    position = gl_ModelViewMatrix * gl_Vertex;
    
    //Set the gl position of this vertex
    gl_Position = ftransform();
}