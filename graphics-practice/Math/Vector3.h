//
//  Vector3.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Vector3__
#define __graphics_practice__Vector3__

#include "Vector2.h"
#include "Matrix.h"

class Vector3
{
public:
    float x, y, z;
    Vector3();
    Vector3(float initx, float inity, float initz);
    Vector3(const Vector2& vec);
    ~Vector3();
    
    void Normalize();
    static Vector3 Normalize(Vector3 v);
    float Length();
    void Init();
    void Set(float sx, float sy, float sz);
    float DotProduct(const Vector3& vec) const;
    float Magnitude() const;
    
    Vector3 operator+(const Vector3& vec) const;
    Vector3 operator-(const Vector3& vec) const;
    Vector3 operator-(void) const;
    
    Vector3 operator*(const float scalar) const;
    friend Vector3 operator*(const float scalar, const Vector3& vec);
    Vector3 operator/(const float scalar) const;
    
    float operator*(const Vector3& vec) const;
    Vector3 operator^(const Vector3& vec) const;
    
    Vector3& operator+=(const Vector3& vec);
    Vector3& operator-=(const Vector3& vec);
    Vector3& operator*=(const float scalar);
    Vector3& operator/=(const float scalar);
    
    Vector3 operator*(const Matrix3 m) const;
};

#endif /* defined(__graphics_practice__Vector3__) */
