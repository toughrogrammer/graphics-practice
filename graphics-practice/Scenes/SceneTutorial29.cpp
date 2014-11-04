//
//  SceneTutorial29.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial29.h"


SceneTutorial29* SceneTutorial29::Create()
{
    SceneTutorial29 *pRet = new SceneTutorial29;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial29::Init()
{
    glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
    
    glShadeModel(GL_SMOOTH);									// Enables Smooth Color Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);						// This Will Clear The Background Color To Black
    glClearDepth(1.0);											// Enables Clearing Of The Depth Buffer
    glEnable(GL_DEPTH_TEST);									// Enables Depth Testing
    glDepthFunc(GL_LESS);										// The Type Of Depth Test To Do
    
    _cameraPosition.Set(0, 0, 10);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    
    img1 = MyImage::LoadImageFromRAW("Data/Monitor.raw", 256, 256, 4);
    if( img1 == NULL ) {
        return false;
    }
    
    img2 = MyImage::LoadImageFromRAW("Data/GL.raw", 256, 256, 4);
    if( img2 == NULL ) {
        return false;
    }
    
    
    MyImage::Blit(img2, img1, 127, 127, 128, 128, 64, 64, 1, 127);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, img1->GetWidth(), img1->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, img1->GetData());

    return true;
}

void SceneTutorial29::OnExit()
{

}

void SceneTutorial29::Update(float dt)
{
    Scene::Update(dt);
    
    xrot += 20.0f * dt;
    yrot += 21.0f * dt;
    zrot += 22.0f * dt;
}

void SceneTutorial29::Draw()
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
    
    
    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);
    glRotatef(zrot,0.0f,0.0f,1.0f);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    // Right Face
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
    
    glutSwapBuffers();
}

void SceneTutorial29::ProcessNormalKeys(unsigned char key, int x, int y)
{
    
}