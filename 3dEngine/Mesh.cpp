//
//  ObjParser.cpp
//  3dEngine
//
//  Created by Massimo Perini on 02/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include "Mesh.h"
#include "Point.h"
#include "Face.h"

#include <string>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include <string>

using std::cout;

void Mesh::setFaces (vector<Face *>* faces)
{
    this->faces=faces;

}

vector<Face*>* Mesh::getFaces()
{
    return faces;
}

Mesh::~Mesh()
{
    for (int i=0;i<(*faces).size();i++)
        delete (*faces)[i];
    
    vector<Face*>().swap(*faces);
}

Mesh::Mesh(vector<Face *>* faces, string name)
{
    this->faces=faces;
    this->name=name;
}

Mesh::Mesh(string name)
{
    this->name=name;
}