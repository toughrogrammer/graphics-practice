//
//  SceneTutorial38.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial38__
#define __graphics_practice__SceneTutorial38__

#include "Prefix.h"


class SceneTutorial38 : public Scene
{
    class Object {
    public:
        GLuint tex;
        Vector3 pos;
        float yi;
        float spinz;
        float spinzi;
        float flap;
        float fi;
    };
    
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    
    vector<Object> _objects;
    vector<GLuint> _textures;
    vector<MyImage*> _images;
    
    
public:
    static SceneTutorial38* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    void ResetObject(Object &obj);
};


#endif /* defined(__graphics_practice__SceneTutorial38__) */
