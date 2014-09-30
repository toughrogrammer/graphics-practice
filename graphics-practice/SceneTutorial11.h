//
//  SceneTutorial9.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial11__
#define __graphics_practice__SceneTutorial11__

#include "Prefix.h"
#include "Scene.h"


class SceneTutorial11 : public Scene {
private:
    bool _light, _blend;
    Vector3 _cameraRotation;
    MyImage *_imgTim;
    vector< vector< vector<float> > > _points;
    int _wiggle_count;

    
public:
    static SceneTutorial11* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};

#endif /* defined(__graphics_practice__SceneTutorial9__) */
