//
//  Render.h
//  3dEngine
//
//  Created by Massimo Perini on 03/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Render__
#define ___dEngine__Render__

#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

#include "Shader.h"


using namespace std;

class Render
{
private:
    static vector<Mesh*> meshes;
    static vector <Camera*> cameras;
    static vector <Light*>* lights;
    static vector<Mesh*> skyBox;
    static int screenW;
    static int screenH;
    static int xOrigin;
    static int yOrigin;
    static bool leftClick;
    static int defScreenW;
    static int defScreenH;
    
    static void initOpengl();
    static void reshape(int width, int height);
    static void specialKeys( int key, int x, int y );
    static void keyPressed(unsigned char Key, int x, int y);
    static void mouseClick (int button, int state, int x, int y);
    static void mouseMove(int x, int y);
    static void animate ();
    static void display();
    static void drawObj(vector <Mesh*> meshes);
    static void setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z);
    
    static void manageJoystick(unsigned int buttons, int xaxis, int yaxis, int zaxis);
    static void setTextureMatrix(void);
    static void generateShadowFBO();
    
    static Shader shader;
    
    //implementare singleton
   //
    Render(vector <Mesh*> meshes, vector <Light*>* lights, vector <Mesh*> skybox, int screenWidth, int screenHeight);

    
public:
    //
    static Render& get_instance(vector <Mesh*> fMeshes, vector <Light*>* lights, vector <Mesh*> skybox, int screenWidth, int screenHeight);

    static void startLoop ();
    static void render ();
    static void setLights ();

};

#endif /* defined(___dEngine__Render__) */
