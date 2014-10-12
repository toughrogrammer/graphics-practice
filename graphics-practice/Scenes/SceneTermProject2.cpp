//
//  SceneTermProject2.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTermProject2.h"


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
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    
    
    GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[] = { 0.0f, 0.0f, 50.0f, 1.0f };
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One

    
    MyImage *img = MyImage::LoadImage("TermProject2/Treasure.jpg");
    _cube = Cube::Create(img->GetTexture(), 5.0f);
    SAFE_DELETE(img);
    _cube->SetPosition(Vector3( 0, 2.5f, -30 ));
    _cube->SetRotation(Vector3(0, 0, 180));
    
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
    
    return true;
}

void SceneTermProject2::Update(float dt)
{
    Scene::Update(dt);
    cout << dt << endl;
    
    CameraMove(dt);
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
    _cube->Draw();

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
    
    float new_y = sin(_cameraPosition.z) * 0.5 + 10;
    _cameraPosition.y = new_y;
}