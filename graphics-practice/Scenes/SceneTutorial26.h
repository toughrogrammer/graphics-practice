//
//  SceneTutorial26.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial26__
#define __graphics_practice__SceneTutorial26__

#include "Prefix.h"


class SceneTutorial26 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    GLfloat  LightAmb[4] = {0.7f, 0.7f, 0.7f, 1.0f};              // Ambient Light
    GLfloat  LightDif[4] = {1.0f, 1.0f, 1.0f, 1.0f};              // Diffuse Light
    GLfloat  LightPos[4] = {4.0f, 4.0f, 6.0f, 1.0f};              // Light Position

    GLUquadricObj   *q;                             // Quadratic For Drawing A Sphere
 
	GLfloat     xrot        =  0.0f;                    // X Rotation
	GLfloat     yrot        =  0.0f;                    // Y Rotation
	GLfloat     xrotspeed   =  10.0f;                    // X Rotation Speed
	GLfloat     yrotspeed   =  20.0f;                    // Y Rotation Speed
	GLfloat     zoom        = -7.0f;                    // Depth Into The Screen
	GLfloat     height      =  2.0f;                    // Height Of Ball From Floor

	MyImage *imageFloor;
	MyImage *imageEnv;
	MyImage *imageBall;

    
public:
    static SceneTutorial26* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    virtual void ProcessSpecialKeys(int key, int x, int y);

    void DrawObject();
    void DrawFloor();
};


#endif /* defined(__graphics_practice__SceneTutorial26__) */
