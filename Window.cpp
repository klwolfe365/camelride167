#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "Globals.h"
#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Drawable.h"
#include "Geode.h"
#include "MatrixTransform.h"
#include "Group.h"



int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height inpixels here
Group Window::root = Group();
Group Window::terr = Group();
float prev_y = 0;
extern std::string cwd;

void Window::initialize(void)
{

    
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    
    Globals::shape = &Globals::camel;
//    Globals::camel.obj_color = new Color(Color::camel());
//    Globals::shapeTransform->trans = Matrix4().makeScale(.15)*Matrix4().makeRotateX(-M_PI_2)*Matrix4().makeRotateZ(-M_PI_4)*Matrix4().makeTranslate(0.0, 5.0,0.0)*Matrix4().setIdentity();
    Globals::shapeTransform->addChild(Globals::camel_ride);
//    root.addChild(Globals::shapeTransform);
//    //Setup obj material properties

    /*Initialize the skybox textures*/
    Globals::skybox.top = new Texture((cwd + "/skyboxes/s_top.ppm").c_str());
    Globals::skybox.bottom = new Texture((cwd + "/skyboxes/s_down.ppm").c_str());
    Globals::skybox.left = new Texture((cwd + "/skyboxes/s_right.ppm").c_str());
    Globals::skybox.right = new Texture((cwd + "/skyboxes/s_left.ppm").c_str());
    Globals::skybox.front = new Texture((cwd + "/skyboxes/s_front.ppm").c_str());
    Globals::skybox.back = new Texture((cwd + "/skyboxes/s_back.ppm").c_str());

    Globals::shader = new Shader((cwd + "/shaders/toon.vert").c_str(), (cwd + "/shaders/toon.frag").c_str());
//    Globals::terrain.init("/Users/karen/cse167/Project1/desert.ppm").c_str();
    Globals::sandstorm->sand_text = new Texture((cwd + "/textures/iron.ppm").c_str());
//    MatrixTransform * terrTrans = new MatrixTransform(Matrix4().makeTranslate(-1000, -5000, 0)*Matrix4().makeScale(.1)*Matrix4().setIdentity());
//    terrTrans->addChild(&Globals::terrain);
//    root.addChild(terrTrans);
//    //root.addChild(&Globals::terrain);
   
    //Globals::terrain_desert = Terrain();

//    Globals::sandstorm->initSystem();
//    Globals::sandstorm->genSystem();
//    root.addChild(Globals::sandstorm);
    
    //Globals::shader->printLog();
    //Globals::rasterizer = Rasterizer();
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    root.removeChild(Globals::sandstorm);
    Globals::sandstorm->update();
    root.addChild(Globals::sandstorm);
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    

    glViewport(0, 0, w, h);           //Set new viewport size
    glMatrixMode(GL_PROJECTION);      //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                 //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 2000.0); //Set perspective projection viewing frustum


    Globals::rasterizer.reshape(width,height);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    
    //Globals::rasterizer.clearBuffer();    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
   
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::dl.bind(1, Matrix4().setIdentity());
    Globals::pl.bind(0, Matrix4().makeTranslate((Globals::pl.position.toVector3())));
    //Globals::pl.draw(Matrix4().makeTranslate((Globals::pl.position.toVector3())));
    //Globals::sl.bind(3);
    //Globals::sl.draw(Globals::drawData);
    
    /*if(Globals::army)
        root.draw(Matrix4().setIdentity());
//    else if(Globals::cow_mode)
//        Globals::cow.draw(Globals::drawData);
    else
        terr.draw(Matrix4().setIdentity());
        Globals::terrain.draw(Matrix4().setIdentity());
        //*/
//    Globals::terrain.draw(Matrix4().setIdentity());

///////TEST YOSELF BEFORE YOU WRECK YOSELF//////////
//    testBezierCurve(Globals::bezierC);
//    testBezierPatch(Globals::bezierP, Globals::shapeTransform->trans);
    
//    testDesert(Globals::shapeTransform->trans, Globals::terrain_desert);
///////ALL TESTING MUST END/////////
    
///////UNCOMMENT THIS TO MAKE STUFF WORKS/////////////
    Globals::skybox.draw(Matrix4().setIdentity());
    Globals::shapeTransform->draw(Matrix4().setIdentity());
    
///////YEAH UNCOMMENT THE ABOVE TO MAKE CAMEL AND STUFFS WORKS/////////
    
    
    
    //Globals::sandstorm->draw(Matrix4().setIdentity());
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    
    if(Globals::flag_OpenGL)
        glFlush();
    else
        Globals::rasterizer.display();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
    
}


