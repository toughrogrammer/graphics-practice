//
//  SceneTutorial25.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial25__
#define __graphics_practice__SceneTutorial25__

#include "Prefix.h"


class SceneTutorial25 : public Scene
{
private:
    class Object {
    public:
        vector<Vector3> _points;
    };

private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;

    Object morph1, morph2, morph3, morph4, helper;
    Object *sour, *dest;
    int maxver = 0;
    int step = 0;
    int steps = 200;
    
    bool morph = false;
    int curr = 0;
    
    
public:
    static SceneTutorial25* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);

    void LoadObject(string path, Object &obj);
    Vector3 Calculate(int i);
};


#endif /* defined(__graphics_practice__SceneTutorial25__) */
