//
//  Color4f.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Color4f.h"


Color4f::Color4f()
{
    _r = _g = _b = _a = 0;
}

Color4f::Color4f(float r, float g, float b, float a)
{
    Set(r, g, b, a);
}

void Color4f::Set(float r, float g, float b, float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

Color4f Color4f::operator+(const Color4f& color) const
{
    return Color4f(_r + color._r, _g + color._g, _b + color._b, _a + color._a);
}
Color4f Color4f::operator-(const Color4f& color) const
{
    return Color4f(_r - color._r, _g - color._g, _b - color._b, _a - color._a);
}
Color4f& Color4f::operator+=(const Color4f& color)
{
    _r += color._r;
    _g += color._g;
    _b += color._b;
    _a += color._a;
    return *this;
}
Color4f& Color4f::operator-=(const Color4f& color)
{
    _r -= color._r;
    _g -= color._g;
    _b -= color._b;
    _a -= color._a;
    return *this;
}