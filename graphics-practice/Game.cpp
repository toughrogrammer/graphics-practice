//
//  Game.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Game.h"
#include "TutorialScenes.h"
#include "SceneTermProject1.h"


Game::Game()
{
    gettimeofday( &_timePrev, NULL );
}

Game::~Game()
{
    
}

void Game::Initialize()
{
    Scene *startScene;
    startScene = SceneTutorial12::Create();
    
    SceneManager::Instance()->ReplaceScene(startScene);
}

void Game::MainLoop()
{
    // setting time
    gettimeofday( &_timeCurr, NULL );
    long msDeltaTime = GetMillisecond(_timeCurr) - GetMillisecond(_timePrev);
    float dt = msDeltaTime * 0.001;
    _timePrev = _timeCurr;

    Update(dt);
}

void Game::Update(float dt)
{
    ActionManager::Instance()->Update( dt );
    
    Scene *scene = SceneManager::Instance()->GetCurrentScene();
    if( scene != NULL ) {
        scene->Update(dt);
    }
}

void Game::Render()
{
    Scene *scene = SceneManager::Instance()->GetCurrentScene();
    if( scene != NULL ) {
        scene->Draw();
    }
}

void Game::ReshapedWindow(int width, int height)
{
    int w = width;
    int h = height;
    
    if (h == 0)
        h = 1;
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    float ratio = w * 1.0 / h;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set the correct perspective.
    gluPerspective(45, ratio, 1, 1000);
    
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Game::ProcessSpecialKeys(bool keyDown, int key, int x, int y)
{
    Keyboard::EventSpecialKey(key, keyDown);
    
    SceneManager::Instance()->GetCurrentScene()->ProcessSpecialKeys(key, x, y);
}

void Game::ProcessNormalKeys(bool keyDown, unsigned char key, int x, int y)
{
    Keyboard::EventNormalKey(key, keyDown);
    
    SceneManager::Instance()->GetCurrentScene()->ProcessNormalKeys(key, x, y);
}
