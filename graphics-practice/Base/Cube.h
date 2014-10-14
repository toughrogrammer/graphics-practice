//
//  Cube.h
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Cube__
#define __graphics_practice__Cube__

#include <OpenGL/OpenGL.h>
#include "Node.h"


class Cube : public Node {
private:
    GLuint _texture;
    float _length;
    Vector3 *_points;
    
public:
    Cube(GLuint texture, float length);
    virtual ~Cube();
    
    static Cube* Create(GLuint texture, float length);
    virtual bool Init();
    virtual void Draw();
    
    void SetTexture(GLuint texture);
    
};

#endif /* defined(__graphics_practice__Cube__) */
