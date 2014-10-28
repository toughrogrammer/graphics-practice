//
//  Color4f.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Color4f__
#define __graphics_practice__Color4f__

#include "Prefix.h"

class Color4f
{
public:
    float _r, _g, _b, _a;
    
    Color4f();
    Color4f(float r, float g, float b, float a);
    
    void Set(float r, float g, float b, float a);
    
    Color4f operator+(const Color4f& vec) const;
    Color4f operator-(const Color4f& vec) const;
    Color4f& operator+=(const Color4f& vec);
    Color4f& operator-=(const Color4f& vec);

};

#endif /* defined(__graphics_practice__Color4f__) */
