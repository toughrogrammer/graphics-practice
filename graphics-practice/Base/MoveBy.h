//
//  MoveBy.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__MoveBy__
#define __graphics_practice__MoveBy__

#include "Action.h"
#include "../Math/Vector3.h"

class Node;

class MoveBy : public Action {
private:
    Vector3 _dist;
    Vector3 _start;
    float _duration;
    
public:
    MoveBy(float duration, Vector3 dist);
    virtual ~MoveBy();
    
    static MoveBy* Create(float duration, Vector3 vec);
    
    virtual void SetTarget(Node *target);
    virtual void Update(float dt);
};

#endif /* defined(__graphics_practice__MoveBy__) */
