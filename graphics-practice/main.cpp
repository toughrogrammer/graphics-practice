//
//  main.cpp
//  graphics-pratice
//
//  Created by loki on 2014. 9. 15..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Prefix.h"

#include "Game.h"

#define WINDOW_TITLE "Loki's Graphics Practice"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Game MyGame;

void processNormalKeys(unsigned char key, int x, int y) {
    MyGame.ProcessNormalKeys(key, x, y);
}

void processSpecialKeys(int key, int x, int y) {
    MyGame.ProcessSpecialKeys(key, x, y);
}

void changeSize(int w, int h) {
    MyGame.ReshapedWindow(w, h);
}

void render() {
    MyGame.Render();
}

void MainLoop() {
    MyGame.MainLoop();
    glutPostRedisplay();
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   	glutCreateWindow(WINDOW_TITLE);
    
    // here are the new entries
    glutKeyboardFunc(&processNormalKeys);
    glutSpecialFunc(&processSpecialKeys);
    
	// register callbacks
	glutReshapeFunc(&changeSize);
    glutDisplayFunc(&render);
    
    // set my main loop callback function
    glutIdleFunc(&MainLoop);

    
    MyGame.Initialize();
    
    // enter GLUT event processing loop
	glutMainLoop();
    
	return 0;
}
