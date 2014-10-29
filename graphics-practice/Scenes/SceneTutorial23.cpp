//
//  SceneTutorial23.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial23.h"


SceneTutorial23* SceneTutorial23::Create()
{
    SceneTutorial23 *pRet = new SceneTutorial23;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial23::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear The Background Color To Black
    glClearDepth(1.0); // Enables Clearing Of The Depth Buffer
    glEnable(GL_DEPTH_TEST); // Enable Depth Testing
    glShadeModel(GL_SMOOTH); // Enables Smooth Color Shading
    glEnable(GL_TEXTURE_2D); // Enable 2D Texture Mapping
    
    _cameraPosition.Set(0, 0, 10);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One
    
    quadratic=gluNewQuadric();							// Create A Pointer To The Quadric Object (Return 0 If No Memory)
    gluQuadricNormals(quadratic, GLU_SMOOTH);			// Create Smooth Normals
    gluQuadricTexture(quadratic, GL_TRUE);				// Create Texture Coords
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)

    
    imgBackground = MyImage::LoadImage("Textures/BG.bmp");
    imgReflect = MyImage::LoadImage("Textures/Reflect.bmp");
    
    object = 0;
    rotObject.Set(0, 0, 0);
    
    return true;
}

void SceneTutorial23::OnExit()
{
    SAFE_DELETE( imgBackground );
    SAFE_DELETE( imgReflect );
}

void SceneTutorial23::Update(float dt)
{
    Scene::Update(dt);
    
    rotObject.x += 5.0f * dt;
    rotObject.y += 4.0f * dt;
    
    if( Keyboard::PressedNormal('w') || Keyboard::PressedNormal('W') ) {
        _cameraPosition.z -= 1.0f * dt;
    }
    if( Keyboard::PressedNormal('s') || Keyboard::PressedNormal('S') ) {
        _cameraPosition.z += 1.0f * dt;
    }
    if( Keyboard::PressedNormal('a') || Keyboard::PressedNormal('A') ) {
        _cameraPosition.x -= 1.0f * dt;
    }
    if( Keyboard::PressedNormal('d') || Keyboard::PressedNormal('D') ) {
        _cameraPosition.x += 1.0f * dt;
    }
    if( Keyboard::PressedSpecial(GLUT_KEY_UP) ) {
        _cameraPosition.y += 1.0f * dt;
    }
    if( Keyboard::PressedSpecial(GLUT_KEY_DOWN) ) {
        _cameraPosition.y -= 1.0f * dt;
    }
}

void SceneTutorial23::Draw()
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
    
    glEnable(GL_TEXTURE_GEN_S);							// Enable Texture Coord Generation For S (NEW)
    glEnable(GL_TEXTURE_GEN_T);							// Enable Texture Coord Generation For T (NEW)
    
    glBindTexture(GL_TEXTURE_2D, imgReflect->GetTexture()); // This Will Select The Sphere Map
    glPushMatrix();
    glRotatef(rotObject.x,1.0f,0.0f,0.0f);
    glRotatef(rotObject.y,0.0f,1.0f,0.0f);
    switch(object)
    {
        case 0:
            glDrawCube();
            break;
        case 1:
            glTranslatef(0.0f,0.0f,-1.5f);					// Center The Cylinder
            gluCylinder(quadratic,1.0f,1.0f,3.0f,32,32);	// A Cylinder With A Radius Of 0.5 And A Height Of 2
            break;
        case 2:
            gluSphere(quadratic,1.3f,32,32);				// Draw A Sphere With A Radius Of 1 And 16 Longitude And 16 Latitude Segments
            break;
        case 3:
            glTranslatef(0.0f,0.0f,-1.5f);					// Center The Cone
            gluCylinder(quadratic,1.0f,0.0f,3.0f,32,32);	// A Cone With A Bottom Radius Of .5 And A Height Of 2
            break;
    };
    
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    
    glBindTexture(GL_TEXTURE_2D, imgBackground->GetTexture());	// This Will Select The BG Maps...
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -24.0f);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-13.3f, -10.0f,  10.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 13.3f, -10.0f,  10.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 13.3f,  10.0f,  10.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-13.3f,  10.0f,  10.0f);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void SceneTutorial23::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == ' ' ) {
        object = (object + 1) % 4;
    }
}

void SceneTutorial23::glDrawCube()
{
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    // Back Face
    glNormal3f( 0.0f, 0.0f,-0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    // Top Face
    glNormal3f( 0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    // Bottom Face
    glNormal3f( 0.0f,-0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    // Right Face
    glNormal3f( 0.5f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    // Left Face
    glNormal3f(-0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
}