//
//  Material.cpp
//  3dEngine
//
//  Created by Massimo on 02/03/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include "Material.h"

#include <string>

using namespace std;

Material::Material ()
{
    ambient[0]=0.2;
    ambient[1]=0.2;
    ambient[2]=0.2;
    diffuse[0]=0.2;
    diffuse[1]=0.4;
    diffuse[2]=0.4;
    specWeight=1;
    specular[0]=0.2;
    specular[1]=0.1;
    specular[2]=0.2;
    diffMap="";
    name="";
    diffSetted=false;
}

Material::~Material ()
{
    
}

Material::Material (string name)
{
    ambient[0]=0.2;
    ambient[1]=0.2;
    ambient[2]=0.2;
    diffuse[0]=0.2;
    diffuse[1]=0.4;
    diffuse[2]=0.4;
    specWeight=1;
    specular[0]=0.2;
    specular[1]=0.1;
    specular[2]=0.2;
    diffMap="";
    this->name=name;
    this->diffSetted=false;
    cout<<this->name;
}

void Material::setAmbient (double r, double g, double b)
{
    ambient[0]=r;
    ambient[1]=g;
    ambient[2]=b;
}

void Material::setDiffuse (double r, double g, double b, double alpha)
{
    diffuse[0]=r;
    diffuse[1]=g;
    diffuse[2]=b;
    diffuse[3]=alpha;
}

void Material::setAlpha (double alpha)
{
    diffuse[3]=alpha;
}

void Material::setSpecular (double r, double g, double b)
{
    specular[0]=r;
    specular[1]=g;
    specular[2]=b;
}

void Material::setSpecWeight (double weight)
{
    specWeight=weight;
}

void Material::setDiffuseMap (string path)
{
    diffMap=path;
}

void Material::setDiffuseMap(GLuint mat)
{
    txtDiffMap=mat;
    diffSetted=true;
}

string Material::getName ()
{
    return name;
}

void Material::bind ()
{
    
}

bool Material::hasDiffuseMap ()
{
    return this->diffSetted;
}


GLuint *Material::getDiffuseMap ()
{
    return &txtDiffMap;
}

GLfloat* Material::getDiffuse()
{
    return diffuse;
}

GLfloat* Material::getAmbient()
{
    return ambient;
}

GLfloat* Material::getSpecular()
{
    return specular;
}