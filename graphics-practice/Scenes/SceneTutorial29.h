//
//  SceneTutorial29.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial29__
#define __graphics_practice__SceneTutorial29__

#include "Prefix.h"


class SceneTutorial29 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    MyImage *img1, *img2;
    GLuint texture;
    float xrot = 0;
    float yrot = 0;
    float zrot = 0;
    
public:
    static SceneTutorial29* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};


#endif /* defined(__graphics_practice__SceneTutorial29__) */
