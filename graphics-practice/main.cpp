//
//  main.cpp
//  graphics-pratice
//
//  Created by loki on 2014. 9. 15..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "SOIL.h"

#include "MyImage.h"
#include "Sprite.h"
#include "RubiksCube3.h"

#define WINDOW_TITLE "Loki's Graphics Practice"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;

GLfloat	xrot;				// X Rotation
GLfloat	yrot;				// Y Rotation
GLfloat zrot;               // Z Rotation
GLfloat xspeed;				// X Rotation Speed
GLfloat yspeed;				// Y Rotation Speed

Vector3 position;

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };
bool	light;				// Lighting ON/OFF
bool    blend;

GLuint	filter;				// Which Filter To Use
GLuint	texture[3];			// Storage For 3 Textures


Sprite *spriteGrass = NULL;

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
    
    // Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    
	float ratio = w * 1.0 / h;
    
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 10000);
    
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();
    
    // move camera
    // camera move direction must be inverse
    glTranslatef( -position.x, -position.y, -position.z );
    
    spriteGrass->Draw();
    
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
    
    if (key == 'l' || key == 'L' ) {
        light=!light;
        if (!light)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }
    }
    
    if( key == 'f' || key == 'F' ) {
        filter+=1;
        if (filter>2)
        {
            filter=0;
        }
        
        cout << "current filter : " << filter << endl;
    }
    
    if ( key == 'b' || key == 'B' ) {
        blend = !blend;
        if(blend)
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

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1:
            exit(0);
            break;
        case GLUT_KEY_LEFT:
            position.x -= 1.0f;
            break;
        case GLUT_KEY_RIGHT:
            position.x += 1.0f;
            break;
        case GLUT_KEY_UP:
            position.y += 1.0f;
            break;
        case GLUT_KEY_DOWN:
            position.y -= 1.0f;
            break;
	}
    
    cout << position.x << " " << position.y << " " << position.z << endl;
}

void MainLoop() {
    xrot += 0.3f;
    yrot += 0.2f;
    zrot += 0.4f;
    
    glutPostRedisplay();
}

bool LoadGLTextures() {
    spriteGrass = Sprite::Create("Textures/grass.jpg");
    if( spriteGrass == NULL ) {
        return false;
    }
    
    spriteGrass->SetPosition( Vector3( 0, -30, -1000 ) );
    spriteGrass->SetRotation( Vector3( -80, 0, 0 ) );
    return true;
}

bool InitGL() {
    if (!LoadGLTextures())                          // Jump To Texture Loading Routine ( NEW )
    {
        return false;                           // If Texture Didn't Load Return FALSE ( NEW )
    }
    
    glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
    glEnable(GL_LIGHT1);								// Enable Light One
    
    // set camera position
    position.Set( 0, 100, -20 );
    
    return true;
}



int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   	glutCreateWindow(WINDOW_TITLE);
    
	// register callbacks
	glutDisplayFunc(&renderScene);
	glutReshapeFunc(&changeSize);
    
    // set my main loop callback function
    glutIdleFunc(&MainLoop);
    
    // here are the new entries
	glutKeyboardFunc(&processNormalKeys);
	glutSpecialFunc(&processSpecialKeys);
    
    if( ! InitGL() ) {
        return 0;
    }
    
	// enter GLUT event processing loop
	glutMainLoop();
    
	return 0;
}
