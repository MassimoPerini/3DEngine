//
//  ObjParser.h
//  3dEngine
//
//  Created by Massimo Perini on 02/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__ObjParser__
#define ___dEngine__ObjParser__

#include <iostream>
#include <vector>
#include "Point.h"
#include "Face.h"
#include <string>

using namespace std;

class Mesh{
    
private:
    std::vector<Face *>* faces;//to store vertex information of 3D model started with v
    //    std::vector<Point&> meshVertices;//to store all 3D model face vertices
    string name;
    
public:
    Mesh(vector<Face *>* faces, string name);//constructor
    ~Mesh();
    Mesh(string name);

    vector<Face*>* getFaces ();
    void setFaces (vector<Face *>* faces);


};
#endif /* defined(___dEngine__ObjParser__) */
