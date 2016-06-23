#version 120

varying vec3 norm;
varying vec4 position;
//uniform sample1D edgeramp;

void main()
{
    //gl vert time modelview
    norm = normalize(gl_NormalMatrix * gl_Normal);
    position = gl_ModelViewMatrix * gl_Vertex;
    //position = vec3(gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex);
    gl_Position = ftransform();
    
}