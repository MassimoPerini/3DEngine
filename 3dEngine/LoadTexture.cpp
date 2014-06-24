//
//  LoadTexture.cpp
//  3dEngine
//
//  Created by Massimo Perini on 25/04/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "LoadTexture.h"
#include "SOIL.h"


GLfloat angle = 0.0; //set the angle of rotation

GLuint loadTexture( const char * filename )
{
	std::cout<<"Loading "<<filename<<" texture";
    GLuint tex_2d = SOIL_load_OGL_texture
    (
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
     );
    
    /* check for an error during the load process */
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
//	glGenTextures( 1, &tex_2d ); //generate the texture with the loaded data
    
    
    
    
     
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters
    
	//And if you go and use extensions, you can use Anisotropic filtering textures which are of an
	//even better quality, but this will do for now.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
	//Here we are setting the parameter to repeat the texture instead of clamping the texture
	//to the edge of our shape.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
	return tex_2d; //return whether it was successfull
}

void FreeTexture( GLuint texture )
{
    glDeleteTextures( 1, &texture );
}



