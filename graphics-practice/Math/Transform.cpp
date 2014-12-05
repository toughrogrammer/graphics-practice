//
//  Transform.cpp
//  graphics-practice
//
//  Created by loki on 2014. 12. 5..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Transform.h"


Matrix4 Transform::Ortho(float left, float right, float bottom, float top, float znear, float zfar)
{
    Matrix4 result(1);
    result.a11 = 2.0 / (right - left);
    result.a22 = 2.0 / (top - bottom);
    result.a33 = 2.0 / (zfar - znear);
    result.a41 = -(right + left) / (right - left);
    result.a42 = -(top + bottom) / (top - bottom);
    result.a43 = -(zfar + znear) / (zfar - znear);
    
    return result;
}

Matrix4 Transform::LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up)
{
    Vector3 f(center - eye);
    f.Normalize();
    Vector3 s(Vector3::Cross(f, up));
    s.Normalize();
    Vector3 u(Vector3::Cross(s, f));
    
    Matrix4 result(1);
    result.a11 = s.x;
    result.a21 = s.y;
    result.a31 = s.z;
    
    result.a12 = u.x;
    result.a22 = u.y;
    result.a32 = u.z;
    
    result.a13 = -f.x;
    result.a23 = -f.y;
    result.a33 = -f.z;
    
    result.a41 = -s.DotProduct(eye);
    result.a42 = -u.DotProduct(eye);
    result.a43 = f.DotProduct(eye);
    
    return result;
}