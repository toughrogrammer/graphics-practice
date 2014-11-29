//
//  SceneTutorial38.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial38.h"


SceneTutorial38* SceneTutorial38::Create()
{
    SceneTutorial38 *pRet = new SceneTutorial38;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial38::Init()
{
    glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
    glClearDepth (1.0f);										// Depth Buffer Setup
    glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
    glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
    glShadeModel (GL_SMOOTH);									// Select Smooth Shading
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
    glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
    glBlendFunc(GL_ONE,GL_SRC_ALPHA);							// Set Blending Mode (Cheap / Quick)
    glEnable(GL_BLEND);											// Enable Blending
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    MyImage *img = NULL;
    img = MyImage::LoadImage("Textures/Butterfly1.bmp");
    _images.push_back(img);
    img = MyImage::LoadImage("Textures/Butterfly2.bmp");
    _images.push_back(img);
    img = MyImage::LoadImage("Textures/Butterfly3.bmp");
    _images.push_back(img);
    
    for( unsigned int i = 0; i < _images.size(); i ++ ) {
        _textures.push_back( _images[i]->GetTexture() );
        cout << _textures[i] << endl;
    }
    
    _objects.resize(50);
    for( unsigned int i = 0; i < _objects.size(); i ++ ) {
        ResetObject(_objects[i]);
    }
    

    return true;
}

void SceneTutorial38::OnExit()
{

}

void SceneTutorial38::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial38::Draw()
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
    
    glPushMatrix();
    for( unsigned int i = 0; i < _objects.size(); i ++ ) {
        Object &obj = _objects[i];
        
        glLoadIdentity ();										// Reset The Modelview Matrix
        glBindTexture(GL_TEXTURE_2D, obj.tex);	// Bind Our Texture
        glTranslatef(obj.pos.x, obj.pos.y, obj.pos.z);		// Position The Object
        glRotatef(45.0f, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis
        glRotatef((obj.spinz),0.0f,0.0f,1.0f);			// Spin On The Z-Axis
        
        glBegin(GL_TRIANGLES);
        glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f, obj.flap);
        glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
        glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f,-1.0f, obj.flap);
        glEnd();
        
        obj.pos.y -= obj.yi;
        obj.spinz += obj.spinzi;
        obj.flap += obj.fi;
        
        if (obj.pos.y < -18.0f)									// Is Object Off The Screen?
        {
            ResetObject(obj);									// If So, Reassign New Values
        }
        
        if ((obj.flap > 1.0f) || (obj.flap < -1.0f))	// Time To Change Flap Direction?
        {
            obj.fi = -obj.fi;
        }
    }
    glPopMatrix();
    
    
    glutSwapBuffers();
}

void SceneTutorial38::ProcessNormalKeys(unsigned char key, int x, int y)
{

}


void SceneTutorial38::ResetObject(SceneTutorial38::Object &obj)
{
    obj.tex = _textures[rand()%_textures.size()];
    cout << obj.tex << endl;
    obj.pos.Set(rand() % 34 - 17.0f, 18.0f, -((rand()%30000/1000.0f)+10.0f));
    obj.spinzi=(rand()%10000)/5000.0f-1.0f;				// spinzi Is A Random Value From -1.0f To 1.0f
    obj.flap=0.0f;										// flap Starts Off At 0.0f;
    obj.fi=0.05f+(rand()%100)/1000.0f;					// fi Is A Random Value From 0.05f To 0.15f
    obj.yi=0.001f+(rand()%1000)/10000.0f;					// yi Is A Random Value From 0.001f To 0.101f
}