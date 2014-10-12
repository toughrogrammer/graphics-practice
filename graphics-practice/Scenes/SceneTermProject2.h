//
//  SceneTermProject2.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTermProject2__
#define __graphics_practice__SceneTermProject2__

#include "Prefix.h"

class Treasure;
class SceneTermProject2 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    Sprite *_floorSprite;
    vector<Treasure*> _treasures;
    
    float WalkingSpeed;
    float _takingDelay;
    string _stringGainTreasure;

    
public:
    static SceneTermProject2* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    void CameraMove(float dt);
    void Enter2d();
    void Exit2d();
};

#endif /* defined(__graphics_practice__SceneTermProject2__) */
