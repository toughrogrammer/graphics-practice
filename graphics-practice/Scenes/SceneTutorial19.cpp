//
//  SceneTutorial19.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial19.h"
#define NUM_OF_PARTICLE 100


SceneTutorial19* SceneTutorial19::Create()
{
    SceneTutorial19 *pRet = new SceneTutorial19;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial19::Init()
{
    glShadeModel(GL_SMOOTH);                        // Enables Smooth Shading
    glClearColor(0.0f,0.0f,0.0f,0.0f);                  // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
    glEnable(GL_BLEND);                         // Enable Blending
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);                   // Type Of Blending To Perform
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);           // Really Nice Perspective Calculations
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);                 // Really Nice Point Smoothing
    glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping
    
    _cameraPosition.Set(0, 0, 5);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    srand( (unsigned)time(NULL) );
    
    _particleImage = MyImage::LoadImage("Textures/Particle.bmp");
    for( int i = 0; i < NUM_OF_PARTICLE; i ++ ) {
        Particle *particle = new Particle();
        particle->_active = true;
        particle->_life = 1.0f;
        particle->_fade = float( rand() % 100 ) / 1000.0f + 0.003f;
        particle->_r = Random0to1();
        particle->_g = Random0to1();
        particle->_b = Random0to1();
        particle->_position.Set(0.0f, 0.0f, 0.0f);
        particle->_movement.Set(RandomRangeDouble(-25, 25), RandomRangeDouble(-25, 25), RandomRangeDouble(-25, 25));
        particle->_gravity.Set(0.0f, -0.8f, 0.0f);
        
        _particles.push_back( particle );
    }
    
    return true;
}

void SceneTutorial19::OnExit()
{
    for( int i = 0; i < NUM_OF_PARTICLE; i ++ ) {
        SAFE_DELETE( _particles[i] );
    }
    SAFE_DELETE( _particleImage );
}

void SceneTutorial19::Update(float dt)
{
    Scene::Update(dt);
    
    float slowdown = 2.0f;
    for( int i = 0; i < NUM_OF_PARTICLE; i ++ ) {
        Particle *particle = _particles[i];
        particle->_position += particle->_movement / (slowdown * 1000);
        particle->_movement += particle->_gravity;
        particle->_life -= particle->_fade;
        if( particle->_life < 0.0f ) {
            particle->_life = 1.0f;
            particle->_fade = float(rand()%100)/1000.0f+0.003f;
            particle->_position.Set(0.0f, 0.0f, 0.0f);
            particle->_movement.Set(RandomRangeDouble(-25, 25), RandomRangeDouble(-25, 25), RandomRangeDouble(-25, 25));
            particle->_r = Random0to1();
            particle->_g = Random0to1();
            particle->_b = Random0to1();
        }
    }
    
    if( Keyboard::PressedSpecial(GLUT_KEY_UP) ) {
        _cameraPosition.z -= 5.0f * dt;
    }
    if( Keyboard::PressedSpecial(GLUT_KEY_DOWN) ) {
        _cameraPosition.z += 5.0f * dt;
    }
}

void SceneTutorial19::Draw()
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
    
    glBindTexture(GL_TEXTURE_2D, _particleImage->GetTexture());                // Select Our Texture
    for( int i = 0; i < NUM_OF_PARTICLE; i ++ ) {
        Particle *particle = _particles[i];
        if( ! particle->_active ) {
            continue;
        }
        
        float x = particle->_position.x;
        float y = particle->_position.y;
        float z = particle->_position.z;
        
        glColor4f(particle->_r, particle->_g, particle->_b, particle->_life);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
        glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
        glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
        glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
        glEnd();
    }
    
    glutSwapBuffers();
}