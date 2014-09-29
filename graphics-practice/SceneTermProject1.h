//
//  SceneTermProject1.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTermProject1__
#define __graphics_practice__SceneTermProject1__

#include "Prefix.h"
#include "Scene.h"

class SceneTermProject1 : public Scene {
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    Sprite *_spriteGrass;
    Cube *_cube;
    
    bool _light, _blend;
    
    
public:
    static SceneTermProject1* Create();
    
    virtual bool Init();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    void LogCameraStatus();
};

#endif /* defined(__graphics_practice__SceneTermProject1__) */
