//
//  Cube.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Cube.h"
#include "MyImage.h"

Cube::Cube(GLuint texture, float length)
: ::Node()
, _texture(texture)
, _length(length)
{
    _scale.Set( 1.0f, 1.0f, 1.0f );
    
    _points = new Vector3[8] {
        Vector3( -1 * length / 2, -1 * length / 2, length / 2 ),
        Vector3( 1 * length / 2, -1 * length / 2, length / 2 ),
        Vector3( 1 * length / 2, 1 * length / 2, length / 2 ),
        Vector3( -1 * length / 2, 1 * length / 2, length / 2 ),
        Vector3( -1 * length / 2, -1 * length / 2, -1 * length / 2 ),
        Vector3( 1 * length / 2, -1 * length / 2, -1 * length / 2 ),
        Vector3( 1 * length / 2, 1 * length / 2, -1 * length / 2 ),
        Vector3( -1 * length / 2, 1 * length / 2, -1 * length / 2 ),
    };
}

Cube::~Cube()
{
    delete[] _points;
}

Cube* Cube::Create(GLuint texture, float length)
{
    Cube *pRet = NULL;
    
    pRet = new Cube( texture, length );
    if( pRet->Init() )
    {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool Cube::Init()
{
    return Node::Init();
}

void Cube::Draw()
{
    Node::Draw();
    
    glPushMatrix();
    
    glTranslatef( _position.x, _position.y, _position.z );
    glScalef( _scale.x, _scale.y, _scale.z );
    glRotatef( _rotation.x, 1.0f, 0.0f, 0.0f );
    glRotatef( _rotation.y, 0.0f, 1.0f, 0.0f );
    glRotatef( _rotation.z, 0.0f, 0.0f, 1.0f );
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texture);

    
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer
    glTexCoord2f(0.0f, 0.0f); GLVertexByVector3( _points[0] );
    glTexCoord2f(1.0f, 0.0f); GLVertexByVector3( _points[1] );
    glTexCoord2f(1.0f, 1.0f); GLVertexByVector3( _points[2] );
    glTexCoord2f(0.0f, 1.0f); GLVertexByVector3( _points[3] );
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f); // Normal Pointing Away From Viewer
    glTexCoord2f(1.0f, 0.0f); GLVertexByVector3( _points[4] );
    glTexCoord2f(1.0f, 1.0f); GLVertexByVector3( _points[5] );
    glTexCoord2f(0.0f, 1.0f); GLVertexByVector3( _points[6] );
    glTexCoord2f(0.0f, 0.0f); GLVertexByVector3( _points[7] );
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f); // Normal Pointing Up
    glTexCoord2f(0.0f, 1.0f); GLVertexByVector3( _points[3] );
    glTexCoord2f(0.0f, 0.0f); GLVertexByVector3( _points[2] );
    glTexCoord2f(1.0f, 0.0f); GLVertexByVector3( _points[6] );
    glTexCoord2f(1.0f, 1.0f); GLVertexByVector3( _points[7] );
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f); // Normal Pointing Down
    glTexCoord2f(1.0f, 1.0f); GLVertexByVector3( _points[0] );
    glTexCoord2f(0.0f, 1.0f); GLVertexByVector3( _points[1] );
    glTexCoord2f(0.0f, 0.0f); GLVertexByVector3( _points[5] );
    glTexCoord2f(1.0f, 0.0f); GLVertexByVector3( _points[4] );
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f); // Normal Pointing Right
    glTexCoord2f(1.0f, 0.0f); GLVertexByVector3( _points[5] );
    glTexCoord2f(1.0f, 1.0f); GLVertexByVector3( _points[1] );
    glTexCoord2f(0.0f, 1.0f); GLVertexByVector3( _points[2] );
    glTexCoord2f(0.0f, 0.0f); GLVertexByVector3( _points[6] );
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f); // Normal Pointing Left
    glTexCoord2f(0.0f, 0.0f); GLVertexByVector3( _points[0] );
    glTexCoord2f(1.0f, 0.0f); GLVertexByVector3( _points[4] );
    glTexCoord2f(1.0f, 1.0f); GLVertexByVector3( _points[7] );
    glTexCoord2f(0.0f, 1.0f); GLVertexByVector3( _points[3] );
    glEnd(); // Done Drawing Quads
    
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}