//
//  Macro.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef graphics_practice_Macro_h
#define graphics_practice_Macro_h

#include <OpenGL/gl.h>
#include "../Math/Vector3.h"

#include <sys/time.h>

#define SAFE_DELETE(p) if( (p) != NULL ) delete (p); (p) = NULL;

void GLVertexByVector3(Vector3 &v);
long GetMillisecond(struct timeval tv);


#endif
