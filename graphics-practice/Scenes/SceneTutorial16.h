//
//  SceneTutorial16.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 13..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial16__
#define __graphics_practice__SceneTutorial16__

#include "Prefix.h"

class SceneTutorial16 : public Scene {
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    Cube *_box;
    
public:
    static SceneTutorial16* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
};

#endif /* defined(__graphics_practice__SceneTutorial16__) */
