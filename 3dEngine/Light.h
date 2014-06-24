//
//  Light.h
//  3dEngine
//
//  Created by Massimo on 30/03/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Light__
#define ___dEngine__Light__

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <string>

using namespace std;

class Light
{
private:
    
    GLfloat diffuse [4];
    GLfloat ambient [4];
    GLfloat specular [4];
    GLfloat position [4];
    string name;
    
public:
    
    Light(string name);
    Light (string name, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat w);
    
    ~Light();
    
    void setPosition (GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat w);
    void setDiffuse (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void setAmbient (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void setSpecular (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    
    string getName ();
    GLfloat * getPosition ();
    GLfloat * getDiffuse ();
    GLfloat * getAmbient ();
    GLfloat * getSpecular ();
    
};

#endif /* defined(___dEngine__Light__) */
