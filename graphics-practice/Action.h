//
//  Action.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Action__
#define __graphics_practice__Action__

#include <stdlib.h>
#include "Node.h"

class Node;

class Action {
protected:
    Node *_target;
    float _time;
    
public:
    Action(float time);
    virtual ~Action();
    
    virtual void SetTarget(Node *target);
    virtual void Start();
    virtual void Update(float dt);
};

#endif /* defined(__graphics_practice__Action__) */
