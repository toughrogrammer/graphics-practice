//
//  SceneTutorial13.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 13..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial14.h"


SceneTutorial14* SceneTutorial14::Create()
{
    SceneTutorial14 *pRet = new SceneTutorial14;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial14::Init()
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_LIGHT0);								// Enable Default Light (Quick And Dirty)
    glEnable(GL_LIGHTING);								// Enable Lighting
    glEnable(GL_COLOR_MATERIAL);						// Enable Coloring Of Material
    
    g_rot = 0;
    
    return true;
}

void SceneTutorial14::OnExit()
{

}

void SceneTutorial14::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial14::Draw()
{
    Scene::Draw();
    
    char str[128];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glTranslatef(0.0f,0.0f,-15.0f);						// Move One Unit Into The Screen
    glRotatef(g_rot,1.0f,0.0f,0.0f);					// Rotate On The X Axis
    glRotatef(g_rot*1.5f,0.0f,1.0f,0.0f);				// Rotate On The Y Axis
    glRotatef(g_rot*1.4f,0.0f,0.0f,1.0f);				// Rotate On The Z Axis
    glScalef(0.005, 0.005, 0.0);
    // Pulsing Colors Based On The Rotation
    glColor3f(1.0f*float(cos(g_rot/20.0f)),1.0f*float(sin(g_rot/25.0f)),1.0f-0.5f*float(cos(g_rot/17.0f)));
    sprintf(str, "NeHe - %3.2f",g_rot/50);				// Print GL Text To The Screen
    render_stroke_string(GLUT_STROKE_ROMAN, str);
    g_rot += 0.5f;										// Increase The Rotation Variable
    
    // Swap The Buffers To Become Our Rendering Visible
    glutSwapBuffers();
}

void SceneTutorial14::render_stroke_string(void* font, const char* string)
{
    char* p;
    float width = 0;
    
    // Center Our Text On The Screen
    glPushMatrix();
    // Render The Text
    p = (char*) string;
    while (*p != '\0') glutStrokeCharacter(font, *p++);
    glPopMatrix();
}
