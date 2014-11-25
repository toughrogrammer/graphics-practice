//
//  SceneTermProject.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTermProject.h"
#include "Treasure.h"
#include <sstream>


SceneTermProject* SceneTermProject::Create()
{
    SceneTermProject *pRet = new SceneTermProject;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

SceneTermProject::SceneTermProject()
: _sun(GL_LIGHT0)
, _controlLight(GL_LIGHT1)
{
    
}

bool SceneTermProject::Init()
{
    // init GL
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    
    
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
    UpdateFogByState();

    
    srand((unsigned)time(NULL));
    int radius = 60;
    for( int i = 0; i < 10; i ++ ) {
        Treasure *treasure = Treasure::Create("TermProject2/Treasure.jpg");
        if( treasure == NULL ) {
            continue;
        }
        
        float x, z;
        x = rand() % radius - radius / 2;
        z = -1 * (rand() % radius - radius / 2);
        treasure->SetPosition( Vector3( x, 2.6f, z ) );
        _treasures.push_back( treasure );
    }
    
    
    _floorSprite = Sprite::Create("TermProject2/sand.jpg");
    if( _floorSprite == NULL ) {
        return false;
    }
    _floorSprite->SetSize( 512, 512 );
    _floorSprite->SetPosition( Vector3( 0, 0, 0 ) );
    _floorSprite->SetRotation( Vector3( 90, 0, 0 ) );
    
    
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    _cameraRotation.Set(30, 45, 0);
    _cameraPosition.Set(-90, 90, 90);
    WalkingSpeed = 8.0f;
    
    _takingDelay = 0;
    _stringGainTreasure = "Remaining Treasure : 10";
    
    _model.InitWithFile("TermProject2/Models/floating-pillar.obj");
    
    
    _sun.SetEnabled(false);
    _sun.SetAmbient(0.5f, 0.5f, 0.5f);
    _sun.SetDiffuse(1.0f, 1.0f, 1.0f);
    _sun.SetAttenuation(1.9f);
    
    _controlLight.SetEnabled(true);
    _controlLight.SetAmbient(1.0f, 1.0f, 1.0f);
    _controlLight.SetDiffuse(1.0f, 1.0f, 1.0f);
    _controlLight.SetAttenuation(1.1f);
    _controlLight.SetPosition( Vector3(0, 0, 0) );
    
    return true;
}

void SceneTermProject::OnExit()
{
    for( int i = 0; i < _treasures.size(); i ++ ) {
        SAFE_DELETE( _treasures[i] );
    }
}

void SceneTermProject::Update(float dt)
{
    Scene::Update(dt);
    
    CameraMove(dt);
    _time += dt;
    _moveLightkeyDelay -= dt;
    
    float factedTime = _time * DAY_FACTOR;
    float y = sin(factedTime) * SUN_RADIUS;
    float z = cos(factedTime) * SUN_RADIUS;
    _sun.SetPosition(Vector3(0.0f, y, z));
//    if( y < 0 ) {
//        _sun.SetEnabled( false );
//    }
//    else {
//        _sun.SetEnabled( true );
//    }
    
    
    if( _isMoveLight && Keyboard::PressedSpecial(GLUT_KEY_LEFT) ) {
        Vector3 pos = _controlLight.GetPosition();
        pos.x -= 10 * dt;
        _controlLight.SetPosition(pos);
    }
    if( _isMoveLight && Keyboard::PressedSpecial(GLUT_KEY_RIGHT) ) {
        Vector3 pos = _controlLight.GetPosition();
        pos.x += 10 * dt;
        _controlLight.SetPosition(pos);
    }
    if( _isMoveLight && Keyboard::PressedSpecial(GLUT_KEY_DOWN) ) {
        Vector3 pos = _controlLight.GetPosition();
        pos.y -= 10 * dt;
        _controlLight.SetPosition(pos);
    }
    if( _isMoveLight && Keyboard::PressedSpecial(GLUT_KEY_UP) ) {
        Vector3 pos = _controlLight.GetPosition();
        pos.y += 10 * dt;
        _controlLight.SetPosition(pos);
    }
    if( _isMoveLight && Keyboard::PressedNormal('z') ) {
        Vector3 pos = _controlLight.GetPosition();
        pos.z += 10 * dt;
        _controlLight.SetPosition(pos);
    }
    if( _isMoveLight && Keyboard::PressedNormal('x') ) {
        Vector3 pos = _controlLight.GetPosition();
        pos.z -= 10 * dt;
        _controlLight.SetPosition(pos);
    }
    

    
    _takingDelay += dt;
    if( Keyboard::PressedNormal(' ') && _takingDelay > 2.0f ) {
        int target = -1;
        float min_length = 9999;
        for( int i = 0; i < _treasures.size(); i ++ ) {
            Treasure *treasure = _treasures[i];
            Vector3 pos = treasure->GetPosition();
            Vector3 dist = _cameraPosition - pos;
            float length = dist.Length();
            if( length < 25.0f && length < min_length && ! treasure->IsOnAnimating() ) {
                min_length = length;
                target = i;
            }
        }
        
        if( target != -1 ) {
            Treasure *treasure = _treasures[target];
            treasure->Taked();
            _takingDelay = 0;
        }
    }
    
    
    char str[256];
    Vector3 lightPos = _controlLight.GetPosition();
    sprintf(str, "(%.2f, %.2f, %.2f)", lightPos.x, lightPos.y, lightPos.z);
    _stringLightPosition = string(str);
}

void SceneTermProject::Draw()
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
    
    
    _sun.Draw();
    _controlLight.Draw();
    
    
    _floorSprite->Draw();
    
    for( int i = 0; i < _treasures.size(); i ++ ) {
        _treasures[i]->Draw();
    }
    
    glPushMatrix();
    glTranslatef(0, 1.0f, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    // x-axis
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-100, 0, 0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(100, 0, 0);
    // y-axis
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0, -100, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 100, 0);
    // z-axis
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0, 0, -100);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 100);
    
    Vector3 sunPosition = _sun.GetPosition();
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(sunPosition.x, sunPosition.y, sunPosition.z);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    
    // show light position
    glPointSize(20);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    Vector3 lightPos = _controlLight.GetPosition();
    glVertex3f(lightPos.x, lightPos.y, lightPos.z);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
    
    
    glTranslatef(50, 30, 0);
    glRotatef(_time * 10, 0, 1, 0);
    glScalef(20, 20, 20);
    _model.Draw();
    
    
    Enter2d();
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 20, 20, _stringLightPosition.c_str());
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    Exit2d();
    
    glutSwapBuffers();
}

