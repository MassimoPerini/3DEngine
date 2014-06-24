//
//  Parser.cpp
//  3dEngine
//
//  Created by Massimo Perini on 05/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include <string>

#include "Parser.h"
#include <vector>
#include "Mesh.h"
#include "Face.h"
#include "Material.h"

#include "LoadTexture.h"

using namespace std;



vector<Material*>* parseMaterial (const char * filename)
{
    cout<<filename;
    vector<Material*> *result=new vector<Material*>();
    Material *m;
    std::string line;
    std::ifstream in(filename, std::ios::in);
    if (!in)
    {
        cout<<"Cannot open the .obj file";
        exit(1);
        
    }
    
     while (std::getline(in, line))
     {
         if (line.substr(0,2)=="# ")
             continue;
         
         else if (line.substr(0, 7)=="newmtl ")
         {
             m=new Material (line.substr(7));
             result->push_back(m);
             cout<<"a";
         }
         
         else if (line.substr(0,3)=="Ka ")
         {
             //Ambient color (rgb)
             
             std::istringstream v(line.substr(3));
             int i=0;
             double values[3];
             while (v.good())
             {
                 string s;
                 v>>s;
                 values[i]=atof(s.c_str());
                 i++;
             }
             m->setAmbient(values[0], values[1], values[2]);
             
         }
         else if (line.substr(0,3)=="Kd ")
         {
             //diffuse color
             std::istringstream v(line.substr(3));
             int i=0;
             double values[3];
             while (v.good())
             {
                 string s;
                 v>>s;
                 values[i]=atof(s.c_str());
                 i++;
             }
             m->setDiffuse(values[0], values[1], values[2], 1.0);
             
         }
         else if (line.substr(0,3)=="Ks ")
         {
             //specular color
             
             std::istringstream v(line.substr(3));
             int i=0;
             double values[3];
             while (v.good())
             {
                 string s;
                 v>>s;
                 values[i]=atof(s.c_str());
                 i++;
             }
             m->setSpecular(values[0], values[1], values[2]);
             
         }
         else if (line.substr(0,3)=="Tf ")
         {
         }
         else if (line.substr(0,3)=="Ns ")
         {
             std::istringstream v(line.substr(3));
             int i=0;
             string s;
             v>>s;
             m->setSpecWeight(atof(s.c_str()));
             //specular weight
         }
         else if (line.substr(0,3)=="Ni ")
         {
             //specular color
         }
         else if (line.substr(0,2)=="d ")
         {
             std::istringstream v(line.substr(3));
             string s;
             v>>s;
             m->setAlpha(atof(s.c_str()));
         }
         else if (line.substr(0,7)=="map_Ka ")
         {
             //specular color
         }
         else if (line.substr(0,7)=="map_Kd ")
         {
             //diffuse map
             
             size_t found;
             string path(filename);
             found=path.find_last_of("/\\");
             
      //       m->setDiffuseMap((path.substr(0,found).append("/"+line.substr (7))));

             m->setDiffuseMap(loadTexture((path.substr(0,found).append("/"+line.substr (7)).c_str())));
             
             //TODO: carica le texture generando un vettore di gluint. Il loro bind e filtraggio sarà fatto una volta inizializzato openGL.
             
         }
         else if (line.substr(0,7)=="map_Ks ")
         {
             //specular color
         }
         else if (line.substr(0,7)=="map_Ns ")
         {
             //specular color
         }
         else if (line.substr(0,6)=="map_d ")
         {
             //specular color
         }
         else if (line.substr(0,9)=="map_bump ")
         {
             //specular color
         }
         else if (line.substr(0,5)=="bump ")
         {
             //specular color
         }
         else if (line.substr(0,5)=="disp ")
         {
             //specular color
         }
     }
    
    for (int i=0;i<result->size();i++)
    {
        cout<<"Elemento "<<(*result)[i]->getName();
    }
    
    return result;
}

