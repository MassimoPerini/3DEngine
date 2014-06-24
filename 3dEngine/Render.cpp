//
//  Render.cpp
//  3dEngine
//
//  Created by Massimo Perini on 03/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//


/*
 Parameter Name  Default Value          Meaning
 
 GL_AMBIENT      (0.0, 0.0, 0.0, 1.0)   ambient RGBA intensity of light
 
 GL_DIFFUSE      (1.0, 1.0, 1.0, 1.0)   diffuse RGBA intensity of light
 
 GL_SPECULAR     (1.0, 1.0, 1.0, 1.0)   specular RGBA intensity of light
 
 GL_POSITION     (0.0, 0.0, 1.0, 0.0)   (x, y, z, w) position of light
 
 GL_SPOT_DIRECTION   (0.0, 0.0, -1.0)   (x, y, z) direction of spotlight
 
 GL_SPOT_EXPONENT    0.0                spotlight exponent
 
 GL_SPOT_CUTOFF     180.0               spotlight cutoff angle
 
 GL_CONSTANT_ATTENUATION    1.0         constant attenuation factor
 
 GL_LINEAR_ATTENUATION      0.0         linear attenuation factor
 GL_QUADRATIC_ATTENUATION   0.0         quadratic attenuation factor
 
 */

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

// Expressed as float so gluPerspective division returns a float and not 0 (640/480 != 640.0/480.0).
#define RENDER_WIDTH 2000.0
#define RENDER_HEIGHT 2000.0
#define SHADOW_MAP_RATIO 2
GLuint fboId;

// Z values will be rendered to this texture when using fboId framebuffer
GLuint depthTextureId;


#include "Render.h"
#include <vector>
#include "Mesh.h"
#include <string>
#include "Face.h"
#include "Point.h"
#include "Camera.h"
#include "Light.h"
#include "LoadTexture.h"

#include "shader.h"


using namespace std;

int Render::defScreenW=800;
int Render::defScreenH=800;
int Render::screenW=800;
int Render::screenH=800;
//camera settings
int Render::xOrigin = -1;
int Render::yOrigin = -1;
bool Render::leftClick=false;


vector<Mesh*> Render::meshes=*new vector<Mesh*>;
vector<Mesh*> Render::skyBox=*new vector<Mesh*>;
vector <Camera*> Render::cameras=*new vector<Camera*>;
vector <Light*>* Render::lights;

Shader Render::shader;
GLuint texture;
GLuint txtSkyBox [6];
GLuint uiVAO;
GLuint shadowMapUniform;

#pragma mark Remeber to add new attributes

Render& Render::get_instance(vector <Mesh*> fMeshes, vector <Light*>* lights, vector <Mesh*> skybox, int screenWidth, int screenHeight)
{
    static Render instance (fMeshes, lights, skybox, screenWidth, screenHeight); // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;

}

Render::Render(vector <Mesh*> fMeshes, vector <Light*>* vLights,vector <Mesh*> skybox, int screenWidth, int screenHeight)
{
    lights=vLights;
    meshes=fMeshes;
    screenW=screenWidth;
    screenH=screenHeight;
    defScreenH=screenH;
    defScreenW=screenW;
    skyBox=skybox;
    initOpengl();
}


void Render::drawObj(vector <Mesh*> meshes)
{
    for (int i = 0; i < meshes.size();i++)
    {
        Mesh *mesh=meshes[i];
        vector <Face*>*faces=mesh->getFaces();
        
        glActiveTexture(GL_TEXTURE0);
        int texture_location = glGetUniformLocation(shader.id(), "texture_color");
        glUniform1i(texture_location, 0);
        
        
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        
        
        for (int k=0;k<(faces)->size();k++)
        {
            Face *fac=(*faces)[k];
            
#pragma mark inizio materiali
            if (NULL!=(fac->getMaterial())){
                Material *mat=(fac->getMaterial());
                
                glClearColor (0.0, 0.0, 0.0, 0.0);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat->getDiffuse());
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat->getSpecular());
                GLfloat mat_shininess[] = { 1.0 };
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
                
                if ((mat->hasDiffuseMap())){
                    glBindTexture(GL_TEXTURE_2D, *(mat->getDiffuseMap()));
                }
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, NULL);
            }
            
            
            glBegin(GL_POLYGON);
            
            vector <Point*> *points=(*fac).getPoints();
            for (int j=0;j<(points)->size();j++)
            {
                glNormal3d((*points)[j]->getNormal()[0], (*points)[j]->getNormal()[1], (*points)[j]->getNormal()[2]);
                glTexCoord2d((*points)[j]->getUvw()[0], (*points)[j]->getUvw()[1]);
                glVertex3d((*points)[j]->getTuple()[0], (*points)[j]->getTuple()[1], (*points)[j]->getTuple()[2]);
                
            }
            glEnd();
            
            
        }
    }
}


