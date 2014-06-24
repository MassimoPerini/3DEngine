//
//  Light.cpp
//  3dEngine
//
//  Created by Massimo on 30/03/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include "Light.h"


Light::Light (string name)
{
    for (int i=0;i<4;i++)
    {
        diffuse[i]=1;
        ambient[i]=1;
        specular[i]=0;
        position[i]=0;
    }
    
    position[2]=-3;
    
    this->name=name;
    
}

Light::Light (string name, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat w)
{
    for (int i=0;i<4;i++)
    {
        diffuse[i]=0;
        ambient[i]=0;
        specular[i]=0;
    }
    
    position[0]=posX;
    position[1]=posY;
    position[2]=posZ;
    position[3]=w;
    this->name=name;
}

void Light::setPosition (GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat w)
{
    position[0]=posX;
    position[1]=posY;
    position[2]=posZ;
    position[3]=w;
}

void Light::setDiffuse (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    diffuse[0]=red;
    diffuse[1]=green;
    diffuse[2]=blue;
    diffuse[3]=alpha;
}

void Light::setAmbient (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    ambient[0]=red;
    ambient[1]=green;
    ambient[2]=blue;
    ambient[3]=alpha;
}

void Light::setSpecular (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    specular[0]=red;
    specular[1]=green;
    specular[2]=blue;
    specular[3]=alpha;
}

Light::~Light()
{
}

GLfloat * Light::getPosition ()
{
    return position;
}
GLfloat * Light::getDiffuse ()
{
    return diffuse;
}
GLfloat * Light::getAmbient ()
{
    return ambient;
}
GLfloat * Light::getSpecular ()
{
    return specular;
}

string Light::getName ()
{
    return name;
}