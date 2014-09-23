//
//  MyImage.cpp
//  graphics-pratice
//
//  Created by loki on 2014. 9. 23..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "MyImage.h"
#include <iostream>
using namespace std;

MyImage::MyImage(GLuint texture, unsigned char* data, unsigned int width, unsigned int height)
:_texture(texture)
,_data(data)
,_width(width)
,_height(height)
{
    
}

MyImage::~MyImage()
{
    SOIL_free_image_data( _data );
}

MyImage* MyImage::LoadImage(string path) {
    GLuint texture;
    unsigned char *data;
    int width, height;
    texture = SOIL_load_OGL_texture(path.c_str(),
                                    SOIL_LOAD_AUTO,
                                    SOIL_CREATE_NEW_ID,
                                    SOIL_FLAG_INVERT_Y,
                                    &data,
                                    &width,
                                    &height);
    if( texture == 0 ) {
        return NULL;
    }
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    MyImage *img = new MyImage( texture, data, width, height );
    return img;
}