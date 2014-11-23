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


SceneTermProject::Sun::Sun()
{
    Initialize();
}

void SceneTermProject::Sun::Initialize()
{
    glEnable(LightID);
    glLightfv(LightID, GL_AMBIENT, LightAmbient);
    glLightfv(LightID, GL_DIFFUSE, LightDiffuse);
    glLightfv(LightID, GL_CONSTANT_ATTENUATION, LightAttenuation);
}

void SceneTermProject::Sun::SetLightID(GLenum id)
{
    glDisable(LightID);
    LightID = id;
    Initialize();
}

void SceneTermProject::Sun::SetPosition(float x, float y, float z, float w)
{
    LightPosition[0] = x;
    LightPosition[1] = y;
    LightPosition[2] = z;
    LightPosition[3] = w;
    
    glLightfv(LightID, GL_POSITION, LightPosition);
}

void SceneTermProject::Sun::Update(float dt)
{
    _time += DAY_FACTOR * dt;
    float y = sin(_time) * SUN_RADIUS;
    float z = cos(_time) * SUN_RADIUS;
    SetPosition(0.0f, y, z);
    if( y < 0 ) {
        glDisable(LightID);
    }
    else {
        glEnable(LightID);
    }
}

SceneTermProject* SceneTermProject::Create()
{
    SceneTermProject *pRet = new SceneTermProject;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTermProject::Init()
{
    // init GL
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL); // Enable Coloring Of Material ( NEW )
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
    
    
    GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightAttenuation[1] = { 1.9f, };
    GLfloat LightPosition[4] = { 50.0f, 30.0f, 0.0f, 1.0f };
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, LightAttenuation);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    
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
    
    _sun.Update(dt);
    
    
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
    
    for( int i = 0; i < _treasures.size(); i ++ ) {
        _treasures[i]->Update(dt);
        if( _treasures[i]->IsFinishedAnimating() ) {
            vector<Treasure*>::iterator it = _treasures.begin();
            for( int j = 0; j < i; j ++ ) it++;
            _treasures.erase(it);
            
            ostringstream ostr;
            ostr << "Remaining Treasure : ";
            ostr << _treasures.size();
            _stringGainTreasure = ostr.str();
            break;
        }
    }
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
    
    _floorSprite->Draw();
    
    for( int i = 0; i < _treasures.size(); i ++ ) {
        _treasures[i]->Draw();
    }
    
    Enter2d();
    {
        glColor3d(1.0f, 0.0f, 0);
        RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 20, 20, _stringGainTreasure.c_str());
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    Exit2d();

    
    glLineWidth(3);
    glBegin(GL_LINES);
    // x-axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100, 1, 0);
    glVertex3f(100, 1, 0);
    // y-axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    // z-axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 1, -100);
    glVertex3f(0, 1, 100);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(_sun.LightPosition[0], _sun.LightPosition[1], _sun.LightPosition[2]);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    
    
    glTranslatef(50, 30, 0);
    glRotatef(_time * 10, 0, 1, 0);
    glScalef(20, 20, 20);
    _model.Draw();
    
    
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
}


void SceneTermProject::CameraMove(float dt)
{
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