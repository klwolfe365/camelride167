#version 120
#extension GL_EXT_gpu_shader4 : enable

varying vec4 position;
varying vec3 normal;
varying vec3 color;
uniform float band_width;
uniform float water_level;

void main()
{
    //Declare variables for intermediate calculations
    vec4 finalColor;
    vec3 lightDir;
    float attenuation;
    float distance;
    
   
    //Declare and initialize variables for storing lighting results
    vec3 finalLighting = vec3(gl_FrontMaterial.emission);
    vec3 ambientReflection = vec3(0.0,0.0,0.0);
    vec3 diffuseReflection = vec3(0.0,0.0,0.0);
    
    //Loop through all 8 lights that the OpenGL fixed function pipeline supports
    for (int i = 0; i < 1; ++i)
    {
        //Calculate the light direction
        lightDir = gl_LightSource[i].position.xyz - position.xyz;
        
        //Add the ambient light factor to the ambient accumulator
        //ambientReflection += vec3(gl_FrontMaterial.ambient) * vec3(gl_LightSource[i].ambient);
        
        //If the light is behind the surface, continue
        if(dot(normal, lightDir) < 0.0)
            continue;
        
        //Set the default attenuation to none (by the multiplicative identity, this is 1.0)
        attenuation = 1.0;
        
        //If the light is not a directional light, then apply the appropriate attenuation
        if (0.0 != gl_LightSource[i].position.w)
        {
            distance = length(lightDir);
            attenuation = 1.0 / (gl_LightSource[i].constantAttenuation
                                 + gl_LightSource[i].linearAttenuation * distance
                                 + gl_LightSource[i].quadraticAttenuation * distance * distance);
        }

        diffuseReflection += attenuation * vec3(gl_LightSource[i].diffuse) * (color) * max(0.0, dot(normal, normalize(lightDir)));
    }
    
    //Sum all of the lighting together
    finalLighting = finalLighting + ambientReflection + diffuseReflection;
    
    //Return the final lighting
    gl_FragColor = vec4(finalLighting, 1.0);
}