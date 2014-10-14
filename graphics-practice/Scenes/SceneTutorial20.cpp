//
//  SceneTutorial20.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial20.h"


SceneTutorial20* SceneTutorial20::Create()
{
    SceneTutorial20 *pRet = new SceneTutorial20;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial20::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear The Background Color To Black
    glClearDepth(1.0); // Enables Clearing Of The Depth Buffer
    glEnable(GL_DEPTH_TEST); // Enable Depth Testing
    glShadeModel(GL_SMOOTH); // Enables Smooth Color Shading
    glEnable(GL_TEXTURE_2D); // Enable 2D Texture Mapping
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    
    _logo = MyImage::LoadImage("Textures/logo.bmp");
    _mask1 = MyImage::LoadImage("Textures/mask1.bmp");
    _mask2 = MyImage::LoadImage("Textures/mask2.bmp");
    _img1 = MyImage::LoadImage("Textures/image1.bmp");
    _img2 = MyImage::LoadImage("Textures/image2.bmp");
    
    glBindTexture(GL_TEXTURE_2D, _logo->GetTexture());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glBindTexture(GL_TEXTURE_2D, _mask1->GetTexture());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    glBindTexture(GL_TEXTURE_2D, _mask2->GetTexture());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    glBindTexture(GL_TEXTURE_2D, _img1->GetTexture());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    glBindTexture(GL_TEXTURE_2D, _img2->GetTexture());
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    glBindTexture(GL_TEXTURE_2D, 0);

    
    _roll = 0;
    _masking = false;
    _anotherScene = false;
    
    return true;
}

void SceneTutorial20::OnExit()
{
    SAFE_DELETE( _logo );
    SAFE_DELETE( _mask1 );
    SAFE_DELETE( _mask2 );
    SAFE_DELETE( _img1 );
    SAFE_DELETE( _img2 );
}

void SceneTutorial20::Update(float dt)
{
    Scene::Update(dt);
    
    _roll += 0.002f;
    if (_roll > 1.0f) {
        _roll -= 1.0f;
    }
}

void SceneTutorial20::Draw()
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
    
    glBindTexture(GL_TEXTURE_2D, _logo->GetTexture()); // Select Our Logo Texture
    glBegin(GL_QUADS); // Start Drawing A Textured Quad
    glTexCoord2f(0.0f, -_roll+0.0f); glVertex3f(-1.1f, -1.1f, 0.0f); // Bottom Left
    glTexCoord2f(3.0f, -_roll+0.0f); glVertex3f( 1.1f, -1.1f, 0.0f); // Bottom Right
    glTexCoord2f(3.0f, -_roll+3.0f); glVertex3f( 1.1f, 1.1f, 0.0f);  // Top Right
    glTexCoord2f(0.0f, -_roll+3.0f); glVertex3f(-1.1f, 1.1f, 0.0f);  // Top Left
    glEnd(); // Done Drawing The Quad

    
    glEnable(GL_BLEND);                         // Enable Blending
    glDisable(GL_DEPTH_TEST);                       // Disable Depth Testing
    
    if( _masking ) {
        glBlendFunc(GL_DST_COLOR,GL_ZERO);              // Blend Screen Color With Zero (Black)
    }
    
    if (_anotherScene)											// Are We Drawing The Second Scene?
    {
        glTranslatef(0.0f,0.0f,-1.0f);					// Translate Into The Screen One Unit
        glRotatef(_roll*360,0.0f,0.0f,1.0f);				// Rotate On The Z Axis 360 Degrees.
        if (_masking)									// Is Masking On?
        {
            glBindTexture(GL_TEXTURE_2D, _mask2->GetTexture());	// Select The Second Mask Texture
            glBegin(GL_QUADS);							// Start Drawing A Textured Quad
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
            glEnd();									// Done Drawing The Quad
        }
        
        glBlendFunc(GL_ONE, GL_ONE);					// Copy Image 2 Color To The Screen
        glBindTexture(GL_TEXTURE_2D, _img2->GetTexture());		// Select The Second Image Texture
        glBegin(GL_QUADS);								// Start Drawing A Textured Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
        glEnd();										// Done Drawing The Quad
    }
    else												// Otherwise
    {
        if (_masking)									// Is Masking On?
        {
            glBindTexture(GL_TEXTURE_2D, _mask1->GetTexture());	// Select The First Mask Texture
            glBegin(GL_QUADS);							// Start Drawing A Textured Quad
            glTexCoord2f(_roll+0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
            glTexCoord2f(_roll+4.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
            glTexCoord2f(_roll+4.0f, 4.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
            glTexCoord2f(_roll+0.0f, 4.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
            glEnd();									// Done Drawing The Quad
        }
        
        glBlendFunc(GL_ONE, GL_ONE);					// Copy Image 1 Color To The Screen
        glBindTexture(GL_TEXTURE_2D, _img1->GetTexture());		// Select The First Image Texture
        glBegin(GL_QUADS);								// Start Drawing A Textured Quad
        glTexCoord2f(_roll+0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
        glTexCoord2f(_roll+4.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
        glTexCoord2f(_roll+4.0f, 4.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
        glTexCoord2f(_roll+0.0f, 4.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
        glEnd();										// Done Drawing The Quad
    }
    
    glEnable(GL_DEPTH_TEST);							// Enable Depth Testing
    glDisable(GL_BLEND);								// Disable Blending
    
    
    glutSwapBuffers();
}

void SceneTutorial20::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == 'm' || key == 'M' ) {
        _masking = !_masking;
    }
    
    if( key == 's' || key == 'S' ) {
        _anotherScene = !_anotherScene;
    }
}