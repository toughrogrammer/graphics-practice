//
//  Node.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Node.h"
#include "Action.h"

Node::Node()
{
    
}

Node::~Node()
{
    
}

bool Node::Init()
{
    return true;
}

void Node::Update(float dt)
{
    
}

void Node::Draw()
{
    
}

Vector3 Node::GetPosition()
{
    return _position;
}

void Node::SetPosition(Vector3 vec)
{
    _position = vec;
}

Vector3 Node::GetRotation()
{
    return _rotation;
}

void Node::SetRotation(Vector3 vec)
{
    _rotation = vec;
}

void Node::RunAction(Action *action)
{
    action->SetTarget(this);
    action->Start();
}