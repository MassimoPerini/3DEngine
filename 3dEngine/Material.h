//
//  Material.h
//  3dEngine
//
//  Created by Massimo on 02/03/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Material__
#define ___dEngine__Material__

#include <iostream>
#include <string>
#include <OpenGL/OpenGL.h>

class Material
{
public:
    
    Material ();
    Material (std::string name);
 //   Material ();
    ~Material ();
    
    void setDiffuse (double r, double g, double b, double alpha);
    void setSpecular (double r, double g, double b);
    void setAmbient (double r, double g, double b);
    void setSpecWeight (double weight);
    void setDiffuseMap (std::string path);
    void setDiffuseMap (GLuint mat);
    void bind ();
    GLuint *getDiffuseMap ();
    GLfloat * getDiffuse ();
    GLfloat* getSpecular ();
    GLfloat* getAmbient ();
    void setAlpha (double alpha);
    std::string getName ();
    
    bool hasDiffuseMap ();
    
private:
    GLfloat diffuse [4];
    GLfloat specular [3];
    GLfloat ambient [3];
    double specWeight;
    std::string diffMap;
    std::string name;
    GLuint txtDiffMap;
    bool diffSetted;
};

#endif /* defined(___dEngine__Material__) */
