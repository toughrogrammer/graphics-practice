//
//  SceneTutorial27.h
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__SceneTutorial27__
#define __graphics_practice__SceneTutorial27__

#include "Prefix.h"


class SceneTutorial27 : public Scene
{
    class Plane
    {
    public:
        GLfloat a, b, c, d;
    };
    
    // Structure Describing An Object's Face
    class Face
    {
    public:
        int vertexIndices[3];           // Index Of Each Vertex Within An Object That Makes Up The Triangle Of This Face
        Vector3 normals[3];         // Normals To Each Vertex
        Plane planeEquation;            // Equation Of A Plane That Contains This Triangle
        int neighbourIndices[3];        // Index Of Each Face That Neighbours This One Within The Object
        bool visible;               // Is The Face Visible By The Light?
    };
    
    class ShadowedObject
    {
    public:
        int nVertices;
        Vector3 *pVertices;         // Will Be Dynamically Allocated
        
        int nFaces;
        Face *pFaces;               // Will Be Dynamically Allocated
        
        ~ShadowedObject()
        {
            delete[] pVertices;
            delete[] pFaces;
        }
    };
    
    
private:
    Vector3 _cameraPosition, _cameraRotation, _cameraScale;
    
    ShadowedObject obj;										// Object
    GLfloat		xrot=0;
    GLfloat     xrotspeed=5;							// X Rotation & X Speed
    GLfloat		yrot=0;
    GLfloat     yrotspeed=6;							// Y Rotation & Y Speed
    
    float LightPos[4] = { 0.0f, 5.0f,-4.0f, 1.0f};			// Light Position
    float LightAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f};			// Ambient Light Values
    float LightDif[4] = { 0.6f, 0.6f, 0.6f, 1.0f};			// Diffuse Light Values
    float LightSpc[4] = {-0.2f, -0.2f, -0.2f, 1.0f};			// Specular Light Values
    
    float MatAmb[4] = {0.4f, 0.4f, 0.4f, 1.0f};				// Material - Ambient Values
    float MatDif[4] = {0.2f, 0.6f, 0.9f, 1.0f};				// Material - Diffuse Values
    float MatSpc[4] = {0.0f, 0.0f, 0.0f, 1.0f};				// Material - Specular Values
    float MatShn[1] = {0.0f};								// Material - Shininess
    
    float ObjPos[3] = {-2.0f,-2.0f,-5.0f};					// Object Position
    
    GLUquadricObj	*q;										// Quadratic For Drawing A Sphere
    float SpherePos[3] = {-4.0f,-5.0f,-6.0f};

    
    
public:
    static SceneTutorial27* Create();
    
    virtual bool Init();
    virtual void OnExit();
    virtual void Update(float dt);
    virtual void Draw();
    
    virtual void ProcessNormalKeys(unsigned char key, int x, int y);
    
    bool InitObjects();
    bool readObject(const char *filename, ShadowedObject& object);
    void VMatMult(float M[16], float v[4]);
    void calculatePlane( const ShadowedObject& object, Face& face );
    void DrawGLRoom();
    void DrawShadowedObject(const ShadowedObject& object);
    void castShadow(ShadowedObject& object, GLfloat *lightPosition );
    void doShadowPass(ShadowedObject& object, GLfloat *lightPosition );
};


#endif /* defined(__graphics_practice__SceneTutorial27__) */
