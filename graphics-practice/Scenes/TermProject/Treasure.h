//
//  Treasure.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Treasure__
#define __graphics_practice__Treasure__

#include "Prefix.h"

class Treasure : public Node
{
private:
    float _opacity;
    Cube *_model;

    int _step;
    float _timer;
    
public:
    static Treasure* Create(const char* texturePath);
    
    bool InitWithPath(const char* path);
    virtual void Update(float dt);
    virtual void Draw();
    
    void Taked();
    bool IsOnAnimating();
    bool IsFinishedAnimating();
};

#endif /* defined(__graphics_practice__Treasure__) */
