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

class SceneTermProject2 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    Sprite *_floorSprite;
    Cube *_cube;
    vector<Cube*> _cubes;
    
    float WalkingSpeed;

    
public:
    static SceneTermProject2* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    void CameraMove(float dt);
};

#endif /* defined(__graphics_practice__SceneTermProject2__) */
