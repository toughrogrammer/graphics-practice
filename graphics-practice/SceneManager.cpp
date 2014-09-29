//
//  SceneManager.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneManager.h"
#include "Scene.h"


SceneManager *SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
    _currScene = NULL;
}

SceneManager::~SceneManager()
{
    
}

SceneManager* SceneManager::Instance()
{
    if( _instance == 0 ) {
        _instance = new SceneManager();
    }
    
    return _instance;
}

Scene* SceneManager::GetCurrentScene()
{
    return _currScene;
}

void SceneManager::ReplaceScene(Scene *scene)
{
    if( _currScene ) {
        _currScene->OnExit();
    }
    
    _currScene = scene;
    _currScene->OnEnter();
}