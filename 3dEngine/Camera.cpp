//
//  Camera.cpp
//  3dEngine
//
//  Created by Massimo Perini on 31/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include "Camera.h"
#include <vector>
#include <math.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using std::vector;



#define SQR(x) (x*x)

#define NULL_VECTOR F3dVector(0.0f,0.0f,0.0f)

SF3dVector F3dVector ( GLfloat x, GLfloat y, GLfloat z )
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLfloat GetF3dVectorLength( SF3dVector * v)
{
	return (GLfloat)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

SF3dVector Normalize3dVector( SF3dVector v)
{
	SF3dVector res;
	float l = GetF3dVectorLength(&v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

SF3dVector operator+ (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
SF3dVector operator- (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


SF3dVector operator* (SF3dVector v, float r)
{
	SF3dVector res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

SF3dVector CrossProduct (SF3dVector * u, SF3dVector * v)
{
	SF3dVector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;
    
	return resVector;
}
float operator* (SF3dVector v, SF3dVector u)	//dot product
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}




/***************************************************************************************/

Camera::Camera()
{
	//Init with standard OGL values:
	Position = F3dVector (0.0, 0.0,	0.0);
	ViewDir = F3dVector( 0.0, 0.0, -1.0);
	RightVector = F3dVector (1.0, 0.0, 0.0);
	UpVector = F3dVector (0.0, 1.0, 0.0);
    
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
}

Camera::Camera (double lookingAngle, double aspectRatio, double minDist, double maxDist, bool active)
{
    //Init with standard OGL values:
	Position = F3dVector (0.0, 0.0,	0.0);
	ViewDir = F3dVector( 0.0, 0.0, -1.0);
	RightVector = F3dVector (1.0, 0.0, 0.0);
	UpVector = F3dVector (0.0, 1.0, 0.0);
    
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
    
    this->lookingAngle=lookingAngle;
    this->aspectRatio=aspectRatio;
    this->maxDist=maxDist;
    this->minDist=minDist;
    this->active=active;
    if (active)
    {
        this->activate();
    }
}

void Camera::setActive (bool active)
{
    this->active=active;
}

void Camera::activate()
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(this->lookingAngle, this->aspectRatio, this->minDist, this->maxDist);  //Angolo, aspect ratio, distanza min, distanza max
    //senza il lookAt è a 0
    glMatrixMode(GL_MODELVIEW);
    this->active=true;
}

void Camera::Move (SF3dVector Direction)
{
	Position = Position + Direction;
}

void Camera::RotateX (GLfloat Angle)
{
	RotatedX += Angle;
	
	//Rotate viewdir around the right vector:
	ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)
								+ UpVector*sin(Angle*PIdiv180));
    
	//now compute the new UpVector (by cross product)
	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
    
	
}

void Camera::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	
	//Rotate viewdir around the up vector:
	ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)
								- RightVector*sin(Angle*PIdiv180));
    
	//now compute the new RightVector (by cross product)
	RightVector = CrossProduct(&ViewDir, &UpVector);
}

void Camera::RotateZ (GLfloat Angle)
{
	RotatedZ += Angle;
	
	//Rotate viewdir around the right vector:
	RightVector = Normalize3dVector(RightVector*cos(Angle*PIdiv180)
                                    + UpVector*sin(Angle*PIdiv180));
    
	//now compute the new UpVector (by cross product)
	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void Camera::insideCamera()
{
    if (active){
	//The point at which the camera looks:
	SF3dVector ViewPoint = Position+ViewDir;
    
	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(	Position.x,Position.y,Position.z,
              ViewPoint.x,ViewPoint.y,ViewPoint.z,
              UpVector.x,UpVector.y,UpVector.z);
    }
}

void Camera::setProprieties (double posX, double posY, double posZ, double ruotaX, double ruotaY, double ruotaZ, double inclinazione)
{
    this->RotateX(ruotaX);
    this->RotateY(ruotaY);
    this->RotateZ(ruotaZ);
    Position = F3dVector (posX, posY,posZ);
    this->StrafeRight(inclinazione);
    
    //    this->setLooking();
}

void Camera::MoveForward( GLfloat Distance )
{
	Position = Position + (ViewDir*-Distance);
}

void Camera::StrafeRight ( GLfloat Distance )
{
	Position = Position + (RightVector*Distance);
}

void Camera::MoveUpward( GLfloat Distance )
{
	Position = Position + (UpVector*Distance);
}

/*void Camera::setLooking ()
{
    if (active){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(position[0], position[1], position[2], looking[0], looking[1], looking[2], upVector[0], upVector[1], upVector[2]);//posizione x, y, x, posizione del punto centrale a cui guardare, rotazione (direzione del vettore su)
        
        
        
        glutPostRedisplay();
        
    }
}*/

Camera::~Camera()
{/*
    for (int i=0;i<drawableObj.size();i++)
        delete drawableObj[i];
    vector <Drawable*> ().swap(drawableObj);*/
}