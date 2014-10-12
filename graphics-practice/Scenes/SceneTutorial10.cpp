//
//  SceneTutorial9.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 30..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial10.h"
#include <math.h>


const float piover180 = 0.0174532925f;
float heading;


SceneTutorial10* SceneTutorial10::Create()
{
    SceneTutorial10 *pRet = new SceneTutorial10;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial10::Init()
{
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// This Will Clear The Background Color To Black
    glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    SetupWorld();
    
    _mudImage = MyImage::LoadImage("Textures/Mud.bmp");
    
    _yrot = 0;
    _walkbias = 0;
    _walkbiasangle = 0;
    _lookupdown = 0;
    
    return true;
}

void SceneTutorial10::OnExit()
{
    SAFE_DELETE( _mudImage );
}

void SceneTutorial10::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial10::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The View
    
    GLfloat x_m, y_m, z_m, u_m, v_m;
    GLfloat xtrans = -_pos.x;
    GLfloat ztrans = -_pos.z;
    GLfloat ytrans = -_walkbias-0.25f;
    GLfloat sceneroty = 360.0f - _yrot;
    
    int numtriangles;
    
    glRotatef(_lookupdown,1.0f,0,0);
    glRotatef(sceneroty,0,1.0f,0);
    
    glTranslatef(xtrans, ytrans, ztrans);
    glBindTexture(GL_TEXTURE_2D, _mudImage->GetTexture());
    
    numtriangles = _sector.numOfTriangles;
    
    // Process Each Triangle
    for (int loop_m = 0; loop_m < numtriangles; loop_m++)
    {
        glBegin(GL_TRIANGLES);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        x_m = _sector.triangles[loop_m].vertex[0].x;
        y_m = _sector.triangles[loop_m].vertex[0].y;
        z_m = _sector.triangles[loop_m].vertex[0].z;
        u_m = _sector.triangles[loop_m].vertex[0].u;
        v_m = _sector.triangles[loop_m].vertex[0].v;
        glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
        
        x_m = _sector.triangles[loop_m].vertex[1].x;
        y_m = _sector.triangles[loop_m].vertex[1].y;
        z_m = _sector.triangles[loop_m].vertex[1].z;
        u_m = _sector.triangles[loop_m].vertex[1].u;
        v_m = _sector.triangles[loop_m].vertex[1].v;
        glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
        
        x_m = _sector.triangles[loop_m].vertex[2].x;
        y_m = _sector.triangles[loop_m].vertex[2].y;
        z_m = _sector.triangles[loop_m].vertex[2].z;
        u_m = _sector.triangles[loop_m].vertex[2].u;
        v_m = _sector.triangles[loop_m].vertex[2].v;
        glTexCoord2f(u_m,v_m); glVertex3f(x_m,y_m,z_m);
        glEnd();
    }
    
    glutSwapBuffers();
}

void SceneTutorial10::ProcessSpecialKeys(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_UP:
        {
            _pos.x -= (float)sin(heading * piover180) * 0.05f;
            _pos.z -= (float)cos(heading * piover180) * 0.05f;
            if( _walkbiasangle >= 359.0f ) {
                _walkbiasangle = 0.0f;
            }
            else {
                _walkbiasangle += 10.0f;
            }
            _walkbias = (float)sin(_walkbiasangle * piover180)/20.0f;
        }
            break;
        case GLUT_KEY_DOWN:
        {
            _pos.x += (float)sin(heading * piover180) * 0.05f;
            _pos.z += (float)cos(heading * piover180) * 0.05f;
            if( _walkbiasangle <= 1.0f ) {
                _walkbiasangle = 359.0f;
            }
            else {
                _walkbiasangle -= 10.0f;
            }
            _walkbias = (float)sin(_walkbiasangle * piover180)/20.0f;
        }
            break;
        case GLUT_KEY_LEFT:
            heading += 1.0f;
            _yrot = heading;
            break;
        case GLUT_KEY_RIGHT:
            heading -= 1.0f;
            _yrot = heading;
            break;
    }
}

void SceneTutorial10::ProcessNormalKeys(unsigned char key, int x, int y)
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

void SceneTutorial10::readstr(FILE *fp, char *string)
{
    do
    {
        fgets(string, 255, fp);
    } while ((string[0] == '/') || (string[0] == '\n'));
    return;
}

void SceneTutorial10::SetupWorld()
{
    float x, y, z, u, v;
    int numtriangles;
    FILE *filein;
    char oneline[255];
    filein = fopen("Data/World.txt", "rt");				// File To Load World Data From
    
    readstr(filein,oneline);
    sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);
    
    _sector.numOfTriangles = numtriangles;
    for (int loop = 0; loop < numtriangles; loop++)
    {
        Triangle triangle;
        for (int vert = 0; vert < 3; vert++)
        {
            readstr(filein,oneline);
            sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
            cout << loop << " " << oneline << endl;
            
            triangle.vertex[vert].x = x;
            triangle.vertex[vert].y = y;
            triangle.vertex[vert].z = z;
            triangle.vertex[vert].u = u;
            triangle.vertex[vert].v = v;
        }
        
        _sector.triangles.push_back( triangle );
    }
    
    fclose(filein);
    return;
}
