//
//  SceneTutorial37.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 25..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial37__
#define __graphics_practice__SceneTutorial37__

#include "Prefix.h"


class SceneTutorial37 : public Scene
{
    class MATRIX {
    public:
        float Data[16];
    };

    class VERTEX {
    public:
        Vector3 normal, position;
    };

    class POLYGON {
    public:
        VERTEX vertices[3];
    };


private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;

    bool outlineDraw = true; // Flag To Draw The Outline
    bool outlineSmooth = false; // Flag To Anti-Alias The Lines
    float outlineColor[3] = { 0.0f, 0.0f, 0.0f }; // Color Of The Lines
    float outlineWidth = 3.0f; // Width Of The Lines
    Vector3 lightAngle; // The Direction Of The Light
    bool lightRotate = false; // Flag To See If We Rotate The Light
    float modelAngle = 0.0f; // Y-Axis Angle Of The Model
    bool modelRotate = false; // Flag To Rotate The Model
    POLYGON *polyData = NULL; // Polygon Data
    int polyNum = 0; // Number Of Polygons
    GLuint shaderTexture[1]; // Storage For One Texture

    
public:
    static SceneTutorial37* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);


    bool ReadMesh();
    void RotateVector(MATRIX &mat, const Vector3 &vec, Vector3 &result);
};


#endif /* defined(__graphics_practice__SceneTutorial37__) */
