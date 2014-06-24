//
//  Face.h
//  3dEngine
//
//  Created by Massimo Perini on 02/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Face__
#define ___dEngine__Face__

#include <iostream>
#include "Point.h"
#include <vector>
#include "Material.h"

using namespace std;

class Face
{
private:
    vector<Point *> faceVertices;
    Material *mat;
    
public:
    Face();//constructor
    ~Face();
    void addPoint(Point *p);
    
    void setMaterial (Material *m);
    Material *getMaterial ();
    
    vector<Point*>* getPoints();
};

#endif /* defined(___dEngine__Face__) */
