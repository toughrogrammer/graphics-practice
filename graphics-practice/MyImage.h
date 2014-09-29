//
//  MyImage.h
//  graphics-pratice
//
//  Created by loki on 2014. 9. 23..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#ifndef graphics_pratice_MyImage_h
#define graphics_pratice_MyImage_h

#include "prefix.h"

class MyImage {
private:
    GLuint _texture;
    unsigned char* _data;
    unsigned int _width;
    unsigned int _height;
    
public:
    MyImage(GLuint texture, unsigned char* data, unsigned int width, unsigned int height);
    ~MyImage();
    
    static MyImage* LoadImage(string path);
    GLuint GetTexture() {
        return _texture;
    }
    unsigned char* GetData() {
        return _data;
    }
    unsigned int GetWidth() {
        return _width;
    }
    unsigned int GetHeight() {
        return _height;
    }
};

#endif
