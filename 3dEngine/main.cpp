//
//  main.cpp
//  3dEngine
//
//  Created by Massimo Perini on 29/01/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#include <iostream>
#include <vector>

#include "mainwindow.h"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qpushbutton.h>

#include <ctime>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//OpenGL
#include <OpenGL/OpenGL.h>//OpenGL Library
/* Windows:
 #include <GL/glut.h>
 */
/* Max OSX  */

//#include <wx/wx.h>

//Classi


#include "Mesh.h"
#include "Render.h"
#include <vector>
#include "Parser.h"
#include "Light.h"
#include <OpenGL/OpenGL.h>

using namespace std;


vector<Mesh*>* fileMeshes;
vector<Mesh*>* skybox;
vector<Light*> lights;

/*
 TODO:
  Finire rendering e caricamento materiali --OK
 - Finire GUI  --- ??? Gli shader non supportano il cambiamento delle luci --sistemato
 - Shadow map  migliorare il puntinato  OK
 - Global Illumination (Irradiance Cache)
 - Carico distribuito
 - utilizzo mouse e miglioramento controllo camera OK
 - skybox  OK
 */

void initApplication()
{
    fileMeshes=parser("/Users/Massimo/Documents/maturita'/testFiles/stradaNew.obj");
    skybox=parser("/Users/Massimo/Documents/maturita'/testFiles/skybox.obj");
 //   skybox=new vector <Mesh *>;
    Light *l=new Light ("luce 1");
    
    l->setPosition(1, 1, 1, 1);                //Non cambiare w della luce o phong la muovera' con la camera stackoverflow.com/questions/15930638/opengl-point-light-moving-when-camera-rotates
    l->setDiffuse(0.5, 0.5, 0.5, 0);
    l->setAmbient(0.6, 0.6, 0.6, 0);
    l->setSpecular(0.8, 0.8, 0.8, 0);
    
    lights.push_back(l);
}


int main(int argc, char * argv[])
{
    int windowHeight=800;
    int windowWidth=800;
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ACCUM | GLUT_MULTISAMPLE | GLUT_STENCIL);
    
    glutInitWindowSize(windowWidth, windowHeight);
    glutPositionWindow(0,0);
    glutCreateWindow("Debug");

    
    initApplication();
    
    Render r=Render::get_instance(*fileMeshes, &lights, *skybox, windowWidth, windowHeight);
    
    
    QApplication a(argc, argv);
    MainWindow w (&lights, &r);
    w.show();
    
    a.exec();
    
    r.startLoop();
    
    
    return 0;
}

