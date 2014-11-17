//
//  Treasure.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 12..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Treasure.h"


Treasure* Treasure::Create(const char *texturePath)
{
    Treasure *pRet = new Treasure();
    
    if( pRet->InitWithPath(texturePath) ) {
        return pRet;
    }
    
    SAFE_DELETE(pRet);
    return pRet;
}


bool Treasure::InitWithPath(const char *path)
{
    if( ! Node::Init() ) {
        return false;
    }
    
    MyImage *img = MyImage::LoadImage(path);
    _model = Cube::Create(img->GetTexture(), 5.0f);
    _model->SetRotation(Vector3(0, 0, 0));
    SAFE_DELETE(img);
    
    _opacity = 1.0f;
    _step = 0;
    _timer = 0;
    
    return true;
}


void Treasure::Update(float dt)
{
    Node::Update(dt);
    
    if( _step == 1 ) {
        _position.y += 3 * dt;
        _timer += dt;
        if( _timer > 3.0f ) {
            _timer = 0;
            _step++;
        }
    }
    else if( _step == 2 ) {
        _model->SetRotation( _model->GetRotation() + Vector3(0, 300 * dt, 0) );
        _timer += dt;
        if( _timer > 2.0f ) {
            _timer = 0;
            _step++;
        }
    }
    else if( _step == 3 ) {
        _model->SetRotation( _model->GetRotation() + Vector3(0, 300 * dt, 0) );
        _opacity -= dt;
        if( _opacity < 0 ) {
            _opacity = 0;
            _step++;
        }
    }
}

void Treasure::Draw()
{
    Node::Draw();
    
    glPushMatrix();
    glTranslatef( _position.x, _position.y, _position.z );
    
    
    glEnable(GL_BLEND);
    glColor4f(1.0f, 1.0f, 1.0f, _opacity);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _model->Draw();
    glDisable(GL_BLEND);
    
    glPopMatrix();
}


void Treasure::Taked()
{
    if( _step == 0 ) {
        _step++;
    }
}

bool Treasure::IsOnAnimating()
{
    return 0 < _step && _step < 4;
}

bool Treasure::IsFinishedAnimating()
{
    if( _opacity <= 0 && _step == 4 ) {
        return true;
    }
    
    return false;
}