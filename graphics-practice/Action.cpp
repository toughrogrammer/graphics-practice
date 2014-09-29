//
//  Action.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Action.h"
#include "ActionManager.h"


Action::Action(float time)
: _time(time)
{
    
}

Action::~Action()
{
    
}

void Action::SetTarget(Node *target)
{
    _target = target;
}

void Action::Start()
{
    ActionManager::Instance()->AddAction( this );
}

void Action::Update(float dt)
{
    _time -= dt;
    if( _time < 0 ) {
        
    }
}