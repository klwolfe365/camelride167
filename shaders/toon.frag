#version 120

uniform vec3 lightDir;
uniform vec4 color;
varying vec3 norm;
varying vec4 position;

//cos of normal
void main()
{
    float intensity;
    vec4 shade;
    //vec3 n = normalize(norm);
    vec3 p = -1 * normalize(position.xyz);
    float angle = acos(dot(p, norm));
    intensity = dot(vec3(gl_LightSource[1].position), norm);
    
    if (intensity > 1.25){
        shade = color;
    }
    else if (intensity > 0.8){
        shade = color * .7;
        
    }
    else if (intensity > 0.25)
        shade = color * .4;
    else
        shade = color * .3;
    
    if(angle > 1.1)
        shade = vec4(0.0,0.0,0.0,1.0);
    gl_FragColor = shade;
    
}
