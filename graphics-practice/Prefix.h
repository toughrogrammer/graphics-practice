//
//  prefix.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef graphics_practice_prefix_h
#define graphics_practice_prefix_h

// std header
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

// opengl
#if defined(__APPLE__) && defined(__MACH__)
/* Apple OSX and iOS (Darwin). ------------------------------ */
#include <TargetConditionals.h>
#if TARGET_OS_MAC == 1
/* OSX */
#include <GLUT/glut.h>
#endif
#endif

#if defined(__linux__)
#include <GL/gl.h>
#endif

#include "SOIL.h"


// my headers
#include "Macro.h"

#include "Vector3.h"
#include "Vector2.h"
#include "Matrix.h"

#include "Action.h"
#include "ActionInterval.h"
#include "ActionManager.h"

#include "Scene.h"
#include "SceneManager.h"

#include "Node.h"
#include "MyImage.h"
#include "Sprite.h"
#include "Cube.h"

#endif
