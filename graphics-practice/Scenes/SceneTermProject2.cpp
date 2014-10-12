//
//  SceneTermProject2.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTermProject2.h"
#include "Treasure.h"
#include <sstream>


SceneTermProject2* SceneTermProject2::Create()
{
    SceneTermProject2 *pRet = new SceneTermProject2;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTermProject2::Init()
{
    // init GL
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.43f, 0.85f, 0.99f, 1.0f);                   // Black Background
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
    _cameraRotation.Set(20, 0, 0);
    _cameraPosition.Set(0, 15, 0);
    WalkingSpeed = 8.0f;
    
    _takingDelay = 0;
    _stringGainTreasure = "Remaining Treasure : 10";
    
    return true;
}

void SceneTermProject2::OnExit()
{
    for( int i = 0; i < _treasures.size(); i ++ ) {
        SAFE_DELETE( _treasures[i] );
    }
}

void SceneTermProject2::Update(float dt)
{
    Scene::Update(dt);
    
    CameraMove(dt);
    
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

void SceneTermProject2::Draw()
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
    
    glutSwapBuffers();
}


void SceneTermProject2::CameraMove(float dt)
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
    
    float new_y = sin(_cameraPosition.z + _cameraPosition.x) * 0.5 + 15;
    _cameraPosition.y = new_y;
}

void SceneTermProject2::Enter2d()
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

void SceneTermProject2::Exit2d()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
}