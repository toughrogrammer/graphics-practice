//
//  SceneTermProject1.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTermProject1.h"


SceneTermProject1* SceneTermProject1::Create()
{
    SceneTermProject1 *pRet = new SceneTermProject1;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTermProject1::Init()
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
    
    
    // set camera position
    _cameraPosition.Set( 0, 600, 120 );
    _cameraRotation.Set( 60, 0, 0 );
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    
    _spriteGrass = Sprite::Create("Textures/grass.jpg");
    if( _spriteGrass == NULL ) {
        return false;
    }
    
    _spriteGrass->SetPosition( Vector3( 0, 0, 0 ) );
    _spriteGrass->SetRotation( Vector3( 90, 0, 0 ) );
    
    MyImage *boxImage = MyImage::LoadImage("Textures/Crate.bmp");
    _cube = Cube::Create( boxImage->GetTexture(), 100.0f );
    _cube->SetPosition( Vector3( 0, 50, -300 ) );
    delete boxImage;
    
    return true;
}

void SceneTermProject1::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTermProject1::Draw()
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
    
    _spriteGrass->Draw();
    _cube->Draw();
    
    glutSwapBuffers();
}

void SceneTermProject1::ProcessSpecialKeys(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_LEFT:
        {
            MoveBy *move = MoveBy::Create( 1.0f, Vector3(-100, 0, 0) );
            _cube->RunAction( move );
        }
            break;
        case GLUT_KEY_RIGHT:
        {
            MoveBy *move = MoveBy::Create( 1.0f, Vector3(100, 0, 0) );
            _cube->RunAction( move );
        }
            break;
        case GLUT_KEY_UP:
        {
            MoveBy *move = MoveBy::Create( 1.0f, Vector3(0, 0, -100) );
            _cube->RunAction( move );
        }
            break;
        case GLUT_KEY_DOWN:
        {
            MoveBy *move = MoveBy::Create( 1.0f, Vector3(0, 0, 100) );
            _cube->RunAction( move );
        }
            break;
    }
}

void SceneTermProject1::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    
    if (key == 'l' || key == 'L' ) {
        _light=!_light;
        if (!_light)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }
    }
    
    if ( key == 'b' || key == 'B' ) {
        _blend = !_blend;
        if(_blend)
        {
            glEnable(GL_BLEND);			// Turn Blending On
            glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off
        }
        else
        {
            glDisable(GL_BLEND);		// Turn Blending Off
            glEnable(GL_DEPTH_TEST);	// Turn Depth Testing On
        }
    }
}

void SceneTermProject1::LogCameraStatus() {
    cout << "camera position - (" << _cameraPosition.x << ", " << _cameraPosition.y << ", " << _cameraPosition.z << ")" << endl;
    cout << "camera rotation - (" << _cameraRotation.x << ", " << _cameraRotation.y << ", " << _cameraRotation.z << ")" << endl;
    cout << "camera scale - (" << _cameraScale.x << ", " << _cameraScale.y << ", " << _cameraScale.z << ")" << endl;
}
