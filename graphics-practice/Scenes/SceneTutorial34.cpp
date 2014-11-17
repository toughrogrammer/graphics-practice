//
//  SceneTutorial34.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial34.h"


SceneTutorial34* SceneTutorial34::Create()
{
    SceneTutorial34 *pRet = new SceneTutorial34;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial34::Init()
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    
    mapData = new unsigned char[MAP_SIZE * MAP_SIZE];
    if( ! LoadRawFile("Textures/Terrain.raw", MAP_SIZE * MAP_SIZE, mapData) ) {
        return false;
    }
    

    return true;
}

void SceneTutorial34::OnExit()
{

}

void SceneTutorial34::Update(float dt)
{
    Scene::Update(dt);
    
    if( Keyboard::PressedSpecial(GLUT_KEY_UP) ) {
        scaleValue += 0.2 * dt;
    }
    else if( Keyboard::PressedSpecial(GLUT_KEY_DOWN) ) {
        scaleValue -= 0.2 * dt;
    }
}

void SceneTutorial34::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The Matrix
    
    // 			 Position	      View		Up Vector
    gluLookAt(212, 65, 194,  186, 55, 171,  0, 1, 0);	// This Determines Where The Camera's Position And View Is
    
    glScalef(scaleValue, scaleValue * HEIGHT_RATIO, scaleValue);
    
    RenderHeightMap(mapData);

    
    glutSwapBuffers();
}

void SceneTutorial34::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == ' ' ) {
        bRender = !bRender;
    }
}


bool SceneTutorial34::LoadRawFile(string path, int size, unsigned char *map)
{
    FILE *pFile = NULL;
    pFile = fopen( path.c_str(), "rb" );
    
    if ( pFile == NULL )
    {
        return false;
    }
    
    fread( map, 1, size, pFile );
    
    // After We Read The Data, It's A Good Idea To Check If Everything Read Fine
    int result = ferror( pFile );
    
    // Check If We Received An Error
    if (result)
    {
        return false;
    }
    
    // Close The File.
    fclose(pFile);
    return true;
}

int SceneTutorial34::GetHeight(unsigned char* map, int x, int y)
{
    int px = x % MAP_SIZE;
    int py = y % MAP_SIZE;
    
    return map[px + py * MAP_SIZE];
}

void SceneTutorial34::SetVertexColor(unsigned char *map, int x, int y)
{
    if( map == NULL ) {
        return;
    }
    
    float color = -0.15f + (GetHeight(map, x, y) / 256.0f);
    glColor3f(0, 0, color);
}

void SceneTutorial34::RenderHeightMap(unsigned char *map)
{
    int X = 0, Y = 0;									// Create Some Variables To Walk The Array With.
    int x, y, z;										// Create Some Variables For Readability
    
    if(!map) return;								// Make Sure Our Height Data Is Valid
    
    if(bRender)											// What We Want To Render
        glBegin( GL_QUADS );							// Render Polygons
    else
        glBegin( GL_LINES );							// Render Lines Instead
    
    for ( X = 0; X < (MAP_SIZE-STEP_SIZE); X += STEP_SIZE )
        for ( Y = 0; Y < (MAP_SIZE-STEP_SIZE); Y += STEP_SIZE )
        {
            // Get The (X, Y, Z) Value For The Bottom Left Vertex
            x = X;
            y = GetHeight(map, X, Y );
            z = Y;
            
            // Set The Color Value Of The Current Vertex
            SetVertexColor(map, x, z);
            
            glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered (Integer Points Are Faster)
            
            // Get The (X, Y, Z) Value For The Top Left Vertex
            x = X;
            y = GetHeight(map, X, Y + STEP_SIZE );
            z = Y + STEP_SIZE ;
            
            // Set The Color Value Of The Current Vertex
            SetVertexColor(map, x, z);
            
            glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered
            
            // Get The (X, Y, Z) Value For The Top Right Vertex
            x = X + STEP_SIZE;
            y = GetHeight(map, X + STEP_SIZE, Y + STEP_SIZE );
            z = Y + STEP_SIZE ;
            
            // Set The Color Value Of The Current Vertex
            SetVertexColor(map, x, z);
            
            glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered
            
            // Get The (X, Y, Z) Value For The Bottom Right Vertex
            x = X + STEP_SIZE; 
            y = GetHeight(map, X + STEP_SIZE, Y );
            z = Y;
            
            // Set The Color Value Of The Current Vertex
            SetVertexColor(map, x, z);
            
            glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered
        }
    glEnd();
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
}