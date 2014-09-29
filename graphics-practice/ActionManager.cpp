//
//  ActionManager.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "ActionManager.h"
#include "Action.h"

#include <algorithm>

ActionManager *ActionManager::_instance = 0;

ActionManager::ActionManager()
{
    
}

ActionManager::~ActionManager()
{
    
}

ActionManager* ActionManager::Instance()
{
    if( _instance == 0 ) {
        _instance = new ActionManager();
    }
    
    return _instance;
}

void ActionManager::AddAction(Action *action)
{
    _actions.push_back(action);
}

void ActionManager::RemoveAction(Action *action)
{
    auto it = find( _actions.begin(), _actions.end(), action );
    if( it != _actions.end() ) {
        _actions.erase( it );
    }
}