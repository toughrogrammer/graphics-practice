//
//  SceneTutorial34.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial34__
#define __graphics_practice__SceneTutorial34__

#include "Prefix.h"


class SceneTutorial34 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    unsigned char* mapData;
    const int MAP_SIZE = 1024;
    const int STEP_SIZE = 16;
    const float HEIGHT_RATIO = 1.5f;
    bool bRender = true;
    float scaleValue = 0.15f;
    
public:
    static SceneTutorial34* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    bool LoadRawFile(string path, int size, unsigned char* map);
    int GetHeight(unsigned char* map, int x, int y);
    void SetVertexColor(unsigned char* map, int x, int y);
    void RenderHeightMap(unsigned char* map);
};


#endif /* defined(__graphics_practice__SceneTutorial34__) */
