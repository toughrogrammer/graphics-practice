//
//  SceneTutorial26.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial26.h"


SceneTutorial26* SceneTutorial26::Create()
{
    SceneTutorial26 *pRet = new SceneTutorial26;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial26::Init()
{
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.2f, 0.5f, 1.0f, 1.0f);                   // Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glClearStencil(0);                          // Clear The Stencil Buffer To 0
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    glEnable(GL_TEXTURE_2D);                        // Enable 2D Texture Mapping

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);             // Set The Ambient Lighting For Light0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);             // Set The Diffuse Lighting For Light0
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);                // Set The Position For Light0
     
    glEnable(GL_LIGHT0);                            // Enable Light 0
    glEnable(GL_LIGHTING);                          // Enable Lighting

    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    

    imageEnv = MyImage::LoadImage("Textures/Envroll.bmp");
    imageFloor = MyImage::LoadImage("Textures/Envwall.bmp");
    imageBall = MyImage::LoadImage("Textures/Ball.bmp");


    q = gluNewQuadric();                            // Create A New Quadratic
    gluQuadricNormals(q, GL_SMOOTH);                    // Generate Smooth Normals For The Quad
    gluQuadricTexture(q, GL_TRUE);                      // Enable Texture Coords For The Quad
 
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);            // Set Up Sphere Mapping
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);            // Set Up Sphere Mapping

    return true;
}

void SceneTutorial26::OnExit()
{

}

void SceneTutorial26::Update(float dt)
{
    Scene::Update(dt);

    xrot += xrotspeed * dt;                                  // Update X Rotation Angle By xrotspeed
    yrot += yrotspeed * dt;                                  // Update Y Rotation Angle By yrotspeed
    
    if( Keyboard::PressedNormal('A') || Keyboard::PressedNormal('a') ) {
        zoom += 0.05f;
    }
    if( Keyboard::PressedNormal('Z') || Keyboard::PressedNormal('z') ) {
        zoom -= 0.05f;
    }
    
    if( Keyboard::PressedSpecial(GLUT_KEY_UP) ) {
        height += 0.03;
    }
    if( Keyboard::PressedSpecial(GLUT_KEY_DOWN) ) {
        height -= 0.03;
    }
}

void SceneTutorial26::Draw()
{
    Scene::Draw();
    
    // Clear Screen, Depth Buffer & Stencil Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Clip Plane Equations
    double eqr[] = {0.0f, -1.0f, 0.0f, 0.0f};            // Plane Equation To Use For The Reflected Objects

    glLoadIdentity();                                   // Reset The Modelview Matrix
    glTranslatef(0.0f, -0.6f, zoom);                    // Zoom And Raise Camera Above The Floor (Up 0.6 Units)
    glColorMask(0,0,0,0);                               // Set Color Mask
    glEnable(GL_STENCIL_TEST);                          // Enable Stencil Buffer For "marking" The Floor
    glStencilFunc(GL_ALWAYS, 1, 1);                     // Always Passes, 1 Bit Plane, 1 As Mask
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);          // We Set The Stencil Buffer To 1 Where We Draw Any Polygon
                                                        // Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
                                                        // Replace If Test Passes
    glDisable(GL_DEPTH_TEST);                           // Disable Depth Testing
    DrawFloor();                                        // Draw The Floor (Draws To The Stencil Buffer)
                                                        // We Only Want To Mark It In The Stencil Buffer
    glEnable(GL_DEPTH_TEST);                            // Enable Depth Testing
    glColorMask(1,1,1,1);                               // Set Color Mask to TRUE, TRUE, TRUE, TRUE
    glStencilFunc(GL_EQUAL, 1, 1);                      // We Draw Only Where The Stencil Is 1
                                                        // (I.E. Where The Floor Was Drawn)
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);             // Don't Change The Stencil Buffer
    glEnable(GL_CLIP_PLANE0);                           // Enable Clip Plane For Removing Artifacts
                                                        // (When The Object Crosses The Floor)
    glClipPlane(GL_CLIP_PLANE0, eqr);                   // Equation For Reflected Objects
    glPushMatrix();                                     // Push The Matrix Onto The Stack
        glScalef(1.0f, -1.0f, 1.0f);                    // Mirror Y Axis
        glLightfv(GL_LIGHT0, GL_POSITION, LightPos);    // Set Up Light0
        glTranslatef(0.0f, height, 0.0f);               // Position The Object
        glRotatef(xrot, 1.0f, 0.0f, 0.0f);              // Rotate Local Coordinate System On X Axis
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);              // Rotate Local Coordinate System On Y Axis
        DrawObject();                                   // Draw The Sphere (Reflection)
    glPopMatrix();                                      // Pop The Matrix Off The Stack
    glDisable(GL_CLIP_PLANE0);                          // Disable Clip Plane For Drawing The Floor
    glDisable(GL_STENCIL_TEST);                         // We Don't Need The Stencil Buffer Any More (Disable)
    
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);        // Set Up Light0 Position
    glEnable(GL_BLEND);                                 // Enable Blending (Otherwise The Reflected Object Wont Show)
    glDisable(GL_LIGHTING);                             // Since We Use Blending, We Disable Lighting
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);                  // Set Color To White With 80% Alpha
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Blending Based On Source Alpha And 1 Minus Dest Alpha
    DrawFloor();                                        // Draw The Floor To The Screen
    glEnable(GL_LIGHTING);                              // Enable Lighting
    glDisable(GL_BLEND);                                // Disable Blending
    glTranslatef(0.0f, height, 0.0f);                   // Position The Ball At Proper Height
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);                  // Rotate On The X Axis
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);                  // Rotate On The Y Axis
    DrawObject();                                       // Draw The Ball
    
    glutSwapBuffers();
}

