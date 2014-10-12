//
//  Keyboard.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Keyboard.h"

Keyboard *Keyboard::_instance = NULL;


Keyboard::Keyboard()
{
    _normalKeys.resize(256);
    unsigned long size = _normalKeys.size();
    for( int i = 0; i < size; i ++ ) {
        _normalKeys[i] = false;
    }
}

Keyboard::~Keyboard()
{
    
}

Keyboard* Keyboard::Instance()
{
    if( _instance == 0 ) {
        _instance = new Keyboard();
    }
    
    return _instance;
}

void Keyboard::EventSpecialKey(int key, bool keyDown)
{
    Keyboard *keyboard = Keyboard::Instance();
    keyboard->_specialKeys[key] = keyDown;
}

bool Keyboard::PressedSpecial(int key)
{
    Keyboard *keyboard = Keyboard::Instance();
    
    if( keyboard->_specialKeys.find(key) == keyboard->_specialKeys.end() ) {
        return false;
    }
    
    return keyboard->_specialKeys[key];
}

void Keyboard::EventNormalKey(unsigned char key, bool keyDown)
{
    Keyboard *keyboard = Keyboard::Instance();
    keyboard->_normalKeys[key] = keyDown;
}

bool Keyboard::PressedNormal(unsigned char key)
{
    return Keyboard::Instance()->_normalKeys[key];
}