//TODO: Keyboard callbacks!
void Window::processNormalKeys(unsigned char key, int x, int y) {
    //Matrix4 rotation;
    Vector3 position(0, 0, 0);
    int mod = glutGetModifiers();
    if (mod == GLUT_ACTIVE_CTRL){
        Globals::flag_MouseScroll = !Globals::flag_MouseScroll;
        //std::cout << "Balalalalalala" << std::endl;
    }
    
    switch(key) {
        /*Toggle direction of spin between clockwise and counterclockwise*/
        case 't' :{
            //if(Globals::shape == &Globals::cube)
            Globals::cube.spinAmt = -1 * Globals::cube.spinAmt;
            //Globals::spinAmt = -1 * Globals::spinAmt;
            break;
        }
        /*Move cube left by a small amount*/
        case 'x' :{
            Matrix4 xTrans;
            xTrans.makeTranslate(-1, 0, 0);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = xTrans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            //Globals::shape->toWorld = xTrans * Globals::shape->toWorld;
            break;
        }
        /*Move cube right by a small amount*/
        case 'X' :{
            Matrix4 xTrans;
            xTrans.makeTranslate(1, 0, 0);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = xTrans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            //Globals::shape->toWorld = xTrans * Globals::shape->toWorld;
            break;
        }
        /*Move cube down by a small amount*/
        case 'y' :{
            Matrix4 yTrans;
            yTrans.makeTranslate(0, -1, 0);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = yTrans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            //Globals::shape->toWorld = yTrans * Globals::shape->toWorld;
            break;
        }
        /*Move cube up by a small amount*/
        case 'Y' :{
            Matrix4 yTrans;
            yTrans.makeTranslate(0, 1, 0);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = yTrans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            //Globals::shape->toWorld = yTrans * Globals::shape->toWorld;
            break;
        }
        /*Move cube into screen by a small amount*/
        case 'z' :{
            Matrix4 zTrans;
            zTrans.makeTranslate(0, 0, -1);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = zTrans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            //Globals::shape->toWorld = zTrans * Globals::shape->toWorld;
            break;
        }
        /*Move cube out of screen by a small amount*/
        case 'Z' :{
            Matrix4 zTrans;
            zTrans.makeTranslate(0, 0, 1);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = zTrans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            //Globals::shape->toWorld = zTrans * Globals::shape->toWorld;
            break;
        }
        /*Reset cube position, orientation, and size*/
        case 'r' :
            if(Globals::cube.spinAmt < 0)
                Globals::cube.spinAmt = -1 * Globals::cube.spinAmt;
            //Globals::shape->toWorld.identity();
            break;
        /*Orbit cube around OpenGL window's z axis by a small number of degrees counterclockwise
         *without affecting the spin itself (other than spinning axis)*/
        case 'o' :{
            Matrix4 zRotate;
            zRotate.makeRotateZ(.05);
            //Globals::shape->toWorld = zRotate * Globals::shape->toWorld;
            break;
        }
        /*Orbit cube around OpenGL window's z axis by a small number of degrees clockwise
         *without affecting the spin itself (other than spinning axis)*/
        case 'O' :{
            Matrix4 zRotate;
            zRotate.makeRotateZ(-.05);
            //Globals::shape->toWorld = zRotate * Globals::shape->toWorld;
            break;
        }
        /*Scale cube down about its center*/
        case 's' :{
            Matrix4 scaleD;
            scaleD.makeScale(.95);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = scaleD * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            
            Matrix4 scaleU;
            scaleU.makeScale(1.05);
            Globals::camel_ride->sandstormTrans->trans = scaleU * Globals::camel_ride->sandstormTrans->trans;
            //Globals::shape->toWorld = Globals::shape->toWorld * scaleD;
            break;
        }
        /*Scale cube up about its center*/
        case 'S' :{
            Matrix4 scaleU;
            scaleU.makeScale(1.05);
            if(Globals::army){
                root.removeChild(Globals::androidPlacement);
                Globals::androidPlacement->trans = scaleU * Globals::androidPlacement->trans;
                root.addChild(Globals::androidPlacement);
            }
            else{
                terr.removeChild(Globals::tran);
                Globals::tran->trans = scaleU * Globals::tran->trans;
                terr.addChild(Globals::tran);
            }
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = scaleU * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            
            Matrix4 scaleD;
            scaleD.makeScale(.95);
            Globals::camel_ride->sandstormTrans->trans = scaleD * Globals::camel_ride->sandstormTrans->trans;
            //Globals::shape->toWorld = Globals::shape->toWorld * scaleU;
            break;
        }
        case 'b' :{
            Globals::terrain_desert->setBezierMode(!Globals::terrain_desert->draw_bezier);
            break;
        }
        case 'e':{
            Globals::flag_OpenGL = !Globals::flag_OpenGL;
            break;
        }
        case '+':{
            if(Globals::part < 4)
                Globals::part = ++Globals::part;
            break;
        }
        case '-':{
            if(Globals::part > 1)
                Globals::part = --Globals::part;
            break;
        }
            
        case '1':{
            Globals::dl_on = !Globals::dl_on;
            if(Globals::dl_on)
                std::cout <<  "Directional Light Selected" << std::endl;
            if(!Globals::dl_on)
                std::cout <<  "Directional Light De-selected" << std::endl;
            break;
        }
        case '2':{
            Globals::pl_on = !Globals::pl_on;
            if(Globals::pl_on)
                std::cout <<  "Point Light Selected" << std::endl;
            if(!Globals::pl_on)
                std::cout <<  "Point Light De-selected" << std::endl;
            break;
        }
        case '3':{
            Globals::sl_on = !Globals::sl_on;
            if(Globals::sl_on)
                std::cout <<  "Spot Light Selected" << std::endl;
            if(!Globals::sl_on)
                std::cout <<  "Spot Light De-selected" << std::endl;
            break;
        }
   
        case 'c' :{
            Globals::camera_control = !Globals::camera_control;
            break;
        }
            
        case 27 :
            exit(0);
    }
    
    Globals::shapeTransform->trans.print("toWorld: ");
    
    
    //Globals::shape->update(Globals::updateData);
    displayCallback();


}

