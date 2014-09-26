//
//  Vector2.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Vector2__
#define __graphics_practice__Vector2__

#include "Matrix.h"

class Vector2
{
public:
    float x, y;
    Vector2();
    Vector2(float initx, float inity);
    Vector2(const Vector2& vec);
    ~Vector2();
    
    Vector2 Nomalize(); //´ÜÀ§º¤ÅÍ¸®ÅÏ
    float Length();		//Å©±â°è»ê
    
    Vector2 operator+(const Vector2& vec) const;
    Vector2 operator-(const Vector2& vec) const;
    Vector2 operator-(void) const; //ºÎÈ£º¯°æ
    
    Vector2 operator*(const float scalar) const;
    friend Vector2 operator*(const float scalar, const Vector2& vec);
    Vector2 operator/(const float scalar) const;
    
    float operator*(const Vector2& vec) const; //³»Àû
    
    Vector2& operator+=(const Vector2& vec);
    Vector2& operator-=(const Vector2& vec);
    Vector2& operator*=(const float scalar);
    Vector2& operator/=(const float scalar);
    
    //Çà·Ä°ö¼À
    Vector2 operator*(const Matrix2 m) const;
};

/*
 ºøº¯a
 ¹Øº¯ = a*cos¼¼Å¸
 º¤ÅÍÀÇ ³»ÀûÀº ¾ç¼ö À½¼ö·Î µÎº¤ÅÍ°¡ °°Àº ¹æÇâÀ» ÇâÇÏ°í ÀÖ´ÂÁö ¾Æ´ÑÁö ¾Ë¼öÀÖ´Ù.
 */

#endif /* defined(__graphics_practice__Vector2__) */
