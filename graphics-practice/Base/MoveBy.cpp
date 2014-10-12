//
//  MoveBy.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Prefix.h"
#include "MoveBy.h"

MoveBy::MoveBy(float duration, Vector3 dist)
: Action(duration)
, _dist(dist)
{
    _duration = duration;
}

MoveBy::~MoveBy()
{
    
}

MoveBy* MoveBy::Create(float duration, Vector3 vec)
{
    MoveBy *pRet = 0;
    
    pRet = new MoveBy(duration, vec);
    if( pRet ) {
        return pRet;
    }
    
    
    SAFE_DELETE( pRet );
    return pRet;
}

void MoveBy::SetTarget(Node *target)
{
    Action::SetTarget(target);
    
    _start = target->GetPosition();
}

void MoveBy::Update(float dt)
{
    Action::Update(dt);
    
    float elapsed = _duration - _time;
    Vector3 move = _dist * (elapsed / _duration);
    _target->SetPosition( _start + move );
}