//
//  Parser.h
//  3dEngine
//
//  Created by Massimo Perini on 05/02/14.
//  Copyright (c) 2014 Massimo Perini. All rights reserved.
//

#ifndef ___dEngine__Parser__
#define ___dEngine__Parser__

#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "LoadTexture.h"

vector<Mesh*>* parser (const char * filename);
vector<Material*>* parseMaterial (const char * filename);

#endif /* defined(___dEngine__Parser__) */