void SceneTutorial26::ProcessNormalKeys(unsigned char key, int x, int y)
{

}

void SceneTutorial26::ProcessSpecialKeys(int key, int x, int y)
{

}

void SceneTutorial26::DrawObject()                                       // Draw Our Ball
{
    glColor3f(1.0f, 1.0f, 1.0f);                        // Set Color To White
    glBindTexture(GL_TEXTURE_2D, imageBall->GetTexture());           // Select Texture 2 (1)
    gluSphere(q, 0.35f, 32, 16);                        // Draw First Sphere

    glBindTexture(GL_TEXTURE_2D, imageEnv->GetTexture());           // Select Texture 3 (2)
    glColor4f(1.0f, 1.0f, 1.0f, 0.4f);                  // Set Color To White With 40% Alpha
    glEnable(GL_BLEND);                                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);                  // Set Blending Mode To Mix Based On SRC Alpha
    glEnable(GL_TEXTURE_GEN_S);                         // Enable Sphere Mapping
    glEnable(GL_TEXTURE_GEN_T);                         // Enable Sphere Mapping

    gluSphere(q, 0.35f, 32, 16);                        // Draw Another Sphere Using New Texture
                                                        // Textures Will Mix Creating A MultiTexture Effect (Reflection)
    glDisable(GL_TEXTURE_GEN_S);                        // Disable Sphere Mapping
    glDisable(GL_TEXTURE_GEN_T);                        // Disable Sphere Mapping
    glDisable(GL_BLEND);                                // Disable Blending
}

void SceneTutorial26::DrawFloor()                                        // Draws The Floor
{
    glBindTexture(GL_TEXTURE_2D, imageFloor->GetTexture());           // Select Texture 1 (0)
    glBegin(GL_QUADS);                                  // Begin Drawing A Quad
        glNormal3f(0.0, 1.0, 0.0);                      // Normal Pointing Up
            glTexCoord2f(0.0f, 1.0f);                   // Bottom Left Of Texture
            glVertex3f(-2.0, 0.0, 2.0);                 // Bottom Left Corner Of Floor
            
            glTexCoord2f(0.0f, 0.0f);                   // Top Left Of Texture
            glVertex3f(-2.0, 0.0,-2.0);                 // Top Left Corner Of Floor
            
            glTexCoord2f(1.0f, 0.0f);                   // Top Right Of Texture
            glVertex3f( 2.0, 0.0,-2.0);                 // Top Right Corner Of Floor
            
            glTexCoord2f(1.0f, 1.0f);                   // Bottom Right Of Texture
            glVertex3f( 2.0, 0.0, 2.0);                 // Bottom Right Corner Of Floor
    glEnd();                                            // Done Drawing The Quad
}