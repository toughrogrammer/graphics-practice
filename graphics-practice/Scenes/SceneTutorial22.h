//
//  SceneTutorial22.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial22__
#define __graphics_practice__SceneTutorial22__

#include "Prefix.h"


class SceneTutorial22 : public Scene
{
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;

    bool multiTextureSupported = false; // Flag Indicating Whether Multitexturing Is Supported
    bool useMultiTexture = true; // Use It If It Is Supported?
    GLint maxTexelUnits = 1; // Number Of Texel-Pipelines. This Is At Least 1.

    bool emboss = false;
    bool bumps = false;
    int filter = 0;

    GLfloat LightAmbient[3] = { 0.2f, 0.2f, 0.2f };						// Ambient Light is 20% white
    GLfloat LightDiffuse[3] = { 1.0f, 1.0f, 1.0f };						// Diffuse Light is white
    GLfloat LightPosition[3] = { 0.0f, 0.0f, 2.0f };						// Position is somewhat in front of screen
    GLfloat Gray[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat *data;

    GLuint baseTextures[3];
    GLuint bumpTextures[3];
    GLuint invBumpTextures[3];
    GLuint textureLogo, textureMulti;

    GLfloat	xrot = 0;														// X Rotation
    GLfloat	yrot = 0;														// Y Rotation
    GLfloat xspeed = 0.5f;														// X Rotation Speed
    GLfloat yspeed = 0.7f;														// Y Rotation Speed
    GLfloat	z = -5.0f;													// Depth Into The Screen


public:
    static SceneTutorial22* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);

    void doCube();
    void doLogo();
    bool doMesh1TexelUnits();
    bool doMesh2TexelUnits();
    bool doMeshNoBumps();
    void VMatMult(GLfloat *M, GLfloat *v);
    void SetUpBumps(GLfloat *n, GLfloat *c, GLfloat *l, GLfloat *s, GLfloat *t);
};


#endif /* defined(__graphics_practice__SceneTutorial22__) */
