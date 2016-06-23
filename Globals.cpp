#include "Globals.h"
#include "Window.h"

std::string cwd = "/Users/macuser/Desktop/CSE167/CSE167-FINAL-PROJECT/camelride167";
Camera Globals::camera = Camera();

Cube Globals::cube = Cube(10.0);
Sphere Globals::sphere = Sphere(2.5, 100.0, 100.0);

Vector3 Globals::eDefault(0.0, 0.0, 20.0);
Vector3 Globals::dDefault(0.0, 0.0, 0.0);
Vector3 Globals::upDefault(0.0, 1.0, 0.0);

House Globals::house = House();
Vector3 Globals::img1e(0, 100.0, 350.0);
Vector3 Globals::img1d(0.0, 0.0, 0.0);
Vector3 Globals::img1up(0.0, 1.0, 0.0);
Vector3 Globals::img2e(-28.33, 11.66, 23.33);
Vector3 Globals::img2d(-5.0, 0.0, 0.0);
Vector3 Globals::img2up(0.0, 1.0, 0.5);

//OBJObject Globals::bunny = OBJObject("/Users/karen/cse167/Project1/bunny.obj");
OBJObject Globals::camel = OBJObject(cwd + "/objs/camel.obj");

//OBJObject Globals::cow = OBJObject("/Users/karen/cse167/Project1/cow.obj");

Light Globals::light = Light();

DrawData Globals::drawData = DrawData();
UpdateData Globals::updateData = UpdateData();

float Globals::spinAmt = .0025;

Geode *Globals::shape = &Globals::skybox;

Rasterizer Globals::rasterizer = Rasterizer();
bool Globals::flag_OpenGL = true;

int Globals::part = 1;


int Globals::movement = -1;
Vector3 Globals::point;
Vector3 Globals::lastPoint;
bool Globals::flag_MouseScroll = false;

DirectionalLight Globals::dl = DirectionalLight();
PointLight Globals::pl = PointLight();
SpotLight Globals::sl = SpotLight();

bool Globals::pl_on = false;
bool Globals::sl_on = false;
bool Globals::dl_on = false;

Material Globals::defaultMaterial = Material(Color::ambientMaterialDefault(), Color::diffuseMaterialDefault(), Color::specularMaterialDefault(), Color::emissionMaterialDefault(), Color::white(), 0);
Material Globals::bunnyMat = Material(Color(0.0,1.0,0.0), Color::diffuseMaterialDefault(), Color::specularMaterialDefault(), Color::emissionMaterialDefault(), Color(0,1.0,0), 100);


Skybox Globals::skybox = Skybox(900.0);
Cylinder Globals::cyl = Cylinder(2.0, 0.5);
Android Globals::android  = Android();
std::vector<Texture*> Globals::t = std::vector<Texture*>();
Group Globals::androidArmy = Group();
MatrixTransform *Globals::androidPlacement = new MatrixTransform(Matrix4().setIdentity());
MatrixTransform *Globals::light_path = new MatrixTransform(Matrix4().makeTranslate(pl.position.toVector3()));

bool Globals::army = true;
Terrain Globals::terrain = Terrain();
Ground Globals::ground = Ground();
MatrixTransform *Globals::tran = new MatrixTransform();
MatrixTransform *Globals::shapeTransform = new MatrixTransform(Matrix4().setIdentity());
Group *Globals::group_sel = new Group();
bool Globals::cow_mode = false;
Shader* Globals::shader;

ParticleSystem* Globals::sandstorm = new ParticleSystem();
float Globals::wind_speed = 0.0;

//final project
BezierCurve Globals::bezierC = BezierCurve(Vector3(0.0, 5.0, 0.0),
                                           Vector3(5.0,0.0,0.0),
                                           Vector3(0.0, 0.0, 0.0),
                                           Vector3(0.0, 0.0, 0.0));

BezierPatch Globals::bezierP = BezierPatch(Vector3(0, 0, 0), Vector3(2, 0, 0), Vector3(4, 0, 0), Vector3(6, 0, 0),
                                           Vector3(0, 0, 2), Vector3(2, 4, 2), Vector3(4, 4, 2), Vector3(6, 0, 2),
                                           Vector3(0, 0, 4), Vector3(2, 4, 4), Vector3(4, 4, 4), Vector3(6, 0, 4),
                                           Vector3(0, 0, 6), Vector3(2, 0, 6), Vector3(4, 0, 6), Vector3(6, 0, 6));

Terrain* Globals::terrain_desert = new Terrain((cwd + "/terrain/desert_large.ppm").c_str());

CamelRide* Globals::camel_ride = new CamelRide();

bool Globals::camera_control = false;