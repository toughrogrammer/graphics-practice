//
//  SceneTutorial13.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial13__
#define __graphics_practice__SceneTutorial13__

#include "Prefix.h"

class SceneTutorial13 : public Scene {
private:
    
public:
    static SceneTutorial13* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    void Enter2d();
    void Exit2d();
};

#endif /* defined(__graphics_practice__SceneTutorial13__) */