void Render::setupMatrices(float position_x,float position_y,float position_z,float lookAt_x,float lookAt_y,float lookAt_z)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,screenW/screenH,10,40000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position_x,position_y,position_z,lookAt_x,lookAt_y,lookAt_z,0,1,0);
}

void Render::setTextureMatrix(void)
{
	static double modelView[16];
	static double projection[16];
	
	// This is matrix transform every coordinate x,y,z
	// x = x* 0.5 + 0.5
	// y = y* 0.5 + 0.5
	// z = z* 0.5 + 0.5
	// Moving from unit cube [-1,1] to [0,1]
	const GLdouble bias[16] = {
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0};
	
	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	
	glLoadIdentity();
	glLoadMatrixd(bias);
	
	// concatating all matrice into one.
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void Render::display()
{
    //TODO: Regolare dimensioni
    
    /* clear the color buffer (resets everything to black) */
    //----------------
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fboId);	//Rendering offscreen
    glUseProgramObjectARB(0);
	glViewport(0,0,screenW * SHADOW_MAP_RATIO,screenH* SHADOW_MAP_RATIO);
//----------
    
    glClearStencil(0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//---------
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    
    for (int i=0;i<(*lights).size();i++)
    {
        Light *lShadow=(*lights)[0];
        setupMatrices(lShadow->getPosition()[0],lShadow->getPosition()[1],lShadow->getPosition()[2],0,0,0);
	
        // Culling switching, rendering only backface, this is done to avoid self-shadowing
        glCullFace(GL_FRONT);
        drawObj(meshes);
        setTextureMatrix();
    }
    
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	
	glViewport(0,0,screenW,screenH);
	
	//Enabling color write (previously disabled for light POV z-buffer rendering)
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	// Clear previous frame values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shadowMapUniform=shader.bind();
    glUniform1iARB(shadowMapUniform,7);
	glActiveTextureARB(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,depthTextureId);

    
    //----------
    /* set the current drawing color to red */
    
    glDisable(GL_CULL_FACE);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cameras[0]->insideCamera();
    
//    float posLight []={0,0,-3,0};
    
//    glLightfv(GL_LIGHT0, GL_POSITION, posLight);
    
    //start lights
    
    
 //   glEnable(GL_LIGHTING);
    
    
    
  
    //----------------------------------
    
    int oGLLights []={GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
    GLfloat reset [4]={0,0,0,0};
    for (int i=0;i<8;i++)
    {
        glLightfv(oGLLights[i], GL_POSITION, reset);
        glLightfv(oGLLights[i], GL_AMBIENT, reset);
        glLightfv(oGLLights[i], GL_DIFFUSE, reset);
        glDisable(oGLLights[i]);
    }
    
    unsigned long k=8;
    if (lights->size()<k)
    {
        k=lights->size();
    }
    
    for (unsigned int i=0;i<k;i++)
    {
        Light *l=(*lights)[i];
        glLightfv(oGLLights[i], GL_POSITION, (l->getPosition()));
        glLightfv(oGLLights[i], GL_AMBIENT, l->getAmbient());
        glLightfv(oGLLights[i], GL_DIFFUSE, l->getDiffuse());
        
        glEnable(oGLLights[i]);
    }
    
    //end lights
    
    //glColor3f(1.0, 0.0, 0.0);
    
    //SKYBOX
    
/*    glDepthMask(0);
    glBindVertexArrayAPPLE(texture);
    for(int i=0; i<6;i++)
    {
        glBindTexture(<#GLenum target#>, <#GLuint texture#>)
        tTextures[i].bindTexture();
        glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
    }
    glDepthMask(1);
*/
    
    
    //---------
    
    drawObj(meshes);
    
    shader.unbind();
    
    glDisable(GL_LIGHTING);
    
    drawObj(skyBox);
    
    glFlush();
    glutSwapBuffers();
 //

}

void Render::render ()
{
    glutPostRedisplay();
}

void Render::animate ()
{
}

void Render::keyPressed(unsigned char Key, int x, int y)
{
    switch (Key){
        case 27:
            //exit
            exit(0);
            break;
    
        case 'f':
            glutFullScreen();
            break;
    
        case 'g':
            glutPositionWindow(0,0);
            glutReshapeWindow(defScreenW, defScreenH);
            break;
    
        case '1':
            cameras[0]->MoveForward(-3);
            break;
            
        case '2':
            cameras[0]->MoveForward(3);
            break;
            
        case '3':
            cameras[0]->RotateZ(0.2);
            break;
            
        case '4':
            cameras[0]->RotateZ(-0.2);
            break;
            
    }
    glutPostRedisplay();

}

void Render::specialKeys( int key, int x, int y ) {
 
#pragma mark gestire + telecamere

    
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT){
        cameras[0]->StrafeRight(3);       //pan right
    }
    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT){
        cameras[0]->StrafeRight(-3);
    }
    else if (key == GLUT_KEY_UP){
        cameras[0]->MoveUpward(3);
    }
    
    else if (key == GLUT_KEY_DOWN){
        cameras[0]->MoveUpward(-3);
    }
    //  Request display update
    glutPostRedisplay();
    
}

