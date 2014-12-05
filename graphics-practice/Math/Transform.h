//
//  Transform.h
//  graphics-practice
//
//  Created by loki on 2014. 12. 5..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Transform__
#define __graphics_practice__Transform__

#include "Matrix4.h"
#include "Vector3.h"

class Transform {
public:
    static Matrix4 Ortho(float left, float right, float bottom, float top, float znear, float zfar);
    static Matrix4 LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up);
};


#endif /* defined(__graphics_practice__Transform__) */
