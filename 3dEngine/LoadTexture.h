//
//  LoadTexture.h
//  3dEngine
//
//  Created by Massimo Perini on 25/04/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__LoadTexture__
#define ___dEngine__LoadTexture__

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

GLuint loadTexture( const char * filename);
void FreeTexture( GLuint texture );


#endif /* defined(___dEngine__LoadTexture__) */
