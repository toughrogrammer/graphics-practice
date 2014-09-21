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

#define WINDOW_TITLE "Loki's Graphics Practice"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;

float tAngle = 0;
float qAngle = 0;


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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity(); // Reset The View
    
    glTranslatef(-1.5f,0.0f,-8.0f); // Move Left And Into The Screen
    glRotatef(tAngle,0.0f,1.0f,0.0f); // Rotate The Pyramid On It's Y Axis
    
    glBegin(GL_TRIANGLES); // Drawing Using Triangles

    glColor3f(1.0f,0.0f,0.0f); // Red
    glVertex3f( 0.0f, 1.0f, 0.0f); // Top Of Triangle (Front)
    glColor3f(0.0f,1.0f,0.0f); // Green
    glVertex3f(-1.0f,-1.0f, 1.0f); // Left Of Triangle (Front)
    glColor3f(0.0f,0.0f,1.0f); // Blue
    glVertex3f( 1.0f,-1.0f, 1.0f); // Right Of Triangle (Front)
    
    glColor3f(1.0f,0.0f,0.0f); // Red
    glVertex3f( 0.0f, 1.0f, 0.0f); // Top Of Triangle (Right)
    glColor3f(0.0f,0.0f,1.0f); // Blue
    glVertex3f( 1.0f,-1.0f, 1.0f); // Left Of Triangle (Right)
    glColor3f(0.0f,1.0f,0.0f); // Green
    glVertex3f( 1.0f,-1.0f, -1.0f); // Right Of Triangle (Right)
    
    glColor3f(1.0f,0.0f,0.0f); // Red
    glVertex3f( 0.0f, 1.0f, 0.0f); // Top Of Triangle (Back)
    glColor3f(0.0f,1.0f,0.0f); // Green
    glVertex3f( 1.0f,-1.0f, -1.0f); // Left Of Triangle (Back)
    glColor3f(0.0f,0.0f,1.0f); // Blue
    glVertex3f(-1.0f,-1.0f, -1.0f); // Right Of Triangle (Back)
    
    glColor3f(1.0f,0.0f,0.0f); // Red
    glVertex3f( 0.0f, 1.0f, 0.0f); // Top Of Triangle (Left)
    glColor3f(0.0f,0.0f,1.0f); // Blue
    glVertex3f(-1.0f,-1.0f,-1.0f); // Left Of Triangle (Left)
    glColor3f(0.0f,1.0f,0.0f); // Green
    glVertex3f(-1.0f,-1.0f, 1.0f); // Right Of Triangle (Left)
    
    glEnd(); // Done Drawing The Pyramid
    
    
    glLoadIdentity();
    glTranslatef(1.5f,0.0f,-8.0f); // Move Right And Into The Screen
    glRotatef(qAngle,1.0f,1.0f,1.0f); // Rotate The Cube On X, Y & Z
    
    glBegin(GL_QUADS); // Start Drawing The Cube
    
    glColor3f(0.0f,1.0f,0.0f); // Set The Color To Green
    glVertex3f( 1.0f, 1.0f,-1.0f); // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f); // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f); // Bottom Right Of The Quad (Top)
    
    glColor3f(1.0f,0.5f,0.0f); // Set The Color To Orange
    glVertex3f( 1.0f,-1.0f, 1.0f); // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f); // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f); // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Bottom)
    
    glColor3f(1.0f,0.0f,0.0f); // Set The Color To Red
    glVertex3f( 1.0f, 1.0f, 1.0f); // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f); // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f); // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f); // Bottom Right Of The Quad (Front)
    
    glColor3f(1.0f,1.0f,0.0f); // Set The Color To Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Left Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f); // Top Right Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f); // Top Left Of The Quad (Back)
    
    glColor3f(0.0f,0.0f,1.0f); // Set The Color To Blue
    glVertex3f(-1.0f, 1.0f, 1.0f); // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f); // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f); // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f); // Bottom Right Of The Quad (Left)
    
    glColor3f(1.0f,0.0f,1.0f); // Set The Color To Violet
    glVertex3f( 1.0f, 1.0f,-1.0f); // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f); // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f); // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f); // Bottom Right Of The Quad (Right)
    glEnd(); // Done Drawing The Quad
    
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
        case GLUT_KEY_LEFT:
            tAngle -= 10.0f;
            break;
        case GLUT_KEY_RIGHT:
            tAngle += 10.0f;
            break;
        case GLUT_KEY_UP:
            qAngle += 10.0f;
            break;
        case GLUT_KEY_DOWN:
            qAngle -= 10.0f;
            break;
	}
}

void MainLoop() {
    glutPostRedisplay();
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
    
	// enter GLUT event processing loop
	glutMainLoop();
    
	return 1;
}
