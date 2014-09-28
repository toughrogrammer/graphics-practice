//
//  Node.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Node__
#define __graphics_practice__Node__

#include <OpenGL/OpenGL.h>
#include "Macro.h"
#include "Vector3.h"

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
    
    virtual void SetPosition(Vector3 vec);
    virtual void SetRotation(Vector3 vec);
};

#endif /* defined(__graphics_practice__Node__) */
