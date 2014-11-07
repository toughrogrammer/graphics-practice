//
//  SceneTutorial31.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial31.h"


SceneTutorial31* SceneTutorial31::Create()
{
    SceneTutorial31 *pRet = new SceneTutorial31;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial31::Init()
{
    glEnable(GL_TEXTURE_2D);										// Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);										// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);							// Black Background
    glClearDepth(1.0f);												// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);										// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);											// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Really Nice Perspective Calculations
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    model = ModelMilkshape3D::Create("Data/model.ms3d");
    

    return true;
}

void SceneTutorial31::OnExit()
{

}

void SceneTutorial31::Update(float dt)
{
    Scene::Update(dt);
    
    yrot += yrotspeed * dt;
}

void SceneTutorial31::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear The Screen And The Depth Buffer
    glLoadIdentity();												// Reset The Modelview Matrix
    gluLookAt( 75, 75, 75, 0, 0, 0, 0, 1, 0 );						// (3) Eye Postion (3) Center Point (3) Y-Axis Up Vector
    
    glRotatef(yrot,0.0f,1.0f,0.0f);									// Rotate On The Y-Axis By yrot
    
    model->Draw();													// Draw The Model
    
    glutSwapBuffers();
}

void SceneTutorial31::ProcessNormalKeys(unsigned char key, int x, int y)
{

}