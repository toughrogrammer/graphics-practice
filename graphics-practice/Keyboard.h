//
//  Keyboard.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Keyboard__
#define __graphics_practice__Keyboard__

#include <iostream>
#include <map>
#include <vector>

using namespace std;


class Keyboard
{
private:
    static Keyboard* _instance;
    
public:
    map<int, bool> _specialKeys;
    vector<bool> _normalKeys;
    
private:
    Keyboard();
    
public:
    ~Keyboard();
    static Keyboard* Instance();

    static void EventSpecialKey(int key, bool keyDown);
    static bool PressedSpecial(int key);
    static void EventNormalKey(unsigned char key, bool keyDown);
    static bool PressedNormal(unsigned char key);
};

#endif /* defined(__graphics_practice__Keyboard__) */
