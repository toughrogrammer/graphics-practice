//
//  Matrix3.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Matrix3__
#define __graphics_practice__Matrix3__

class Matrix3
{
public:
    float a11, a12, a13;
    float a21, a22, a23;
    float a31, a32, a33;
    
    Matrix3();
    Matrix3(float m11, float m12, float m13,
            float m21, float m22, float m23,
            float m31, float m32, float m33
            );
    ~Matrix3(){};
    
    void Identity();  //´ÜÀ§Çà·Ä
    void Transpose(); //ÀüÄ¡Çà·Ä
    void Inverse();   //¿ªÇà·Ä
    
    Matrix3 operator+(const Matrix3 &m) const;
    Matrix3 operator-(const Matrix3 &m) const;
    Matrix3 operator*(const Matrix3 &m) const;
    Matrix3 operator*(const float scalar) const;
    friend Matrix3 operator*(const float scalar, const Matrix3 &m);//Àü¿ª¿¬»êÀÚ¿À¹ö·Îµù
    
    void operator+=(const Matrix3 &m);
    void operator-=(const Matrix3 &m);
    void operator*=(const Matrix3 &m); //Çà·Ä¿ä¼Ò °¢°¢À» ³»Àû°è»ê
    void operator*=(const float scalar);
};


#endif /* defined(__graphics_practice__Matrix3__) */
