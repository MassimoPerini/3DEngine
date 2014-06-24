//
//  Point.h
//  3dEngine
//
//  Created by Massimo Perini on 29/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Point__
#define ___dEngine__Point__

#include <iostream>
#include "Vector.h"

class Point
{
private:
    
    double tuple[3];
    double uvwCoords[3];
    double normalCoord [3];
    
public:
    
    double *getTuple();
    double* getNormal();
    double* getUvw();

    
    //Constructor
    Point (double x, double y, double z);
    Point ();
    
    //Destructor
    ~Point();
    
    //basic operators
    Point* addVectorToPoint(Vector v);
    Point* subtractVectorFromPoint(Vector v);
    Vector* subtractPointFromPoint(Point p);
    
    //Getter and setters
    void setPointToPoint(Point p);
    void setUvw (double u, double v, double w);
    void setNormal (double x, double y, double z);
    
    //Functions
    void drawPoint();

    
};

#endif /* defined(___dEngine__Point__) */