//Function Key callbacks!
void Window::processFuncKeys(int key, int x, int y){
    
    
    switch(key) {
        case GLUT_KEY_F1:
            Globals::army = true;
            Globals::group_sel = &root;
            //Globals::shape = &Globals::cube;
            Globals::camera.set(Globals::eDefault, Globals::dDefault, Globals::upDefault);
            glEnable(GL_LIGHTING);
            break;
        case GLUT_KEY_F2:
            Globals::army = false;
            Globals::group_sel = &terr;
            Globals::camera.set(Globals::img1e, Globals::dDefault, Globals::upDefault);
           // Globals::shape = &Globals::house;
            //Globals::camera.set(Globals::img1e, Globals::img1d, Globals::img1up);
            glDisable(GL_LIGHTING);
            break;
        case GLUT_KEY_F3:
            //Globals::shape = &Globals::house;
            //Globals::camera.set(Globals::img2e, Globals::img2d, Globals::img2up);
            glDisable(GL_LIGHTING);
            break;
        /*case GLUT_KEY_F4:
            Globals::shape = &Globals::camel;
            Globals::camera.set(Globals::eDefault, Globals::dDefault, Globals::upDefault);
            glEnable(GL_LIGHTING);
            break;*/
//        case GLUT_KEY_F5:
//            Globals::shape = &Globals::bunny;
//            Globals::camera.set(Globals::eDefault, Globals::dDefault, Globals::upDefault);
//            glEnable(GL_LIGHTING);
//            break;
        /*case GLUT_KEY_F6:
            Globals::shape = &Globals::bear;
            Globals::camera.set(Globals::eDefault, Globals::dDefault, Globals::upDefault);
            glEnable(GL_LIGHTING);
            break;*/
            
        case GLUT_KEY_F7:
            Globals::cow_mode = true;
            Globals::army = false;
//            Globals::shape = &Globals::cow;
            Globals::camera.set(Globals::eDefault, Globals::dDefault, Globals::upDefault);
            glEnable(GL_LIGHTING);
            break;
            
        case GLUT_KEY_UP:{
            if(Globals::camera_control){
                Globals::camera.move(0.0, 3.0, 0.0);
                Globals::camel_ride->moveSandstorm(0.0, 3.0, 0.0);
                break;
            }
            
            //do something here
            Globals::wind_speed += .5;
            std::cout << "windspeed: " << Globals::wind_speed <<std::endl;
//            Matrix4 zRotate;
//            zRotate.makeRotateX(.05);
            //Globals::shape->toWorld = Globals::shape->toWorld * zRotate;
            break;
        }
        case GLUT_KEY_DOWN:{
            if(Globals::camera_control){
                Globals::camera.move(0.0, -3.0, 0.0);
                Globals::camel_ride->moveSandstorm(0.0, -3.0, 0.0);
                break;
            }
            
            Globals::wind_speed -= .5;
            std::cout << "windspeed: " << Globals::wind_speed <<std::endl;

            Matrix4 zRotate;
            zRotate.makeRotateX(-.05);
           // Globals::shape->toWorld = Globals::shape->toWorld * zRotate;
            //do something here
            break;
        }
        case GLUT_KEY_LEFT:{
            if(Globals::camera_control){
                Globals::camera.move(-3.0, 0.0, 0.0);
                Globals::camel_ride->moveSandstorm(-3.0, 0.0, 0.0);
                break;
            }
            
            Matrix4 spinL;
            spinL.makeRotateY(-.05);
            //Globals::shape->toWorld = Globals::shape->toWorld * spinL;
            break;
        }
        case GLUT_KEY_RIGHT:{
            if(Globals::camera_control){
                Globals::camera.move(3.0, 0.0, 0.0);
                Globals::camel_ride->moveSandstorm(3.0, 0.0, 0.0);
                break;
            }
            
            Matrix4 spinR;
            spinR.makeRotateY(.05);
            //Globals::shape->toWorld = Globals::shape->toWorld * spinR;
            break;
        }
    }

}

