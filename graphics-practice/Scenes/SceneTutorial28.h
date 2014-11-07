//
//  SceneTutorial28.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial28__
#define __graphics_practice__SceneTutorial28__

#include "Prefix.h"


class SceneTutorial28 : public Scene
{
    // Structure For A 3-Dimensional Point ( NEW )
    class POINT_3D
    {
    public:
        double x, y, z;
    };
    
    // Structure For A 3rd Degree Bezier Patch ( NEW )
    class BEZIER_PATCH
    {
    public:
        POINT_3D    anchors[4][4];                  // 4x4 Grid Of Anchor Points
        GLuint      dlBPatch;                   // Display List For Bezier Patch
        GLuint      texture;                    // Texture For The Patch
    };
    
    
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    
    GLfloat         rotz = 0.0f;                    // Rotation About The Z Axis
    BEZIER_PATCH        mybezier;                   // The Bezier Patch We're Going To Use ( NEW )
    bool            showCPoints=true;               // Toggles Displaying The Control Point Grid ( NEW )
    int         divs = 7;                   // Number Of Intrapolations (Controls Poly Resolution) ( NEW )
    
    
public:
    static SceneTutorial28* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    POINT_3D pointAdd(POINT_3D p, POINT_3D q);
    POINT_3D pointTimes(double c, POINT_3D p);
    POINT_3D makePoint(double a, double b, double c);
    POINT_3D Bernstein(float u, POINT_3D *p);
    GLuint genBezier(BEZIER_PATCH patch, int divs);
    void initBezier();
};


#endif /* defined(__graphics_practice__SceneTutorial28__) */
