#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);

    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    //c.print("Correct camera");
    update();
    //c.print("Actual Camera");
    //ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
    //ci.print("Camera Inverse");
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    Vector3 z = (e-d);
    z = z.normalize();
    Vector3 x = up.cross(z);
    x = x.normalize();
    Vector3 y = z.cross(x);
    //y.normalize();
    
    //Use these axes and the e vector to create a camera matrix c
    Matrix4 cam(x[0], x[1], x[2], 0,
                y[0], y[1], y[2], 0,
                z[0], z[1], z[2], 0,
                e[0], e[1], e[2], 1);
    c = cam;
    //Use c to solve for an inverse camera matrix ci
    Matrix4 r = {c.get(0,0), c.get(0,1), c.get(0,2), 0,
        c.get(1,0), c.get(1,1), c.get(1,2), 0,
        c.get(2,0), c.get(2,1), c.get(2,2), 0,
        0, 0, 0, 1
    };
    r = r.transpose();
    //r.print("R-Transpose");
    Matrix4 t = {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -e[0], -e[1], -e[2], 1};
    ci = r*t;
    //c.print("Camera Matrix");
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::print(){
    ci.print("camera-inverse");
}

void Camera::move(float x, float y, float z)
{
    Vector3 v = Vector3(x, y, z);
    Vector3 newE, newD;
    newE = e + c*v;
    newD = d + c*v;
    set(newE, newD, up);
}

void Camera::lookAt(Vector3 axis, float angle)
{
    Vector3 lookAt, newLookAt, newD;
    Matrix4 m;
    lookAt = d - e;
    m.makeRotateArbitrary(axis, angle);
    newLookAt = m * lookAt;
    newD = e + newLookAt;
    set(e, newD, up);
}