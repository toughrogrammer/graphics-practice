//
//  SceneTutorial12.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial12__
#define __graphics_practice__SceneTutorial12__

#include "Scene.h"

class SceneTutorial12 : public Scene {
private:
    MyImage *_image;
    GLuint _box, _top;
    float _xrot, _yrot;
    
    
public:
    static SceneTutorial12* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    void BuildLists();
};

#endif /* defined(__graphics_practice__SceneTutorial12__) */