void Render::mouseClick (int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        
		// when the button is released
		if (state == GLUT_UP) {
			xOrigin = -1;
            yOrigin=-1;
            leftClick=false;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
            yOrigin = y;
            leftClick=true;
		}
	}
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP) {
			xOrigin = -1;
            yOrigin=-1;
		}
		else  {// state = GLUT_DOWN
			yOrigin = y;
		}
    }
}
void Render::mouseMove(int x, int y) {
    if (leftClick) {
        double how=(x-xOrigin)+(y-yOrigin);
        cameras[0]->RotateX(how*0.01);
	}
    else if (yOrigin >=0)
    {
        double how=(x-xOrigin)+(y-yOrigin);
        cameras[0]->RotateY(how*0.005);
    }

    glutPostRedisplay();
}

void Render::manageJoystick(unsigned int buttons, int xaxis, int yaxis, int zaxis)
{
    cout<<"X"<<xaxis<<"\n";
    cout<<"Y"<<yaxis<<"\n";
    cout<<"Z"<<zaxis<<"\n";
    if (buttons!=0x0000)
    {
    switch (buttons) {
        case GLUT_JOYSTICK_BUTTON_A:
            break;
        case GLUT_JOYSTICK_BUTTON_B:
            break;
        case GLUT_JOYSTICK_BUTTON_C:
            break;
        case GLUT_JOYSTICK_BUTTON_D:
            break;
        case 0x0100:           //L2
            cameras[0]->MoveUpward(-0.4);
            break;
        case 0x0200:    //R2
            cameras[0]->MoveUpward(0.4);
            break;
        case 0x0400:       //L1
            cameras[0]->RotateZ(-0.3);
            break;
        case 0x0800:        //R1
            cameras[0]->RotateZ(0.3);
            break;
        case 0x1000:    //triangolo
            break;
        case 0x2000:    //Cerchio
            cameras[0]->RotateY(-0.4);
            break;
        case 0x4000:    //Croce
            cameras[0]->RotateY(0.4);
            break;
        case 0x8000:       //Quadrato
            break;
    }
        glutPostRedisplay();

    }
    else if ((xaxis != -1000 && yaxis != -1000 && zaxis != -1000))
    {
        if (xaxis < 40 || xaxis > 300){
            cameras[0]->StrafeRight((xaxis-90)*0.0008);
        }
        if (yaxis < -200 || yaxis > 100){
            cameras[0]->MoveForward((yaxis-90)*0.0008);
        }
        if (zaxis < -100 || zaxis > 100){
            cameras[0]->RotateX(zaxis*0.0008);
        }
            glutPostRedisplay();
        }
}

void Render::reshape(int width, int height)
{
    /* tell OpenGL we want to display in a recangle that is the
     same size as the window
     */
    glViewport(0,0,width,height);
    
    /* switch to the projection matrix */
    //   glMatrixMode(GL_PROJECTION);
    
    /* clear the projection matrix */
    glLoadIdentity();
    screenH=height;
    screenW=width;
    
    generateShadowFBO();
    shader.unbind();
 //   shader.init("/Users/Massimo/Documents/maturita'/3dEngine/3dEngine/shader.vert", "/Users/Massimo/Documents/maturita'/3dEngine/3dEngine/shader.frag");
    glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1.0f);
	
	glEnable(GL_CULL_FACE);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    
    glutPostRedisplay();
    
    /* set the camera view, orthographic projection in 2D */
    //    gluOrtho2D(0,width,0,height);
    
    /* switch back to the model view matrix */
    //    glMatrixMode(GL_MODELVIEW);
    
}


void Render::startLoop ()
{
    glutMainLoop();
}



