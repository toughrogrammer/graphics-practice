//
//  SceneTutorial18.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial18.h"


SceneTutorial18* SceneTutorial18::Create()
{
    SceneTutorial18 *pRet = new SceneTutorial18;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial18::Init()
{
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
    glEnable(GL_LIGHTING);
    
    _cameraPosition.Set(0, 0, 5);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    MyImage *wallImage = MyImage::LoadImage("Textures/Wall.bmp");
    {
        glGenTextures(3, &_texture[0]);
        
        glBindTexture(GL_TEXTURE_2D, _texture[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, wallImage->GetWidth(), wallImage->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, wallImage->GetData());
        
        glBindTexture(GL_TEXTURE_2D, _texture[1]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, wallImage->GetWidth(), wallImage->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, wallImage->GetData());
        
        glBindTexture(GL_TEXTURE_2D, _texture[2]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, wallImage->GetWidth(), wallImage->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, wallImage->GetData());
        
        _cube = Cube::Create(wallImage->GetTexture(), 2.0f);
        _cube->SetPosition( Vector3(0, 0, 0) );
    }
    SAFE_DELETE(wallImage);
    
    _quadratic = gluNewQuadric();
    gluQuadricNormals(_quadratic, GLU_SMOOTH);
    gluQuadricTexture(_quadratic, GL_TRUE);
    
    _filter = 0;
    _objectType = 1;
    _part1 = _part2 = 0;
    _p1 = 0;
    _p2 = 1;
    
    _xrot = _yrot = 0;
    
    return true;
}

void SceneTutorial18::OnExit()
{
    
}

void SceneTutorial18::Update(float dt)
{
    Scene::Update(dt);
    
    _xrot += 30 * dt;
    _yrot += 40 * dt;
}

void SceneTutorial18::Draw()
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
    
    
    glRotatef(_xrot,1.0f,0.0f,0.0f);
    glRotatef(_yrot,0.0f,1.0f,0.0f);
    glBindTexture(GL_TEXTURE_2D, _texture[_filter]);
    
    switch(_objectType)
    {
        case 0:
            _cube->Draw();
            break;
        case 1:
            glTranslatef(0.0f,0.0f,-1.5f);					// Center The Cylinder
            gluCylinder(_quadratic,1.0f,1.0f,3.0f,32,32);	// A Cylinder With A Radius Of 0.5 And A Height Of 2
            break;
        case 2:
            gluDisk(_quadratic,0.5f,1.5f,32,32);				// Draw A Disc (CD Shape) With An Inner Radius Of 0.5, And An Outer Radius Of 2.  Plus A Lot Of Segments ;)
            break;
        case 3:
            gluSphere(_quadratic,1.3f,32,32);				// Draw A Sphere With A Radius Of 1 And 16 Longitude And 16 Latitude Segments
            break;
        case 4:
            glTranslatef(0.0f,0.0f,-1.5f);					// Center The Cone
            gluCylinder(_quadratic,1.0f,0.0f,3.0f,32,32);	// A Cone With A Bottom Radius Of .5 And A Height Of 2
            break;
        case 5:
            _part1 += _p1;
            _part2 += _p2;
            
            if(_part1>359)									// 360 Degrees
            {
                _p1=0;
                _part1=0;
                _p2=1;
                _part2=0;
            }
            if(_part2>359)									// 360 Degrees
            {
                _p1=1;
                _p2=0;
            }
            gluPartialDisk(_quadratic,0.5f,1.5f,32,32,_part1,_part2-_part1);	// A Disk Like The One Before
            break;
    };
    
    glutSwapBuffers();
}

void SceneTutorial18::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == 'f' || key == 'F' ) {
        _filter = (_filter + 1) % 3;
        _cube->SetTexture( _texture[ _filter ] );
    }
    
    if( key == 'n' || key == 'N' ) {
        _objectType = (_objectType + 1) % 6;
    }
}