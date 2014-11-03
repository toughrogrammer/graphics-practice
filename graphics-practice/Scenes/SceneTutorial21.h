//
//  SceneTutorial21.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial21__
#define __graphics_practice__SceneTutorial21__

#include "Prefix.h"


class SceneTutorial21 : public Scene
{
    class Object {
    public:
        int fx, fy;
        int x, y;
        float spin;
    };

    class Timer {
    public:
        long frequency;
        float resolution;
        unsigned long mm_timer_start, mm_timer_elpased;
        bool performance_timer;
        long performance_timer_start, performance_timer_elapsed;
    };

private:
    bool vline[11][10];
    bool hline[10][11];
    bool filled;
    bool anti;
    bool gameover;
    int delay;                              // Enemy Delay
    int adjust;                           // Speed Adjustment For Really Slow Video Cards
    int lives;                            // Player Lives
    int level;                            // Internal Game Level
    int level2;                           // Displayed Game Level
    int stage;                            // Game Stage
    int loop1, loop2;


    Object player, hourglass;
    vector<Object> enemy;
    Timer timer;
    int steps[6];
    MyImage *img;

    
public:
    static SceneTutorial21* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);

    void TimerInit();
    void ResetObjects();

};


#endif /* defined(__graphics_practice__SceneTutorial21__) */