vector<Mesh*>* parser (const char * filename)
{
    vector<Material*> *materials;
    std::cout<<"entrato";
    string actualMaterial="";
    vector<Mesh *> *meshes=new vector<Mesh*> ();
    vector<Face *> *faces;
    std::ifstream in(filename, std::ios::in);
    int indiceObj=0;
    if (!in)
    {
        cout<<"Cannot open the .obj file";
        exit(1);
        
    }
    std::string line;
    std::vector<Point*> points;
    std::vector< vector<double> > textures;
    std::vector< vector<double> > normals;
    Mesh *actualMesh;
    while (std::getline(in, line))
    {
        if (line.substr(0,2)=="# ")
            continue;
        
        if (line.substr(0,7)=="mtllib ")
        {
            
            size_t found;
            string path(filename);
            found=path.find_last_of("/\\");
            
            materials=parseMaterial((path.substr(0,found).append("/"+line.substr (7))).c_str());
        }
        
        else if (line.substr(0,2)=="g " || line.substr(0,2)=="o " )
        {
            if (indiceObj==0)
            {
                faces=new vector<Face *> ();
                actualMesh=new Mesh (line.substr(2));
                meshes->push_back(actualMesh);
            }
            else
            {
                actualMesh->setFaces (faces);
                actualMesh=new Mesh (line.substr(2));
                meshes->push_back(actualMesh);
                faces=new vector<Face*> ();
            }
            indiceObj++;
        }
        
        else if (line.substr(0,2)=="v "){                //vertex
            actualMaterial="";
            std::istringstream v(line.substr(2));
            
            int i=0;
            double values[3];
            while (v.good())
            {
                string s;
                v>>s;
                
                values[i]=atof(s.c_str());
                i++;
            }
            Point *vert=new Point(values[0],values[1],values[2]);
            points.push_back(vert);
        }
        
        else if (line.substr(0,7)=="usemtl ")
        {
            //material flag
            actualMaterial=line.substr(7);
        }
        
        else if (line.substr(0,3)=="vt ")
        {                //textures
            actualMaterial="";
            std::istringstream v(line.substr(3));
            int i=0;
            
            vector <double> values(3);
            while (v.good())
            {
                string s;
                v>>s;
                values[i]=atof(s.c_str());
                i++;
            }
            if (i==2)               //Non è stata esportata la terza coordinata
                values[2]=0;
            textures.push_back(values);
        }
        
        else if (line.substr(0,3)=="vn ")
        {
            actualMaterial="";
            std::istringstream v(line.substr(3));
            int i=0;
            
            vector <double> values(3);
            while (v.good())
            {
                string s;
                v>>s;
                values[i]=atof(s.c_str());
                i++;
            }
            normals.push_back(values);
        }
        
        else if(line.substr(0,2)=="f ")
        {
            
            Face *f=new Face ();
            
            if (actualMaterial!="")
            {
                //Find the pointer to the right material
                for (int i=0;i<materials->size();i++)
                {
                    Material *m=(*materials)[i];
                    if (m->getName()==actualMaterial)
                    {
                        cout<<"Nomi "<<m->getName();
                        f->setMaterial(m);
                        break;
                    }
                    
                }
            }
            
            std::istringstream v(line.substr(2));
            while (v.good())            //spaces
            {
                
                string s;
                v>>s;
                if (s.find_first_not_of(' ') == std::string::npos)
                    continue;
                
                size_t pos = s.find("/");
                size_t pos2=string::npos;
                
                string vertexInd=s;
                int textureIndex=0;
                int normIndex=0;
                if (pos!=string::npos)
                {
                    string textureInd=s.substr (pos+1);
                    vertexInd=s.substr(0, pos);
                    
                    pos2=s.find("/", pos+1);
                    
                    if (pos2!=string::npos)
                    {
                        string normInd=s.substr(pos2+1);
                        textureInd=s.substr(pos+1, pos2);
                        
                        normIndex=atof(normInd.c_str())-1;
                    }
                    
                    textureIndex=atof(textureInd.c_str())-1;
                }
                
                int pointIndex=atof(vertexInd.c_str())-1;
                
                if (pos!=string::npos)
                {
                   // cout<<"\npointIndex"<<pointIndex<<"\ntextureIndex: "<<textureIndex<<"\n";
                    points[pointIndex]->setUvw(textures[textureIndex][0], textures[textureIndex][1], textures[textureIndex][2]);
                    if (pos2!=string::npos)
                    {
                        points[pointIndex]->setNormal(normals[normIndex][0], normals[normIndex][1], normals[normIndex][2]);
                    }
                    
                }
                
                f->addPoint(points[pointIndex]);
                
            }
            faces->push_back(f);
            cout<<"dim   "<<faces->size();
        }
    }
    actualMesh->setFaces (faces);
    
   // delete faces;
    return meshes;
}