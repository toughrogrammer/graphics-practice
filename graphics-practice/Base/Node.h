//
//  Node.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Node__
#define __graphics_practice__Node__

#include "../Math/Vector3.h"

class Action;

class Node {
protected:
    Vector3 _position;
    Vector3 _scale;
    Vector3 _rotation;
    
public:
    Node();
    virtual ~Node();
    
    virtual bool Init();
    virtual void Update(float dt);
    virtual void Draw();
    
    Vector3 GetPosition();
    virtual void SetPosition(Vector3 vec);
    
    Vector3 GetRotation();
    virtual void SetRotation(Vector3 vec);
    
    virtual void RunAction(Action *action);
};

#endif /* defined(__graphics_practice__Node__) */
