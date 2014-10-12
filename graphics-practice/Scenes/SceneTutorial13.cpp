//
//  SceneTutorial13.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial13.h"


SceneTutorial13* SceneTutorial13::Create()
{
    SceneTutorial13 *pRet = new SceneTutorial13;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial13::Init()
{
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    return true;
}

void SceneTutorial13::OnExit()
{

}

void SceneTutorial13::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial13::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();
    
    glLoadIdentity();
    glTranslatef(0, 0, -5);
    
    Enter2d();
    {
        glColor3d(1.0f, 1.0f, 0);
        RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 20, 20, "Hello world");
    }
    Exit2d();

    glutSwapBuffers();
}

void SceneTutorial13::Enter2d()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
}

void SceneTutorial13::Exit2d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
}