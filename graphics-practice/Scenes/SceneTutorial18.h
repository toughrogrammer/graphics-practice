//
//  SceneTutorial18.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial18__
#define __graphics_practice__SceneTutorial18__

#include "Prefix.h"

class SceneTutorial18 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    float _xrot, _yrot;
    Cube *_cube;
    GLuint _texture[3];
    int _filter;
    GLUquadric *_quadratic;
    int _objectType;
    int _part1, _part2;
    int _p1, _p2;
    
public:
    static SceneTutorial18* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
};

#endif /* defined(__graphics_practice__SceneTutorial18__) */
