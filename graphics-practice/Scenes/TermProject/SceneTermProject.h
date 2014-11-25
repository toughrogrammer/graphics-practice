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

#include "MyLight.h"

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
    
    bool _isFog = false;
    
    const float DAY_FACTOR = 0.2f;
    const float SUN_RADIUS = 100.0f;
    MyLight _sun;
    float _time = 0;
    
    MyLight _controlLight;
    bool _isMoveLight = true;
    float _moveLightkeyDelay = 0.3f;
    string _stringLightPosition;
    
    
    ModelObj _model;

    
public:
    static SceneTermProject* Create();
    
    SceneTermProject();
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    void CameraMove(float dt);
    void Enter2d();
    void Exit2d();
    void UpdateFogByState();
};

#endif /* defined(__graphics_practice__SceneTermProject__) */