void Render::setLights ()
{
    

    
    GLfloat mat_specular[] = { 0.2, 0.2, 0.2};
    GLfloat mat_shininess[] = { 1.0 };
//    GLfloat light_position[] = { 3.0, 3.0, -3.0, 0.0 };
//    GLfloat lightAmbient[]={1,1,1,1};
//    GLfloat lighDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat redDiffuseMaterial[] = {0.9, 0.9, 0.9};
    
/*    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, redDiffuseMaterial);
*/
    
//    glClearColor (0.0, 0.0, 0.0, 0.0);
    
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
   /* glClearColor (0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redDiffuseMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);*/
    
    int oGLLights []={GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
    
    unsigned long k=8;
    if (lights->size()<k)
    {
        k=lights->size();
    }
    
    for (unsigned int i=0;i<k;i++)
    {
        Light *l=(*lights)[i];
        glLightfv(oGLLights[i], GL_POSITION, (l->getPosition()));
        glLightfv(oGLLights[i], GL_AMBIENT, l->getAmbient());
        glLightfv(oGLLights[i], GL_DIFFUSE, l->getDiffuse());
    
        glEnable(oGLLights[i]);
        
    }
    
//    glColorMaterial(GL_FRONT, GL_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);
//    glColor3d(0.0, 0.0, 1.0);


}

void Render::generateShadowFBO()
{
	int shadowMapWidth = screenW * SHADOW_MAP_RATIO;
	int shadowMapHeight = screenH * SHADOW_MAP_RATIO;
	
	//GLfloat borderColor[4] = {0,0,0,0};
	
	GLenum FBOstatus;
	
	// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	
	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
	//glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );
	
	
	
	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// create a framebuffer object
	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
	
	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, depthTextureId, 0);
	
	// check FBO status
	FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
	
	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void Render::initOpengl()
{
 //   glutInit(&argc, argv);

    // display mode: Red, Green, Blue and Alpha, depth buffer, double buffering
    
/*    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ACCUM | GLUT_MULTISAMPLE);
    
    glutInitWindowSize(screenW, screenH);
    
    glutCreateWindow("Debug");*/
    
    
    /* 		for (jitter = 0; jitter < giNumSamples; jitter++) {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     accPerspective (50.0,
     (GLdouble) viewport[2]/(GLdouble) viewport[3],
     1.0, 15.0, gpJitter[jitter].x, gpJitter[jitter].y, 0.0, 0.0, 1.0);
     displayObjects ();
     glAccum(GL_ACCUM, 1.0/giNumSamples);
     }
     glAccum (GL_RETURN, 1.0);
     } else {
     accPerspective (50.0,
     (GLdouble) viewport[2]/(GLdouble) viewport[3],
     1.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0);
     displayObjects ();
*/
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glEnable(GL_MULTISAMPLE_ARB);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_MULTISAMPLE_ARB);

    GLint  iMultiSample = 0;
    GLint  iNumSamples = 0;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &iMultiSample);
    glGetIntegerv(GL_SAMPLES, &iNumSamples);
    


    
    cout<<"MultiSample "<<iMultiSample;
    
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel (GL_SMOOTH);
//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    generateShadowFBO();
    
    glClearColor(0,0,0,1);
    
    glEnable(GL_LIGHT0);
    
    shader.init("/Users/Massimo/Documents/maturita'/3dEngine/3dEngine/shader.vert", "/Users/Massimo/Documents/maturita'/3dEngine/3dEngine/shader.frag");
    glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1.0f);
	
//	glEnable(GL_CULL_FACE);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    
    /*glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters
    
	//And if you go and use extensions, you can use Anisotropic filtering textures which are of an
	//even better quality, but this will do for now.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
	//Here we are setting the parameter to repeat the texture instead of clamping the texture
	//to the edge of our shape.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );*/
    
    setLights();
    
 //   glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,5);
    
    // callback every time the window needs to be drawn
    
    Camera *c=new Camera(90,screenW/screenH,1.0,1000, true);   //zNear e zFar relativi!! Evitare lo 0
    
    c->setProprieties(30, -30, -5, 90, 90, -90, 0);
    
    cameras.push_back(c);

    
    glEnable(GL_CULL_FACE);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    
    glutDisplayFunc(display);
    
    
    
    // glut reshape callback (window is resized or created
    
    glutReshapeFunc(reshape);
    //callback keyboard
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(specialKeys);
    if (GLUT_HAS_JOYSTICK)
    {
        glutJoystickFunc(manageJoystick, 1);
    }
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    // set the default background color to black
    
    
 //   texture = loadTexture("/Users/Massimo/Documents/maturita'/3dEngine/imgTest.jpg");
    
    
    glutIdleFunc(animate);
}