void SceneTermProject::ProcessSpecialKeys(int key, int x, int y)
{
    
}

void SceneTermProject::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == 'f' || key == 'F' ) {
        _isFog = ! _isFog;
        UpdateFogByState();
    }
    
    if( key == 'l' && _moveLightkeyDelay < 0 ) {
        _moveLightkeyDelay = 0.3f;
        _isMoveLight = ! _isMoveLight;
    }
}


void SceneTermProject::CameraMove(float dt)
{
    if( _isMoveLight ) {
        return;
    }
    
    Vector3 forward;
    
    if( Keyboard::PressedNormal('w') || Keyboard::PressedNormal('W') ) {
        _cameraPosition.z -= WalkingSpeed * dt;
    }
    if( Keyboard::PressedNormal('s') || Keyboard::PressedNormal('S') ) {
        _cameraPosition.z += WalkingSpeed * dt;
    }
    if( Keyboard::PressedNormal('a') || Keyboard::PressedNormal('A') ) {
        _cameraPosition.x -= WalkingSpeed * dt;
    }
    if( Keyboard::PressedNormal('d') || Keyboard::PressedNormal('D') ) {
        _cameraPosition.x += WalkingSpeed * dt;
    }
    
    if( Keyboard::PressedSpecial(GLUT_KEY_LEFT) ) {
        _cameraRotation.y -= 3.0f;
    }
    if( Keyboard::PressedSpecial(GLUT_KEY_RIGHT) ) {
        _cameraRotation.y += 3.0f;
    }
}

void SceneTermProject::Enter2d()
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

void SceneTermProject::Exit2d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
}

void SceneTermProject::UpdateFogByState()
{
    if( _isFog ) {
        glEnable(GL_FOG);
    }
    else {
        glDisable(GL_FOG);
    }
}