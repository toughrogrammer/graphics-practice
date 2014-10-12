//
//  Matrix2.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Matrix2__
#define __graphics_practice__Matrix2__

class Matrix2
{
public:
    float a11, a12;
    float a21, a22;
    
    Matrix2();
    Matrix2(float m11, float m12, float m21, float m22);
    ~Matrix2(){};
    
    void Identity();  //´ÜÀ§Çà·Ä
    void Transpose(); //ÀüÄ¡Çà·Ä
    void Inverse();   //¿ªÇà·Ä
    
    Matrix2 operator+(const Matrix2 &m) const;
    Matrix2 operator-(const Matrix2 &m) const;
    Matrix2 operator*(const Matrix2 &m) const;
    Matrix2 operator*(const float scalar) const;
    friend Matrix2 operator*(const float scalar, const Matrix2 &m);//Àü¿ª¿¬»êÀÚ¿À¹ö·Îµù
    
    void operator+=(const Matrix2 &m);
    void operator-=(const Matrix2 &m);
    void operator*=(const Matrix2 &m); //Çà·Ä¿ä¼Ò °¢°¢À» ³»Àû°è»ê
    void operator*=(const float scalar);
};


#endif /* defined(__graphics_practice__Matrix2__) */
