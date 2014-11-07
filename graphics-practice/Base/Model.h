//
//  Model.h
//  graphics-practice
//
//  Created by loki on 2014. 11. 8..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef __graphics_practice__Model__
#define __graphics_practice__Model__

#include "GL.h"
#include "Node.h"

#include <vector>
#include <string>

class MyImage;

class Model : public Node
{
public:
    //	Mesh
    struct Mesh
    {
        int m_materialIndex;
        int m_numTriangles;
        int *m_pTriangleIndices;
    };
    
    //	Material properties
    struct Material
    {
        float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
        float m_shininess;
        GLuint m_texture;
        char *m_pTextureFilename;
    };
    
    //	Triangle structure
    struct Triangle
    {
        float m_vertexNormals[3][3];
        float m_s[3], m_t[3];
        int m_vertexIndices[3];
    };
    
    //	Vertex structure
    struct Vertex
    {
        char m_boneID;	// for skeletal animation
        float m_location[3];
    };
    
protected:
    //	Meshes used
    int m_numMeshes;
    Mesh *m_pMeshes;
    
    //	Materials used
    int m_numMaterials;
    Material *m_pMaterials;
    
    //	Triangles used
    int m_numTriangles;
    Triangle *m_pTriangles;
    
    //	Vertices Used
    int m_numVertices;
    Vertex *m_pVertices;
    
    std::vector<MyImage*> m_textures;
    
    
public:
    Model();
    virtual ~Model();
    
    virtual bool Init();
    virtual bool InitWithFile(std::string path) = 0;
    virtual void ReloadTexture();
    
    virtual void Update(float dt);
    virtual void Draw();
};


#endif /* defined(__graphics_practice__Model__) */
