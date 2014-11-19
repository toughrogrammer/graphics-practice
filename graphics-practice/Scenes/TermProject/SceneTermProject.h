//
//  SceneTermProject.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTermProject__
#define __graphics_practice__SceneTermProject__

#include "Prefix.h"

class Treasure;
class SceneTermProject : public Scene
{
    class Sun {
    public:
        GLenum LightID = GL_LIGHT0;
        GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat LightAttenuation[1] = { 1.3f, };
        GLfloat LightPosition[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        
        const float DAY_FACTOR = 0.1f;
        const float SUN_RADIUS = 100.0f;
        float _time = 0;
        
        Sun();
        void Initialize();
        void SetLightID(GLenum id);
        void SetPosition(float x, float y, float z, float w = 1.0f);
        void Update(float dt);
    };
    
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    Sprite *_floorSprite;
    vector<Treasure*> _treasures;
    
    float WalkingSpeed;
    float _takingDelay;
    string _stringGainTreasure;
    
    bool _isFog = false;
    
    Sun _sun;
    float _time = 0;
    
    ModelObj _model;

    
public:
    static SceneTermProject* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessSpecialKeys(int key, int x, int y);
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    void CameraMove(float dt);
    void Enter2d();
    void Exit2d();
    void UpdateFogByState();
};

#endif /* defined(__graphics_practice__SceneTermProject__) */
