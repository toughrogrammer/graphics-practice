//
//  SceneTermProject.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTermProject__
#define __graphics_practice__SceneTermProject__

#include "Prefix.h"

class Treasure;
class SceneTermProject : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    Sprite *_floorSprite;
    vector<Treasure*> _treasures;
    
    float WalkingSpeed;
    float _takingDelay;
    string _stringGainTreasure;

    
public:
    static SceneTermProject* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    void CameraMove(float dt);
    void Enter2d();
    void Exit2d();
};

#endif /* defined(__graphics_practice__SceneTermProject__) */
