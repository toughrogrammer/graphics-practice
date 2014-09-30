//
//  SceneTutorial9.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial11.h"
#include <math.h>


SceneTutorial11* SceneTutorial11::Create()
{
    SceneTutorial11 *pRet = new SceneTutorial11;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial11::Init()
{
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// This Will Clear The Background Color To Black
    glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    glPolygonMode( GL_BACK, GL_FILL );          // Back Face Is Filled In
    glPolygonMode( GL_FRONT, GL_LINE );         // Front Face Is Drawn With Lines
    
    
    _imgTim = MyImage::LoadImage("Textures/Tim.bmp");

    _points.resize(45);
    for( int x = 0; x < 45; x ++ ) {
        _points[x].resize(45);
        for( int y = 0; y < 45; y ++ ) {
            _points[x][y].resize(3);
            _points[x][y][0] = float( (x/5.0f) - 4.5f );
            _points[x][y][1] = float( (y/5.0f) - 4.5f );
            _points[x][y][2] = float( sin( ( ( ( x / 5.0f ) * 40.0f ) / 360.0f ) * 3.141592654 * 2.0f ) );
        }
    }
    
    _wiggle_count = 0;
    
    return true;
}

void SceneTutorial11::OnExit()
{
    
}

void SceneTutorial11::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial11::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The View
    
    glTranslatef(0.0f, 0.0f, -12.0f);
    glRotatef(_cameraRotation.x,1.0f,0.0f,0.0f);
    glRotatef(_cameraRotation.y,0.0f,1.0f,0.0f);
    glRotatef(_cameraRotation.z,0.0f,0.0f,1.0f);
    
    glBindTexture(GL_TEXTURE_2D, _imgTim->GetTexture());
    glBegin(GL_QUADS);
    for( int x = 0; x < 44; x++ )
    {
        for( int y = 0; y < 44; y++ )
        {
            float float_x = float(x)/44.0f;
            float float_y = float(y)/44.0f;
            float float_xb = float(x+1)/44.0f;
            float float_yb = float(y+1)/44.0f;
            
            glTexCoord2f( float_x, float_y);
            glVertex3f( _points[x][y][0], _points[x][y][1], _points[x][y][2] );
            
            glTexCoord2f( float_x, float_yb );
            glVertex3f( _points[x][y+1][0], _points[x][y+1][1], _points[x][y+1][2] );
            
            glTexCoord2f( float_xb, float_yb );
            glVertex3f( _points[x+1][y+1][0], _points[x+1][y+1][1], _points[x+1][y+1][2] );
            
            glTexCoord2f( float_xb, float_y );
            glVertex3f( _points[x+1][y][0], _points[x+1][y][1], _points[x+1][y][2] );
        }
    }
    glEnd();
    
    if( _wiggle_count == 2 )
    {
        for( int y = 0; y < 45; y++ )
        {
            float hold=_points[0][y][2];
            for( int x = 0; x < 44; x++)
            {
                _points[x][y][2] = _points[x+1][y][2];
            }
            _points[44][y][2]=hold;
        }
        _wiggle_count = 0;
    }
    
    _wiggle_count++;
    
    _cameraRotation.x += 0.3f;
    _cameraRotation.y += 0.2f;
    _cameraRotation.z += 0.4f;

    
    glutSwapBuffers();
}

void SceneTutorial11::ProcessSpecialKeys(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
    }
}

void SceneTutorial11::ProcessNormalKeys(unsigned char key, int x, int y)
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
