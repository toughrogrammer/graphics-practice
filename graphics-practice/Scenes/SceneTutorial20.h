//
//  SceneTutorial20.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial20__
#define __graphics_practice__SceneTutorial20__

#include "Prefix.h"


class SceneTutorial20 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    MyImage *_logo, *_img1, *_img2, *_mask1, *_mask2;
    float _roll;
    bool _masking;
    bool _anotherScene;
    
    
public:
    static SceneTutorial20* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};


#endif /* defined(__graphics_practice__SceneTutorial20__) */
