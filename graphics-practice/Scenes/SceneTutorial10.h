//
//  SceneTutorial9.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial10__
#define __graphics_practice__SceneTutorial10__

#include "Prefix.h"


class Vertex {
public:
    float x, y, z;
    float u, v;
};

class Triangle {
public:
    Vertex vertex[3];
};

class Sector {
public:
    int numOfTriangles;
    vector<Triangle> triangles;
};

class SceneTutorial10 : public Scene {
private:
    bool _light, _blend;
    Sector _sector;
    MyImage *_mudImage;
    Vector3 _pos;
    GLfloat	_yrot;
    GLfloat _walkbias;
    GLfloat _walkbiasangle;
    GLfloat _lookupdown;
    
    
public:
    static SceneTutorial10* Create();
    
    virtual bool Init();
    
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    void readstr(FILE *fp, char *string);
    void SetupWorld();
};

#endif /* defined(__graphics_practice__SceneTutorial9__) */
