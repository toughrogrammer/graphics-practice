//
//  SceneTutorial31.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 7..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial31__
#define __graphics_practice__SceneTutorial31__

#include "Prefix.h"


class SceneTutorial31 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    ModelMilkshape3D *model;
    
    float yrot = 0.0f;
    float yrotspeed = 5.0f;
    
public:
    static SceneTutorial31* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};


#endif /* defined(__graphics_practice__SceneTutorial31__) */
