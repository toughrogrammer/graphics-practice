//
//  GL.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 8..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef graphics_practice_GL_h
#define graphics_practice_GL_h

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
#include <GL/glut.h>
#include <GL/glext.h>
#endif

#endif
