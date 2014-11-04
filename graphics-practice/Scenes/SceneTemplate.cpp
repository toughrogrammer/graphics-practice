//
//  SceneTutorial20.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial20.h"


SceneTutorial20* SceneTutorial20::Create()
{
    SceneTutorial20 *pRet = new SceneTutorial20;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial20::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear The Background Color To Black
    glClearDepth(1.0); // Enables Clearing Of The Depth Buffer
    glEnable(GL_DEPTH_TEST); // Enable Depth Testing
    glShadeModel(GL_SMOOTH); // Enables Smooth Color Shading
    glEnable(GL_TEXTURE_2D); // Enable 2D Texture Mapping
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    

    return true;
}

void SceneTutorial20::OnExit()
{

}

void SceneTutorial20::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial20::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();
    
    // roughly camera setting
    glRotatef( _cameraRotation.x, 1.0f, 0.0f, 0.0f );
    glRotatef( _cameraRotation.y, 0.0f, 1.0f, 0.0f );
    glRotatef( _cameraRotation.z, 0.0f, 0.0f, 1.0f );
    glScalef( _cameraScale.x, _cameraScale.y, _cameraScale.z );
    glTranslatef( -_cameraPosition.x, -_cameraPosition.y, -_cameraPosition.z );
    
    glutSwapBuffers();
}

void SceneTutorial20::ProcessNormalKeys(unsigned char key, int x, int y)
{

}