//
//  Macro.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Macro.h"


void GLVertexByVector3(Vector3 &v)
{
    glVertex3f( v.x, v.y, v.z );
}