//
//  Scene.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Scene.h"


Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

Scene* Scene::Create()
{
    Scene *pRet = new Scene;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool Scene::Init()
{
    for( int i = GL_LIGHT0; i <= GL_LIGHT7; i ++ ) {
        glDisable(i);
    }
    
    return true;
}

void Scene::OnEnter()
{
    
}

void Scene::OnExit()
{
    
}

void Scene::Update(float dt)
{
    
}

void Scene::Draw()
{
    
}

void Scene::ProcessSpecialKeys(int key, int x, int y)
{
    
}

void Scene::ProcessNormalKeys(unsigned char key, int x, int y)
{
    
}