//
//  SceneTutorial9.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial9__
#define __graphics_practice__SceneTutorial9__

#include "Prefix.h"


class Star {
public:
    int r, g, b;
    GLfloat dist;
    GLfloat angle;
};

class SceneTutorial9 : public Scene {
private:
    bool _light, _blend;
    MyImage *_starImage;
    vector<Star*> _stars;
    GLfloat	_zoom;
    GLfloat _tilt;
    GLfloat	_spin;
    bool _twinkle;
    
public:
    static SceneTutorial9* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};

#endif /* defined(__graphics_practice__SceneTutorial9__) */
