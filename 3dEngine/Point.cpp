//
//  Point.cpp
//  3dEngine
//
//  Created by Massimo Perini on 29/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include "Point.h"
#include <iostream>
#include <vector>

using namespace std;

Point::Point (double x, double y, double z)
{
    tuple[0]=x;
    tuple[1]=y;
    tuple[2]=z;
}

Point::Point ()
{
    tuple[0]=0;
    tuple[1]=0;
    tuple[2]=0;
    normalCoord[0]=0;
    normalCoord[1]=0;
    normalCoord[2]=0;
    
 //   std::vector<double> position(3, 0);
}

Point::~Point()
{
    //delete
}

double* Point::getUvw()
{
    return uvwCoords;
}

double* Point::getTuple()
{
    return tuple;
}

double* Point::getNormal()
{
    return normalCoord;
}

void Point::drawPoint()
{
    cout << "\nX: "<<tuple[0]<<"\nY: "<<tuple[1]<<"\nZ: "<<tuple[2];
}

void Point::setUvw (double u, double v, double w)
{
    uvwCoords[0]=u;
    uvwCoords[1]=v;
    uvwCoords[2]=w;
}

void Point::setNormal (double x, double y, double z)
{
    this->normalCoord[0]=x;
    this->normalCoord[1]=y;
    this->normalCoord[2]=z;
}

Point* Point::addVectorToPoint(Vector v)
{
    double* parVector=v.getParameters();
    return new Point(tuple[0]+parVector[0], tuple[1]+parVector[1], tuple[2]+parVector[2]);     //Evito di ritornare un riferimento ad un oggetto non più allocato
}
Point* Point::subtractVectorFromPoint(Vector v)
{
    double* parVector=v.getParameters();
    return new Point (tuple[0]-parVector[0], tuple[1]-parVector[1], tuple[2]-parVector[2]);
}
Vector* Point::subtractPointFromPoint(Point p)
{
    double* posPoint=p.getTuple();
    return new Vector (tuple[0]-posPoint[0], tuple[1]-posPoint[1], tuple[2]-posPoint[2]);
}

void Point::setPointToPoint(Point p)
{
    double* pos=p.getTuple();
    tuple[0]=pos[0];
    tuple[1]=pos[1];
    tuple[2]=pos[2];
}