/*TODO: how to process motion while being clicked???*/
void Window::processMouse(int button, int state, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            //process left button clicky stuff
            Globals::movement = MOUSE_LEFT;
            Globals::lastPoint = trackballMapping(Vector3(x,y,0));
            prev_y = y;
            //Save mouse position as logical sphere location, store as lastPoint
            break;
        case GLUT_RIGHT_BUTTON:
            Globals::movement = MOUSE_RIGHT;
            Globals::lastPoint[0] = x;
            Globals::lastPoint[1] = y;
            break;
        case MOUSE_WHEEL:
            break;
            
    }
}

void Window::processMouseMovement(int x, int y){
    Vector3 direction;
   // float pixel_dif;
    float rot_angle;//, zoom_factor;
    Vector3 currPoint;
    float updwn = prev_y - y;
    prev_y = y;
    switch(Globals::movement){
        case MOUSE_LEFT: {
            
            currPoint = trackballMapping(Vector3(x,y,0));
            direction = currPoint - Globals::lastPoint;
            float velocity = direction.magnitude();
            if(velocity > .0001){
                Vector3 rot_axis;
                rot_axis = Globals::lastPoint.cross(currPoint);
                rot_angle = velocity * ROT_SCALE;
                
                if(Globals::camera_control){
                    rot_axis = rot_axis * -0.5;
                    Globals::camera.lookAt(rot_axis, rot_angle * 0.75);
                    Globals::camel_ride->rotateSandstorm(rot_axis, rot_angle * 0.75);
                    break;
                }
                
                Matrix4 rm;
                rm = rm.makeRotateArbitrary(rot_axis, rot_angle);
                
                root.removeChild(Globals::shapeTransform);
                Globals::shapeTransform->trans = rm * Globals::shapeTransform->trans;
                root.addChild(Globals::shapeTransform);
                Globals::lastPoint = currPoint;
                
                
            }
            break;
        }
        case MOUSE_RIGHT:{
            currPoint = Vector3(x, y, 0);
            Matrix4 trans;
            trans = trans.makeTranslate((x - Globals::lastPoint[0])*0.05,
                                        (y -Globals::lastPoint[1])*-0.05, 0);
            root.removeChild(Globals::shapeTransform);
            Globals::shapeTransform->trans = trans * Globals::shapeTransform->trans;
            root.addChild(Globals::shapeTransform);
            Globals::lastPoint = currPoint;

            break;
        }
        case MOUSE_WHEEL:
            std::cout << "yoyoyoyo" << std::endl;
            break;
        
    }
    
}

