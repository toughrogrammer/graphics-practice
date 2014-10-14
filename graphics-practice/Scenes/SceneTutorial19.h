//
//  SceneTutorial19.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial19__
#define __graphics_practice__SceneTutorial19__

#include "Prefix.h"

class Particle
{
public:
    bool _active;
    float _life;
    float _fade;
    float _r, _g, _b;
    Vector3 _position;
    Vector3 _movement;
    Vector3 _gravity;
};

class SceneTutorial19 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    MyImage *_particleImage;
    vector<Particle*> _particles;
    
public:
    static SceneTutorial19* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
};

#endif /* defined(__graphics_practice__SceneTutorial19__) */
