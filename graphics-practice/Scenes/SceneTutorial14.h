//
//  SceneTutorial13.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 13..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial14__
#define __graphics_practice__SceneTutorial14__

#include "Prefix.h"

class SceneTutorial14 : public Scene {
private:
    float g_rot;
    
public:
    static SceneTutorial14* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    void render_stroke_string(void* font, const char* string);
};

#endif /* defined(__graphics_practice__SceneTutorial14__) */
