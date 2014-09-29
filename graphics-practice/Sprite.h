//
//  MySprite.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__MySprite__
#define __graphics_practice__MySprite__

#include "Node.h"

class MyImage;

class Sprite : public Node
{
private:
    MyImage *_img;
    
public:
    Sprite(MyImage *img);
    virtual ~Sprite();
    
    static Sprite* Create(const char* path);
    
    virtual void Update(float dt);
    virtual void Draw();
    
};

#endif /* defined(__graphics_practice__MySprite__) */
