//
//  SceneTutorial12.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial12.h"


static GLfloat boxcol[5][3]=                                // Array For Box Colors
{
    // Bright:  Red, Orange, Yellow, Green, Blue
    {1.0f,0.0f,0.0f},{1.0f,0.5f,0.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,1.0f,1.0f}
};

static GLfloat topcol[5][3]=                                // Array For Top Colors
{
    // Dark:  Red, Orange, Yellow, Green, Blue
    {.5f,0.0f,0.0f},{0.5f,0.25f,0.0f},{0.5f,0.5f,0.0f},{0.0f,0.5f,0.0f},{0.0f,0.5f,0.5f}
};

SceneTutorial12* SceneTutorial12::Create()
{
    SceneTutorial12 *pRet = new SceneTutorial12;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial12::Init()
{
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable(GL_LIGHT0);								// Quick And Dirty Lighting (Assumes Light0 Is Set Up)
    glEnable(GL_LIGHTING);								// Enable Lighting
    glEnable(GL_COLOR_MATERIAL);						// Enable Material Coloring
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    

    BuildLists();
    
    _image = MyImage::LoadImage("Textures/Cube.bmp");
    
    _xrot = 0;
    _yrot = 0;
    
    
    return true;
}

void SceneTutorial12::OnExit()
{
    SAFE_DELETE( _image );
}

void SceneTutorial12::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial12::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    
    glBindTexture(GL_TEXTURE_2D, _image->GetTexture());
    for (int yloop=1;yloop<6;yloop++)
    {
        for (int xloop=0;xloop<yloop;xloop++)
        {
            glLoadIdentity();							// Reset The View
            
            float new_x = 1.4f+(float(xloop)*2.8f)-(float(yloop)*1.4f);
            float new_y = ((6.0f-float(yloop))*2.4f)-7.0f;
            float new_angle_x = 45.0f-(2.0f*yloop)+_xrot;
            float new_angle_y = 45.0f + _yrot;
            
            glTranslatef( new_x, new_y, -20.0f );
            glRotatef( new_angle_x, 1.0f, 0.0f, 0.0f );
            glRotatef( new_angle_y, 0.0f, 1.0f, 0.0f );

            glColor3fv( boxcol[yloop-1] );
            glCallList( _box );
            
            glColor3fv( topcol[yloop-1] );
            glCallList( _top );
        }
    }
    
    glutSwapBuffers();
}

void SceneTutorial12::ProcessSpecialKeys(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_UP:
            _xrot -= 0.2f;
            break;
        case GLUT_KEY_DOWN:
            _xrot += 0.2f;
            break;
        case GLUT_KEY_LEFT:
            _yrot -= 0.2f;
            break;
        case GLUT_KEY_RIGHT:
            _yrot += 0.2f;
            break;
    }
}

void SceneTutorial12::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void SceneTutorial12::BuildLists()
{
    _box = glGenLists(2);
    glNewList(_box, GL_COMPILE);
    glBegin(GL_QUADS);
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    // Right face
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
    glEndList();

    _top = _box + 1;											// Storage For "Top" Is "Box" Plus One
    glNewList(_top, GL_COMPILE);							// Now The "Top" Display List
    glBegin(GL_QUADS);
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glEnd();
    glEndList();
}