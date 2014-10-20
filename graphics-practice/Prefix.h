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

#include <math.h>


// opengl
#if defined(__APPLE__) && defined(__MACH__)
/* Apple OSX and iOS (Darwin). ------------------------------ */
#include <TargetConditionals.h>
#if TARGET_OS_MAC == 1
/* OSX */
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#endif
#endif

#if defined(__linux__)
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include "SOIL.h"


// my headers
#include "Util/Macro.h"

#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Math/Matrix.h"

#include "Util/Keyboard.h"

// action
#include "Base/Action.h"
#include "Base/ActionInterval.h"
#include "Base/ActionManager.h"

// scene
#include "Base/Scene.h"
#include "Base/SceneManager.h"

// base
#include "Base/Node.h"
#include "Base/MyImage.h"
#include "Base/Sprite.h"
#include "Base/Cube.h"

#endif
