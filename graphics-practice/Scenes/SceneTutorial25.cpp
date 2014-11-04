//
//  SceneTutorial25.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial25.h"

#include <fstream>


SceneTutorial25* SceneTutorial25::Create()
{
    SceneTutorial25 *pRet = new SceneTutorial25;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial25::Init()
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);                   // Set The Blending Function For Translucency
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               // This Will Clear The Background Color To Black
    glClearDepth(1.0);                                  // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);                               // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glShadeModel(GL_SMOOTH);                            // Enables Smooth Color Shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    
    
    _cameraPosition.Set(0, 1.5, 10);
    _cameraRotation.Set(0, 0, 0);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);

    maxver = 0;                                           // Sets Max Vertices To 0 By Default
    LoadObject("data/sphere.txt", morph1);
    LoadObject("data/torus.txt", morph2);
    LoadObject("data/tube.txt", morph3);
    
    for( int i = 0; i < morph1._points.size(); i ++ ) {
        float x = RandomRangeDouble(-7, 7);
        float y = RandomRangeDouble(-7, 7);
        float z = RandomRangeDouble(-7, 7);
        morph4._points.push_back( Vector3( x, y, z ) );
    }

    LoadObject("data/sphere.txt", helper);                 // Load sphere.txt Object Into Helper (Used As Starting Point)
    sour = dest = &morph1;                                  // Source & Destination Are Set To Equal First Object (morph1)

    return true;
}

void SceneTutorial25::OnExit()
{
    
}

void SceneTutorial25::Update(float dt)
{
    Scene::Update(dt);
    
    _cameraRotation.x += 1.0f * dt;
    _cameraRotation.y += 2.0f * dt;
    _cameraRotation.z += 3.0f * dt;
    
    if( morph && step <= steps ) {
        step++;
    }
    else {
        morph = false;
        sour = dest;
        step = 0;
    }
    
    cout << dt << endl;
}

void SceneTutorial25::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The View
    
    // roughly camera setting
    glTranslatef( -_cameraPosition.x, -_cameraPosition.y, -_cameraPosition.z );
    glRotatef( _cameraRotation.x, 1.0f, 0.0f, 0.0f );
    glRotatef( _cameraRotation.y, 0.0f, 1.0f, 0.0f );
    glRotatef( _cameraRotation.z, 0.0f, 0.0f, 1.0f );
    
    GLfloat tx,ty,tz;                                   // Temp X, Y & Z Variables
    Vector3 q;                                           // Holds Returned Calculated Values For One Vertex

    glBegin(GL_POINTS);                                 // Begin Drawing Points
    for(int i = 0; i < morph1._points.size(); i ++ )                 // Loop Through All The Verts Of morph1 (All Objects Have
    {                                               // The Same Amount Of Verts For Simplicity, Could Use maxver Also)
        if(morph) {
            q = Calculate(i);
        }
        else {
            q.x = q.y = q.z = 0;   // If morph Is True Calculate Movement Otherwise Movement=0
        }
        
        helper._points[i].x-=q.x;                    // Subtract q.x Units From helper.points[i].x (Move On X Axis)
        helper._points[i].y-=q.y;                    // Subtract q.y Units From helper.points[i].y (Move On Y Axis)
        helper._points[i].z-=q.z;                    // Subtract q.z Units From helper.points[i].z (Move On Z Axis)
        tx=helper._points[i].x;                      // Make Temp X Variable Equal To Helper's X Variable
        ty=helper._points[i].y;                      // Make Temp Y Variable Equal To Helper's Y Variable
        tz=helper._points[i].z;                      // Make Temp Z Variable Equal To Helper's Z Variable

        glColor3f(0,1,1);                           // Set Color To A Bright Shade Of Off Blue
        glVertex3f(tx,ty,tz);                       // Draw A Point At The Current Temp Values (Vertex)
        glColor3f(0,0.5f,1);                        // Darken Color A Bit
        tx-=2*q.x; ty-=2*q.y; ty-=2*q.y;            // Calculate Two Positions Ahead
        glVertex3f(tx,ty,tz);                       // Draw A Second Point At The Newly Calculate Position
        glColor3f(0,0,1);                           // Set Color To A Very Dark Blue
        tx-=2*q.x; ty-=2*q.y; ty-=2*q.y;            // Calculate Two More Positions Ahead
        glVertex3f(tx,ty,tz);                       // Draw A Third Point At The Second New Position
    }                                               // This Creates A Ghostly Tail As Points Move
    glEnd();                                            // Done Drawing Points

    glutSwapBuffers();
}

void SceneTutorial25::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == 'm' || key == 'M' ) {
        morph = !morph;
    }
    
    if( key == ' ' ) {
        curr = (curr + 1) % 4;
        morph = true;
        switch( curr ) {
            case 0:
                dest = &morph1;
                break;
            case 1:
                dest = &morph2;
                break;
            case 2:
                dest = &morph3;
                break;
            case 3:
                dest = &morph4;
                break;
        }
    }
}

void SceneTutorial25::LoadObject(string path, Object &obj) 
{
    int count;
    float x, y, z;

    ifstream input(path.c_str());
    if( ! input.is_open() ) {
        return;
    }
    
    input.ignore(10);
    input >> count;
    
    string line;
    for( int i = 0; i < count; i ++ ) {
        input >> x >> y >> z;
        obj._points.push_back(Vector3(x, y, z));
    }

    if(count > maxver) {
        maxver = count;                          // If ver Is Greater Than maxver Set maxver Equal To ver
    }
}

Vector3 SceneTutorial25::Calculate(int i)
{
    Vector3 a;											// Temporary Vertex Called a
    a.x = 1.0f * (sour->_points[i].x - dest->_points[i].x) / steps;	// a.x Value Equals Source x - Destination x Divided By Steps
    a.y = 1.0f * (sour->_points[i].y - dest->_points[i].y) / steps;	// a.y Value Equals Source y - Destination y Divided By Steps
    a.z = 1.0f * (sour->_points[i].z - dest->_points[i].z) / steps;	// a.z Value Equals Source z - Destination z Divided By Steps
    return a;											// Return The Results
}