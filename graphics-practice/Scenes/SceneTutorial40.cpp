//
//  SceneTutorial40.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial40.h"


SceneTutorial40* SceneTutorial40::Create()
{
    SceneTutorial40 *pRet = new SceneTutorial40;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

SceneTutorial40::SceneTutorial40()
: ropeSimulation(80,
                 0.05f,
                 10000.0f,
                 0.05f,
                 0.2f,
                 Vector3(0, -9.81f, 0),
                 0.02f,
                 100.0f,
                 0.2f,
                 2.0f,
                 -1.5f)
{
    
}

bool SceneTutorial40::Init()
{
    glClearColor (0.0f, 0.0f, 0.0f, 0.5f);									// Black Background
    glClearDepth (1.0f);													// Depth Buffer Setup
    glShadeModel (GL_SMOOTH);												// Select Smooth Shading
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// Set Perspective Calculations To Most Accurate
    
    ropeSimulation.GetMass(ropeSimulation.masses.size() - 1).velocity.z = 10.0f;

    return true;
}

void SceneTutorial40::OnExit()
{

}

void SceneTutorial40::Update(float dt)
{
    Scene::Update(dt);
    
    Vector3 ropeConnectionVel;
    ropeSimulation.SetRopeConnectionVel(ropeConnectionVel);
    
    float slowDt = dt / slowMotionRatio;
    ropeSimulation.Operate(slowDt);
}

void SceneTutorial40::Draw()
{
    Scene::Draw();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();														// Reset The Modelview Matrix
    
    // Position Camera 40 Meters Up In Z-Direction.
    // Set The Up Vector In Y-Direction So That +X Directs To Right And +Y Directs To Up On The Window.
    gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// Clear Screen And Depth Buffer
    
    // Draw A Plane To Represent The Ground (Different Colors To Create A Fade)
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 255);												// Set Color To Light Blue
    glVertex3f(20, ropeSimulation.groundHeight, 20);
    glVertex3f(-20, ropeSimulation.groundHeight, 20);
    glColor3ub(0, 0, 0);												// Set Color To Black
    glVertex3f(-20, ropeSimulation.groundHeight, -20);
    glVertex3f(20, ropeSimulation.groundHeight, -20);
    glEnd();
    
    // Start Drawing Shadow Of The Rope
    glColor3ub(0, 0, 0);													// Set Color To Black
    for (int a = 0; a < ropeSimulation.masses.size() - 1; ++a)
    {
        Mass &mass1 = ropeSimulation.GetMass(a);
        Vector3 &pos1 = mass1.pos;
        
        Mass &mass2 = ropeSimulation.GetMass(a + 1);
        Vector3 &pos2 = mass2.pos;
        
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex3f(pos1.x, ropeSimulation.groundHeight, pos1.z);		// Draw Shadow At groundHeight
        glVertex3f(pos2.x, ropeSimulation.groundHeight, pos2.z);		// Draw Shadow At groundHeight
        glEnd();
    }
    // Drawing Shadow Ends Here.
    
    // Start Drawing The Rope.
    glColor3ub(255, 255, 0);												// Set Color To Yellow
    for (int a = 0; a < ropeSimulation.masses.size() - 1; ++a)
    {
        Mass &mass1 = ropeSimulation.GetMass(a);
        Vector3 &pos1 = mass1.pos;
        
        Mass &mass2 = ropeSimulation.GetMass(a + 1);
        Vector3 &pos2 = mass2.pos;
        
        glLineWidth(4);
        glBegin(GL_LINES);
        glVertex3f(pos1.x, pos1.y, pos1.z);
        glVertex3f(pos2.x, pos2.y, pos2.z);
        glEnd();
    }
    // Drawing The Rope Ends Here.
    
    glutSwapBuffers();
}

void SceneTutorial40::ProcessNormalKeys(unsigned char key, int x, int y)
{

}