void Window::processPassiveMouse(int x, int y){
    if(Globals::flag_MouseScroll){
        //Vector3 currPoint = Vector3(Globals::lastPoint, y, 0);
        Matrix4 mz;
        //Globals::lastPoint[2] = Globals::lastPoint[2] - y;
        mz = mz.makeTranslate(0, 0, (Globals::lastPoint[1]-y) * -0.05);
        if(Globals::army){
            root.removeChild(Globals::androidPlacement);
            Globals::androidPlacement->trans = mz * Globals::androidPlacement->trans;
            root.addChild(Globals::androidPlacement);
        }
        else{
            terr.removeChild(Globals::tran);
            Globals::tran->trans = mz * Globals::tran->trans;
            terr.addChild(Globals::tran);
        }
          //  Globals::shape->toWorld = mz * Globals::shape->toWorld;
       // if(Globals::dl_on)
         //   Globals::dl.toWorld = mz * Globals::dl.toWorld;
//        if(Globals::pl_on)
//            Globals::pl.toWorld = mz * Globals::pl.toWorld;
//        if(Globals::sl_on)
//            Globals::sl.toWorld = mz * Globals::sl.toWorld;
//        //Globals::flag_MouseScroll = false;

    }
    Globals::lastPoint = Vector3(x,y,0);


}

Vector3 Window::trackballMapping(Vector3 point){
    Vector3 v;
    float d;
    
    v[0] = (2.0*point[0] - width)/width;
    v[1] = (height - 2.0*point[1])/height;
    v[2] = 0;
    
    d = v.magnitude();
    
    d = (d < 1.0) ? d : 1.0;
    v[2] = sqrtf(1.001 - d*d);
    v = v.normalize();
    
    return v;
}


//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!

void Window::setUpArmy(){
    for(int r = -5; r < 5; r++){
        for(int c = 0; c < 10; c++){
            float row = r*8.0;
            float col = c*-8.0;
            Matrix4 translate = Matrix4().makeTranslate(row, 0.0, col);
            MatrixTransform* armyPlacement = new MatrixTransform(translate);
            armyPlacement->addChild(&Globals::android);
            Globals::androidArmy.addChild(armyPlacement);
        }
    }
    Globals::androidPlacement->addChild(&Globals::androidArmy);
    root.addChild(Globals::androidPlacement);
}

