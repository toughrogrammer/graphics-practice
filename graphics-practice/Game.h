//
//  Game.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Game__
#define __graphics_practice__Game__

#include "Prefix.h"
#include "Keyboard.h"

class Game {
private:
    struct timeval _timePrev, _timeCurr;
    
public:
    Game();
    ~Game();
    
    void Initialize();
    
    void MainLoop();
    void Update(float dt);
    void Render();
    void ReshapedWindow(int width, int height);
    void ProcessSpecialKeys(bool keyDown, int key, int x, int y);
    void ProcessNormalKeys(bool keyDown, unsigned char key, int x, int y);
};

#endif /* defined(__graphics_practice__Game__) */
