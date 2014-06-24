//
//  Vector.h
//  3dEngine
//
//  Created by Massimo Perini on 29/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Vector__
#define ___dEngine__Vector__

#include <iostream>

class Vector
{
private:
   double parameters [3]; //(x,y,z)

public:
    
    //Constructors
    Vector (double x, double y, double z);
    Vector ();
    ~Vector();
    
    //Basic operators
    Vector* addVectorToVector(Vector v);
    Vector* subtractVectorFromVector(Vector v);
    
    Vector* rotateXY(double degrees);
    Vector* rotateYZ(double degrees);
    Vector* rotateXZ(double degrees);
    Vector* scale(double s0,double s1,double s2);

    
    //Getter & setter
    double* getParameters ();

};

#endif /* defined(___dEngine__Vector__) */
