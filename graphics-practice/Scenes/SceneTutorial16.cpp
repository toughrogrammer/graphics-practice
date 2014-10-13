//
//  SceneTutorial16.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 13..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial16.h"

SceneTutorial16* SceneTutorial16::Create()
{
    SceneTutorial16 *pRet = new SceneTutorial16;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial16::Init()
{
    // init GL
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    
    
    //
    // light
    //
    GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[] = { 0.0f, 0.0f, 50.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One
    
    
    //
    // fog
    //
    GLuint fogFilter = GL_EXP2;
    GLfloat fogColor[4]= {1.0f, 0.94f, 0.7f, 1.0f};
    GLfloat fogDensity = 0.05;
    glFogi(GL_FOG_MODE, fogFilter);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, fogDensity);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, -50.0f);             // Fog Start Depth
    glFogf(GL_FOG_END, 50.0f);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG
    
    
    _cameraPosition.Set(0, 0, 20);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    MyImage *img = MyImage::LoadImage("Textures/Crate.bmp");
    _box = Cube::Create(img->GetTexture(), 5.0f);
    SAFE_DELETE(img);
    
    return true;
}

void SceneTutorial16::OnExit()
{
    
}

void SceneTutorial16::Update(float dt)
{
    Scene::Update(dt);
    
    _box->SetRotation( _box->GetRotation() + Vector3(10 * dt, 20 * dt, 30 * dt) );
}

void SceneTutorial16::Draw()
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
    _box->Draw();
    
    glutSwapBuffers();
}