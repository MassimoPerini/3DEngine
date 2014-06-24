//
//  Vector.cpp
//  3dEngine
//
//  Created by Massimo Perini on 29/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//
#define _USE_MATH_DEFINES M_PI

#include <math.h>

#include "Vector.h"

using namespace std;

Vector::Vector(double x, double y, double z)
{
    parameters[0]=x;
    parameters[1]=y;
    parameters[2]=z;
}

Vector::Vector ()
{
    parameters[0]=0;
    parameters[1]=0;
    parameters[2]=0;
}


Vector::~Vector()
{
    
}

Vector* Vector::addVectorToVector(Vector v)
{
    double* parVector=v.getParameters();
    return new Vector (parameters[0]+parVector[0], parameters[1]+parVector[1], parameters[2]+parVector[2]);
}
Vector* Vector::subtractVectorFromVector(Vector v)
{
    double* parVector=v.getParameters();
    return new Vector (parameters[0]-parVector[0], parameters[1]-parVector[1], parameters[2]-parVector[2]);
}

double* Vector::getParameters ()
{
    return parameters;
}

Vector* Vector::rotateXY(double degrees)
{
    double rad=degrees*(M_PI/180);
    double firstVal=(cos(rad)*parameters[0])+(-1*sin(rad)*parameters[1]);
    double secVal=(sin(rad)*parameters[0])+(cos(rad)*parameters[1]);
    double thirdVal=parameters[2];
    return new Vector (firstVal, secVal, thirdVal);
    
}
Vector* Vector::rotateXZ(double degrees)
{
    double rad=degrees*(M_PI/180);
    double firstVal=(cos(rad)*parameters[0])+(sin(rad)*parameters[2]);
    double secVal=parameters[1];
    double thirdVal=(-1*sin(rad)*parameters[0])+(cos(rad)*parameters[2]);
    return new Vector (firstVal, secVal, thirdVal);
}
Vector* Vector::rotateYZ(double degrees)
{
    double rad=degrees*(M_PI/180);
    double firstVal=parameters[0];
    double secVal=(cos(rad)*parameters[1])+(-1*sin(rad)*parameters[2]);
    double thirdVal=(sin(rad)*parameters[1])+(cos(rad)*parameters[2]);
    return new Vector (firstVal, secVal, thirdVal);
}
Vector* Vector::scale(double s0,double s1,double s2)
{
    double firstVal=parameters[0]*s0;
    double secVal=parameters[1]*s1;
    double thirdVal=parameters[2]*s2;
    return new Vector (firstVal, secVal, thirdVal);
}