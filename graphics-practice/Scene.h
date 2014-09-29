//
//  Scene.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Scene__
#define __graphics_practice__Scene__

#include "Prefix.h"

class Scene {
public:
    Scene();
    virtual ~Scene();
    
    static Scene* Create();
    
    virtual bool Init();
    
    virtual void OnEnter();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};

#endif /* defined(__graphics_practice__Scene__) */
