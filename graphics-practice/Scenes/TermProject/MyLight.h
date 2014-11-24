//
//  MyLight.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 24..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__MyLight__
#define __graphics_practice__MyLight__

#include "Prefix.h"

class MyLight : public Node {
private:
    bool enable = false;
	GLuint LightID = 0;
	GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightSpecular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightAttenuation[1] = { 1.0f, };
	float LightPosition[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

public:
	MyLight(GLuint id);
	virtual bool Init();
    virtual void SetPosition(Vector3 vec);
    void SetEnabled(bool enable);
    void SetAmbient(float r, float g, float b, float a = 1.0f);
    void SetDiffuse(float r, float g, float b, float a = 1.0f);
    void SetAttenuation(float d);
};


#endif /* defined(__graphics_practice__MyLight__) */
