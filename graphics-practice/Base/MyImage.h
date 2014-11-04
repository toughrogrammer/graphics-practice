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
    int _bpp;
    
public:
    MyImage();
    MyImage(GLuint texture, unsigned char* data, unsigned int width, unsigned int height);
    ~MyImage();
    
    static MyImage* LoadImage(string path);
    static MyImage* LoadImageFromRAW(string path, int width, int height, int format);
    bool InitWithFileTGA(string path);
    bool InitWithFileRAW(string path);
    bool InitWithFileBMP();

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
    int GetBitPerPixel() {
        return _bpp * 8;
    }
    int GetBytePerPixel() {
        return _bpp;
    }
    
    void GenerateTexture(int magFilter = GL_LINEAR, int minFilter = GL_LINEAR, int type = GL_UNSIGNED_BYTE);
    static void Blit(MyImage *src, MyImage *dst, int src_xstart, int src_ystart, int src_width, int src_height, int dst_xstart, int dst_ystart, int blend, int alpha);
};

#endif
