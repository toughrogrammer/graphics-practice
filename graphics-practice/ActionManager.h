//
//  ActionManager.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__ActionManager__
#define __graphics_practice__ActionManager__

#include <vector>

using namespace std;

class Action;

class ActionManager {
private:
    static ActionManager* _instance;
    vector<Action*> _actions;
    
    
private:
    ActionManager();

    
public:
    ~ActionManager();
    static ActionManager* Instance();
    
    void AddAction(Action *action);
    void RemoveAction(Action *action);
};

#endif /* defined(__graphics_practice__ActionManager__) */
