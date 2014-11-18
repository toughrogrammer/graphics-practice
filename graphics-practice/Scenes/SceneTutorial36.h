//
//  SceneTutorial36.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial36__
#define __graphics_practice__SceneTutorial36__

#include "Prefix.h"


class SceneTutorial36 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    
    GLuint blurTexture;
    float vertexes[4][3] = { 0.0f, };										// Holds Float Info For 4 Sets Of Vertices
    float normal[3] = { 0.0f, };											// An Array To Store The Normal Data
    float angle = 0;

    
public:
    static SceneTutorial36* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    GLuint EmptyTexture();
    void ReduceToUnit(float vector[3]);
    void calcNormal(float v[3][3], float out[3]);
    void RenderToTexture();
    void ProcessHelix();
    void ViewOrtho();
    void ViewPerspective();
    void DrawBlur(int times, float inc);
    bool Initialize();
};


#endif /* defined(__graphics_practice__SceneTutorial36__) */
