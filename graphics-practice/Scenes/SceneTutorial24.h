//
//  SceneTutorial24.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial24__
#define __graphics_practice__SceneTutorial24__

#include "Prefix.h"


class SceneTutorial24 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    MyImage *imageFont;
    GLuint base;
    float scroll;                                         // Used For Scrolling The Screen
    int maxtokens;                                      // Keeps Track Of The Number Of Extensions Supported
    int swidth;                                         // Scissor Width
    int sheight;                                        // Scissor Height
    
    
public:
    static SceneTutorial24* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    void glPrint(GLint x, GLint y, int set, const char *fmt, ...);
    void BuildFont();
    void KillFont();
};


#endif /* defined(__graphics_practice__SceneTutorial24__) */
