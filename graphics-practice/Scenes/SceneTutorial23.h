//
//  SceneTutorial23.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial23__
#define __graphics_practice__SceneTutorial23__

#include "Prefix.h"


class SceneTutorial23 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    
    GLUquadricObj *quadratic;
    int object;
    
    MyImage *imgBackground;
    MyImage *imgReflect;
    Vector3 rotObject;
    
public:
    static SceneTutorial23* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    void glDrawCube();
};


#endif /* defined(__graphics_practice__SceneTutorial23__) */
