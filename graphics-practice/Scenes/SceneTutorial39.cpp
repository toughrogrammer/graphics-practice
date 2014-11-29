//
//  SceneTutorial39.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial39.h"


SceneTutorial39* SceneTutorial39::Create()
{
    SceneTutorial39 *pRet = new SceneTutorial39;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

SceneTutorial39::SceneTutorial39()
: motionUnderGravitation(Vector3(0.0f, -9.81f, 0.0f))
, massConnectedWithSpring(2.0f)
{
    
}

bool SceneTutorial39::Init()
{
    glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
    glShadeModel (GL_SMOOTH);									// Select Smooth Shading
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    

    return true;
}

void SceneTutorial39::OnExit()
{

}

void SceneTutorial39::Update(float dt)
{
    Scene::Update(dt);
    
    float slowDt = dt / slowMotionRatio;
    
    constantVelocity.Operate(slowDt);
    motionUnderGravitation.Operate(slowDt);
    massConnectedWithSpring.Operate(slowDt);
}

void SceneTutorial39::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();
    
//    // roughly camera setting
//    glRotatef( _cameraRotation.x, 1.0f, 0.0f, 0.0f );
//    glRotatef( _cameraRotation.y, 0.0f, 1.0f, 0.0f );
//    glRotatef( _cameraRotation.z, 0.0f, 0.0f, 1.0f );
//    glScalef( _cameraScale.x, _cameraScale.y, _cameraScale.z );
//    glTranslatef( -_cameraPosition.x, -_cameraPosition.y, -_cameraPosition.z );
    
    gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);
    
    
    // Drawing The Coordinate Plane Starts Here.
    // We Will Draw Horizontal And Vertical Lines With A Space Of 1 Meter Between Them.
    glColor3ub(0, 0, 255);										// Draw In Blue
    glBegin(GL_LINES);
    
    // Draw The Vertical Lines
    for (float x = -20; x <= 20; x += 1.0f)						// x += 1.0f Stands For 1 Meter Of Space In This Example
    {
        glVertex3f(x, 20, 0);
        glVertex3f(x,-20, 0);
    }
    
    // Draw The Horizontal Lines
    for (float y = -20; y <= 20; y += 1.0f)						// y += 1.0f Stands For 1 Meter Of Space In This Example
    {
        glVertex3f( 20, y, 0);
        glVertex3f(-20, y, 0);
    }
    
    glEnd();
    // Drawing The Coordinate Plane Ends Here.
    
    glColor3ub(255, 0, 0);
    for( int i = 0; i < constantVelocity.masses.size(); i ++ ) {
        const Mass& mass = constantVelocity.GetMass(i);
        const Vector3& pos = mass.pos;
        
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3f(pos.x, pos.y, pos.z);
        glEnd();
    }
    
    glColor3ub(255, 255, 0);
    for( int i = 0; i < motionUnderGravitation.masses.size(); i ++ ) {
        const Mass& mass = motionUnderGravitation.GetMass(i);
        const Vector3& pos = mass.pos;
        
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3f(pos.x, pos.y, pos.z);
        glEnd();
    }

    glColor3ub(0, 255, 0);
    for( int i = 0; i < massConnectedWithSpring.masses.size(); i ++ ) {
        const Mass& mass = massConnectedWithSpring.GetMass(i);
        const Vector3& pos1 = mass.pos;
        const Vector3& pos2 = massConnectedWithSpring.connectionPos;
        
        glPointSize(8);
        glBegin(GL_POINTS);
        glVertex3f(pos1.x, pos1.y, pos1.z);
        glEnd();
        
        glBegin(GL_LINES);
        glVertex3f(pos1.x, pos1.y, pos1.z);
        glVertex3f(pos2.x, pos2.y, pos2.z);
        glEnd();
    }
    
    
    glutSwapBuffers();
}

void SceneTutorial39::ProcessNormalKeys(unsigned char key, int x, int y)
{

}