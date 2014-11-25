//
//  SceneTutorial37.cpp
//  graphics-practice
//
//  Created by loki on 2014. 11. 25..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial37.h"

#include <fstream>


SceneTutorial37* SceneTutorial37::Create()
{
    SceneTutorial37 *pRet = new SceneTutorial37;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial37::Init()
{
    // Start Of User Initialization
    glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Realy Nice perspective calculations
    
    glClearColor (0.7f, 0.7f, 0.7f, 0.0f);						// Light Grey Background
    glClearDepth (1.0f);										// Depth Buffer Setup
    
    glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
    glDepthFunc (GL_LESS);										// The Type Of Depth Test To Do
    
    glShadeModel (GL_SMOOTH);									// Enables Smooth Color Shading ( NEW )
    glDisable (GL_LINE_SMOOTH);									// Initially Disable Line Smoothing ( NEW )
    
    glEnable (GL_CULL_FACE);									// Enable OpenGL Face Culling ( NEW )
    
    glDisable (GL_LIGHTING);									// Disable OpenGL Lighting ( NEW )
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);


    float shaderData[32][3];
    ifstream ifs("Data/Tutorial37/Shader.txt", ios::in);
    if( ! ifs.fail() ) {
        for( int i = 0; i < 32; i ++ ) {
            float v;
            ifs >> v;
            shaderData[i][0] = shaderData[i][1] = shaderData[i][2] = v;
        }
    }
    
    glGenTextures (1, &shaderTexture[0]);						// Get A Free Texture ID ( NEW )
    
    glBindTexture (GL_TEXTURE_1D, shaderTexture[0]);			// Bind This Texture. From Now On It Will Be 1D ( NEW )
    
    // For Crying Out Loud Don't Let OpenGL Use Bi/Trilinear Filtering! ( NEW )
    glTexParameteri (GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri (GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage1D (GL_TEXTURE_1D, 0, GL_RGB, 32, 0, GL_RGB , GL_FLOAT, shaderData);	// Upload ( NEW )
    
    lightAngle.x = 0.0f;										// Set The X Direction ( NEW )
    lightAngle.y = 0.0f;										// Set The Y Direction ( NEW )
    lightAngle.z = 1.0f;										// Set The Z Direction ( NEW )
    lightAngle.Normalize();
    
    ReadMesh();
    
    return true;
}

void SceneTutorial37::OnExit()
{
    glDeleteTextures(1,&shaderTexture[0]);
    delete[] polyData;
}

void SceneTutorial37::Update(float dt)
{
    Scene::Update(dt);
    
    modelAngle += 10 * dt;
}

void SceneTutorial37::Draw()
{
    Scene::Draw();
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.5);                        // Set The Clear Color To Black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear Screen And Depth Buffer
    glLoadIdentity();                                           // Reset The View   

    if( outlineSmooth ) {
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
    }
    else {
        glDisable(GL_LINE_SMOOTH);
    }
    
    glTranslatef (0.0f, 0.0f, -2.0f);							// Move 2 Units Away From The Screen ( NEW )
    glRotatef (modelAngle, 0.0f, 1.0f, 0.0f);					// Rotate The Model On It's Y-Axis ( NEW )
    
    float tmpShade;
    Vector3 tmpVector, tmpNormal;
    
    MATRIX tmpMat;
    glGetFloatv (GL_MODELVIEW_MATRIX, tmpMat.Data);
    
    glEnable (GL_TEXTURE_1D);									// Enable 1D Texturing ( NEW )
    glBindTexture (GL_TEXTURE_1D, shaderTexture[0]);			// Bind Our Texture ( NEW )
    
    glColor3f (1.0f, 1.0f, 1.0f);
    glBegin (GL_TRIANGLES);										// Tell OpenGL That We're Drawing Triangles
    {
        for (int i = 0; i < polyNum; i++)							// Loop Through Each Polygon ( NEW )
        {
            for (int j = 0; j < 3; j++)								// Loop Through Each Vertex ( NEW )
            {
                tmpNormal.x = polyData[i].vertices[j].normal.x;		// Fill Up The TmpNormal Structure With
                tmpNormal.y = polyData[i].vertices[j].normal.y;		// The Current Vertices' Normal Values ( NEW )
                tmpNormal.z = polyData[i].vertices[j].normal.z;
                
                RotateVector (tmpMat, tmpNormal, tmpVector);	// Rotate This By The Matrix ( NEW )
                tmpVector.Normalize();
                tmpShade = tmpVector.DotProduct(lightAngle);
                if (tmpShade < 0.0f)
                    tmpShade = 0.0f;							// Clamp The Value to 0 If Negative ( NEW )
                
                glTexCoord1f (tmpShade);						// Set The Texture Co-ordinate As The Shade Value ( NEW )
                
                const Vector3 &pos = polyData[i].vertices[j].position;
                glVertex3f(pos.x, pos.y, pos.z);
            }
        }
    }
    glEnd ();
    
    glDisable(GL_TEXTURE_1D);
    if (outlineDraw)											// Check To See If We Want To Draw The Outline ( NEW )
    {
        glEnable (GL_BLEND);									// Enable Blending ( NEW )
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Set The Blend Mode ( NEW )
        
        glPolygonMode (GL_BACK, GL_LINE);						// Draw Backfacing Polygons As Wireframes ( NEW )
        glLineWidth (outlineWidth);								// Set The Line Width ( NEW )
        
        glCullFace (GL_FRONT);									// Don't Draw Any Front-Facing Polygons ( NEW )
        
        glDepthFunc (GL_LEQUAL);								// Change The Depth Mode ( NEW )
        
        glColor3fv (&outlineColor[0]);							// Set The Outline Color ( NEW )
        
        glBegin (GL_TRIANGLES);									// Tell OpenGL What We Want To Draw
        {
            for (int i = 0; i < polyNum; i++)						// Loop Through Each Polygon ( NEW )
            {
                for (int j = 0; j < 3; j++)							// Loop Through Each Vertex ( NEW )
                {
                    const Vector3 &pos = polyData[i].vertices[j].position;
                    glVertex3f(pos.x, pos.y, pos.z);
                }
            }
        }
        glEnd ();												// Tell OpenGL We've Finished
        
        glDepthFunc (GL_LESS);									// Reset The Depth-Testing Mode ( NEW )
        
        glCullFace (GL_BACK);									// Reset The Face To Be Culled ( NEW )
        
        glPolygonMode (GL_BACK, GL_FILL);						// Reset Back-Facing Polygon Drawing Mode ( NEW )
        
        glDisable (GL_BLEND);									// Disable Blending ( NEW )
    }
    
    
    glutSwapBuffers();
}

void SceneTutorial37::ProcessNormalKeys(unsigned char key, int x, int y)
{

}


bool SceneTutorial37::ReadMesh()
{
    FILE *In = fopen ("Data/Tutorial37/Model.txt", "rb"); // Open The File
    if (!In) {
        return false; // Return FALSE If File Not Opened
    }
    
    fread (&polyNum, sizeof (int), 1, In); // Read The Header (i.e. Number Of Polygons)
    polyData = new POLYGON [polyNum]; // Allocate The Memory
    fread (&polyData[0], sizeof (POLYGON) * polyNum, 1, In);// Read In All Polygon Data
    fclose (In); // Close The File
    return true; // It Worked
}

void SceneTutorial37::RotateVector(MATRIX &mat, const Vector3 &vec, Vector3 &result)
{
    result.x = (mat.Data[0] * vec.x) + (mat.Data[4] * vec.y) + (mat.Data[8] * vec.z); // Rotate Around The X Axis
    result.y = (mat.Data[1] * vec.x) + (mat.Data[5] * vec.y) + (mat.Data[9] * vec.z); // Rotate Around The Y Axis
    result.z = (mat.Data[2] * vec.x) + (mat.Data[6] * vec.y) + (mat.Data[10] * vec.z); // Rotate Around The Z Axis
}