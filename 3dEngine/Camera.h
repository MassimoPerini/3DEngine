//
//  Camera.h
//  3dEngine
//
//  Created by Massimo Perini on 31/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Camera__
#define ___dEngine__Camera__

#include <iostream>
#include <vector>

#include <GLUT/glut.h>
#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)

using std::vector;

struct SF3dVector  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
};
struct SF2dVector
{
	GLfloat x,y;
};
SF3dVector F3dVector ( GLfloat x, GLfloat y, GLfloat z );



class Camera
{
private:
	
	SF3dVector ViewDir;
	SF3dVector RightVector;
	SF3dVector UpVector;
	SF3dVector Position;
    
    double lookingAngle, aspectRatio, minDist, maxDist;
    bool active;
    
	GLfloat RotatedX, RotatedY, RotatedZ;
	
public:
	Camera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
    Camera (double lookingAngle, double aspectRatio, double minDist, double maxDist, bool active);
    
	void insideCamera ();	//executes some glRotates and a glTranslate command
    //Note: You should call glLoadIdentity before using Render
    
	void Move ( SF3dVector Direction );
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
    
	void MoveForward ( GLfloat Distance );
	void MoveUpward ( GLfloat Distance );
	void StrafeRight ( GLfloat Distance );
    void activate();
    void setActive (bool active);
    void setProprieties (double posX, double posY, double posZ, double ruotaX, double ruotaY, double ruotaZ, double inclinazione);

    ~Camera();

};

#endif /* defined(___dEngine__Camera__) */
