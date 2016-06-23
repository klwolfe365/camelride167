#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "House.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Drawable.h"
#include "OBJObject.h"
#include "Rasterizer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Skybox.h"
#include "Cylinder.h"
#include "Android.h"
#include "Terrain.h"
#include "Ground.h"
#include "Shader.h"
#include "ParticleSystem.h"
#include "BezierCurve.h"
#include "BezierPatch.h"
#include "Terrain.h"
#include "CamelRide.h"
#include <unistd.h>

#define GetCurrentDir getcwd

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_WHEEL 3
#define ROT_SCALE 1
#define ZOOM_SCALE .0001


class Sphere;
class House;
class Android;

class Globals
{
    
public:
        
    static Camera camera;
    static Cube cube;
    static Sphere sphere;
    static Vector3 eDefault;
    static Vector3 dDefault;
    static Vector3 upDefault;
    
    static House house;
    static Vector3 img1e;
    static Vector3 img1d;
    static Vector3 img1up;
    static Vector3 img2e;
    static Vector3 img2d;
    static Vector3 img2up;
    
    //static OBJObject bunny;
    static OBJObject camel;
    static OBJObject cow;
    
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    static bool rotateY;
    static float spinAmt;
    static bool sphereVis;
    static Geode *shape;
    
    static Rasterizer rasterizer;
    static bool flag_OpenGL;
    static int part;
    //Feel free to add more member variables as needed
    

    static int movement;
    static Vector3 lastPoint;
    static Vector3 point;
    static bool flag_MouseScroll;
    
    
    static PointLight pl;
    static DirectionalLight dl;
    static SpotLight sl;
    
    static bool pl_on;
    static bool sl_on;
    static bool dl_on;
    static Material defaultMaterial;
    static Material bunnyMat;
    
    static Skybox skybox;
    static Cylinder cyl;
    static Android android;
    static std::vector<Texture*> t;
    static Group androidArmy;
    static MatrixTransform* androidPlacement;
    
    static bool army;
    static Terrain terrain;
    static Ground ground;
    static MatrixTransform * tran;
    static MatrixTransform * shapeTransform;
    static MatrixTransform * light_path;


    static Group* group_sel;
    static bool cow_mode;
    static Shader* shader;
    static ParticleSystem * sandstorm;
    static float wind_speed;
    
    //final project
    static BezierCurve bezierC;

    static BezierPatch bezierP;
    
    static Terrain *terrain_desert;
    
    static CamelRide *camel_ride;
    
    static bool camera_control;
};

#endif
