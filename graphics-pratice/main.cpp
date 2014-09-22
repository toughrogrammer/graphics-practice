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

#define WINDOW_TITLE "Loki's Graphics Practice"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;

GLfloat     xrot;                               // X Rotation ( NEW )
GLfloat     yrot;                               // Y Rotation ( NEW )
GLfloat     zrot;                               // Z Rotation ( NEW )
GLuint      texture[1];                         // Storage For One Texture ( NEW )


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
	gluPerspective(45, ratio, 1, 100);
    
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
    
    glLoadIdentity();                           // Reset The Current Matrix
    glTranslatef(0.0f,0.0f,-5.0f);                      // Move Into The Screen 5 Units
    glRotatef(xrot,1.0f,0.0f,0.0f);                     // Rotate On The X Axis
    glRotatef(yrot,0.0f,1.0f,0.0f);                     // Rotate On The Y Axis
    glRotatef(zrot,0.0f,0.0f,1.0f);                     // Rotate On The Z Axis

    
    glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();
    
    
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1:
            exit(0);
            break;
	}
}

void MainLoop() {
    xrot += 0.3f;
    yrot += 0.2f;
    zrot += 0.4f;
    
    glutPostRedisplay();
}

bool LoadGLTextures() {
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture("Textures/NeHe.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    if(texture[0] == 0)
        return false;
    
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
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
