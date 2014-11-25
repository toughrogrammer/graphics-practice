//
//  MyLight.cpp
//  graphics-practice
//
//  Created by loki on 2014. 11. 24..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "MyLight.h"


MyLight::MyLight(GLuint lightID)
{
	LightID = lightID;
}

bool MyLight::Init() 
{
	if( ! Node::Init() ) {
		return false;
	}

	glEnable(LightID);
    glLightfv(LightID, GL_AMBIENT, LightAmbient);
    glLightfv(LightID, GL_DIFFUSE, LightDiffuse);
    glLightfv(LightID, GL_SPECULAR, LightSpecular);
    glLightfv(LightID, GL_LINEAR_ATTENUATION, LightAttenuation);
    
    SetPosition(Vector3(0, 0, 0));

	return true;
}

void MyLight::Draw()
{
    glLightfv(LightID, GL_POSITION, LightPosition);
}

void MyLight::SetPosition(Vector3 vec)
{
	Node::SetPosition(vec);

	LightPosition[0] = _position.x;
	LightPosition[1] = _position.y;
	LightPosition[2] = _position.z;
}

void MyLight::SetEnabled(bool enable)
{
    this->enable = enable;
    if( enable ) {
        glEnable(LightID);
    }
    else {
        glDisable(LightID);
    }
}

void MyLight::SetAmbient(float r, float g, float b, float a)
{
	LightAmbient[0] = r;
	LightAmbient[1] = g;
	LightAmbient[2] = b;
	LightAmbient[3] = a;
	glLightfv(LightID, GL_AMBIENT, LightAmbient);
}

void MyLight::SetDiffuse(float r, float g, float b, float a)
{
	LightDiffuse[0] = r;
	LightDiffuse[1] = g;
	LightDiffuse[2] = b;
	LightDiffuse[3] = a;
	glLightfv(LightID, GL_DIFFUSE, LightDiffuse);
}

void MyLight::SetAttenuation(GLuint attenuationType, float d)
{
    // default type is constant
    int i = ATTENUATION_TYPE_CONSTANT;
    switch( attenuationType ) {
        case GL_CONSTANT_ATTENUATION:
            i = ATTENUATION_TYPE_CONSTANT;
            break;
        case GL_LINEAR_ATTENUATION:
            i = ATTENUATION_TYPE_LINEAR;
            break;
        case GL_QUADRATIC_ATTENUATION:
            i = ATTENUATION_TYPE_QUADRATIC;
            break;
    }
    
    LightAttenuation[i] = d;
    
    glLightf(LightID, GL_CONSTANT_ATTENUATION, LightAttenuation[ATTENUATION_TYPE_CONSTANT]);
    glLightf(LightID, GL_LINEAR_ATTENUATION, LightAttenuation[ATTENUATION_TYPE_LINEAR]);
    glLightf(LightID, GL_QUADRATIC_ATTENUATION, LightAttenuation[ATTENUATION_TYPE_QUADRATIC]);
}