//
//  MySprite.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Sprite.h"
#include "MyImage.h"


Sprite::Sprite(MyImage *img)
: _img(img)
{
    _scale.Set( 1.0f, 1.0f, 1.0f );
}

Sprite::~Sprite()
{
    SAFE_DELETE( _img );
}

Sprite* Sprite::Create(const char *path)
{
    Sprite *pRet = NULL;
    
    MyImage *img = MyImage::LoadImage(path);
    if( img != NULL )
    {
        pRet = new Sprite(img);
        pRet->Init();
        return pRet;
    }

    SAFE_DELETE(pRet);
    return pRet;
}

void Sprite::Update(float dt)
{
    Node::Update(dt);
}

void Sprite::Draw()
{
    Node::Draw();
    
    glPushMatrix();
    
    glTranslatef( _position.x, _position.y, _position.z );
    glScalef( _scale.x, _scale.y, _scale.z );
    glRotatef( _rotation.x, 1.0f, 0.0f, 0.0f );
    glRotatef( _rotation.y, 0.0f, 1.0f, 0.0f );
    glRotatef( _rotation.z, 0.0f, 0.0f, 1.0f );
    
    GLuint tex = _img->GetTexture();
    int width = _img->GetWidth();
    int height = _img->GetHeight();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -1 * width / 2, -1 * height / 2, 0); // Point 1
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1 * width / 2, -1 * height / 2, 0); // Point 2
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1 * width / 2, 1 * height / 2, 0); // Point 3
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -1 * width / 2, 1 * height / 2, 0); // Point 4
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}