//
//  Face.cpp
//  3dEngine
//
//  Created by Massimo Perini on 02/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include "Face.h"
#include "Point.h"
#include "Material.h"


vector<Point*>* Face::getPoints()
{
    return &faceVertices;
}


Face::Face()
{
    mat=NULL;
}

Face::~Face()
{
    for (int i=0;i<faceVertices.size();i++)
    {
        delete faceVertices[i];
    }
    vector<Point*>().swap(faceVertices);
}

void Face::addPoint (Point* p)
{
    Point *point=new Point(p->getTuple()[0], p->getTuple()[1], p->getTuple()[2]);
    point->setNormal(p->getNormal()[0], p->getNormal()[1], p->getNormal()[2]);
    point->setUvw(p->getUvw()[0], p->getUvw()[1], p->getUvw()[2]);
    faceVertices.push_back(point);
}

void Face::setMaterial(Material *m)
{
    mat=m;
}

Material* Face::getMaterial ()
{
    return mat;
}