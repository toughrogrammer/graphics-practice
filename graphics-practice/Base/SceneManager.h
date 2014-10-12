//
//  SceneManager.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneManager__
#define __graphics_practice__SceneManager__

#include <stdlib.h>


class Scene;

class SceneManager {
private:
    static SceneManager* _instance;
    Scene *_currScene;
    
private:
    SceneManager();
    
public:
    ~SceneManager();
    static SceneManager* Instance();
    
    Scene* GetCurrentScene();
    void ReplaceScene(Scene *scene);
    
};

#endif /* defined(__graphics_practice__SceneManager__) */
