//
//  Vector2.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Vector2.h"

#include <math.h>

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float initx, float inity)
{
    x = initx;
    y = inity;
}

Vector2::Vector2(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
}

Vector2::~Vector2()
{
    
}

float Vector2::Length()
{
    return float(sqrt(x*x + y*y));
}

Vector2 Vector2::Nomalize()
{
    float fLength = 0.0f;
    fLength = Length();
    return (Vector2(x/fLength, y/fLength));
}

//¿¬»êÀÚ¿À¹ö·Îµù
//+,-
Vector2 Vector2::operator+(const Vector2& vec) const
{
    return Vector2(x+vec.x, y+vec.y);
}
Vector2 Vector2::operator-(const Vector2& vec) const
{
    return Vector2(x-vec.x, y-vec.y);
}
Vector2 Vector2::operator-(void) const //ºÎÈ£º¯°æ
{
    return Vector2(-x, -y);
}

//*,/
Vector2 Vector2::operator*(const float scalar) const
{
    return Vector2(scalar*x, scalar*y);
}
Vector2 Vector2::operator/(const float scalar) const
{
    return Vector2(x/scalar, y/scalar);
}
Vector2 operator*(const float scalar, const Vector2& vec)//Àü¿ª¿¬»êÀÚ¿À¹ö·Îµù
{
    return Vector2(scalar * vec.x, scalar * vec.y);
}

//³»Àû
float Vector2::operator*(const Vector2& vec) const
{
    return x*vec.x + y*vec.y;
}

//º¹ÇÕ´ëÀÔ¿¬»êÀÚ
Vector2& Vector2::operator+=(const Vector2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}
Vector2& Vector2::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2& Vector2::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

//Çà·Ä°ö¼À
Vector2 Vector2::operator*(const Matrix2 m) const
{
    Vector2 temp;
    
    temp.x = x * m.a11 + y * m.a21; 
    temp.y = x * m.a12 + y * m.a22; 
    
    return temp; 
}