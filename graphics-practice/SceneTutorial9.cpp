//
//  SceneTutorial9.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial9.h"

#define NUM_OF_STAR 20


SceneTutorial9* SceneTutorial9::Create()
{
    SceneTutorial9 *pRet = new SceneTutorial9;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial9::Init()
{
    // init GL
    glEnable(GL_TEXTURE_2D);                // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);           // Black Background
    glClearDepth(1.0f);                 // Depth Buffer Setup
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);           // Set The Blending Function For Translucency
    glEnable(GL_BLEND);                 // Enable Blending
    
    
    _zoom = -15.0f;         // Distance Away From Stars
    _tilt = 90.0f;			// Tilt The View
    _spin = 0;				// Spin Stars
    
    _starImage = MyImage::LoadImage("Textures/Star.bmp");
    for( int i = 0; i < NUM_OF_STAR; i ++ ) {
        Star *star = new Star();
        star->r = rand()%256;
        star->g = rand()%256;
        star->b = rand()%256;
        star->angle = 0.0f;
        star->dist = (float(i) / NUM_OF_STAR) * 5.0f;
        
        _stars.push_back( star );
    }
    
    return true;
}

void SceneTutorial9::OnExit()
{
    SAFE_DELETE( _starImage );
    
    for( int i = 0; i < _stars.size(); i ++ ) {
        Star *star = _stars[i];
        delete star;
    }
    _stars.clear();
}

void SceneTutorial9::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial9::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glBindTexture(GL_TEXTURE_2D, _starImage->GetTexture());       // Select Our Texture
    
    for(int i = 0; i < _stars.size(); i ++ ) {
        Star *star = _stars[i];
        glLoadIdentity();								// Reset The View Before We Draw Each Star
        glTranslatef(0.0f,0.0f,_zoom);					// Zoom Into The Screen (Using The Value In 'zoom')
        glRotatef(_tilt,1.0f,0.0f,0.0f);					// Tilt The View (Using The Value In 'tilt')
        glRotatef(star->angle,0.0f,1.0f,0.0f);		// Rotate To The Current Stars Angle
        glTranslatef(star->dist,0.0f,0.0f);		// Move Forward On The X Plane
        glRotatef(-star->angle,0.0f,1.0f,0.0f);	// Cancel The Current Stars Angle
        glRotatef(-_tilt,1.0f,0.0f,0.0f);				// Cancel The Screen Tilt
        
        if (_twinkle)
        {
            int at = NUM_OF_STAR - i - 1;
            Star *newOne = _stars[at];
            
            glColor4ub(newOne->r,newOne->g,newOne->b,255);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
            glEnd();
        }
        
        glRotatef(_spin,0.0f,0.0f,1.0f);
        glColor4ub(star->r,star->g,star->b,255);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
        glEnd();
        
        _spin += 0.01f;
        star->angle+=float(i)/NUM_OF_STAR;
        star->dist-=0.01f;
        if (star->dist<0.0f)
        {
            star->dist+=5.0f;
            star->r=rand()%256;
            star->g=rand()%256;
            star->b=rand()%256;
        }
    }
    
    
    glutSwapBuffers();
}

void SceneTutorial9::ProcessSpecialKeys(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_F1:
            exit(0);
            break;
    }
}

void SceneTutorial9::ProcessNormalKeys(unsigned char key, int x, int y)
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
    
    if( key == 't' || key == 'T' ) {
        _twinkle = !_twinkle;
    }
}
