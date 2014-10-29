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


MyImage::MyImage()
: _texture(0)
, _data(NULL)
, _width(0)
, _height(0)
, _bpp(0)
{

}

MyImage::MyImage(GLuint texture, unsigned char* data, unsigned int width, unsigned int height)
:_texture(texture)
,_data(data)
,_width(width)
,_height(height)
{
    
}

MyImage::~MyImage()
{
    delete[] _data;
}

MyImage* MyImage::LoadImage(string path) {
    GLuint texture;
    unsigned char *data;
    int width, height;

    MyImage *image = new MyImage();

    string ext;
    ext = path.substr( path.find_last_of('.') );
    
    if( ext.compare("tga") == 0 ) {
        if( ! image->InitWithFileTGA(path) ) {
            delete image;
            return NULL;
        }
        
        return image;
    }
    else if( ext.compare("png") == 0 ) {
        // not supported
        delete image;
        return NULL;
    }

    
    // else formats ...
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
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    image = new MyImage( texture, data, width, height );
    return image;
}

bool MyImage::InitWithFileTGA(string path)
{
    GLubyte     TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};    // Uncompressed TGA Header
    GLubyte     TGAcompare[12];                             // Used To Compare TGA Header
    GLubyte     header[6];                                  // First 6 Useful Bytes From The Header
    GLuint      bytesPerPixel;                              // Holds Number Of Bytes Per Pixel Used In The TGA File
    GLuint      imageSize;                                  // Used To Store The Image Size When Setting Aside Ram
    GLuint      temp;                                       // Temporary Variable
    GLuint      type=GL_RGBA;                               // Set The Default GL Mode To RBGA (32 BPP)

    FILE *file = fopen(path.c_str(), "rb");                     // Open The TGA File

    if( file==NULL ||                                       // Does File Even Exist?
        fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||  // Are There 12 Bytes To Read?
        memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0               ||  // Does The Header Match What We Want?
        fread(header,1,sizeof(header),file)!=sizeof(header))                // If So Read Next 6 Header Bytes
    {
        if (file == NULL)                                   // Did The File Even Exist? *Added Jim Strong*
            return false;                                   // Return False
        else
        {
            fclose(file);                                   // If Anything Failed, Close The File
            return false;                                   // Return False
        }
    }

    _width  = header[1] * 256 + header[0];          // Determine The TGA Width  (highbyte*256+lowbyte)
    _height = header[3] * 256 + header[2];          // Determine The TGA Height (highbyte*256+lowbyte)
    
    if( _width  <=0 ||                              // Is The Width Less Than Or Equal To Zero
        _height <=0 ||                              // Is The Height Less Than Or Equal To Zero
        (header[4] != 24 && header[4] != 32))                   // Is The TGA 24 or 32 Bit?
    {
        fclose(file);                                       // If Anything Failed, Close The File
        return false;                                       // Return False
    }

    _bpp    = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)
    bytesPerPixel   = _bpp / 8;                       // Divide By 8 To Get The Bytes Per Pixel
    imageSize       = _width * _height * bytesPerPixel; // Calculate The Memory Required For The TGA Data

    _data = (GLubyte *)malloc(imageSize);        // Reserve Memory To Hold The TGA Data

    if( _data == NULL || fread( _data, 1, imageSize, file ) != imageSize )   // Does The Image Size Match The Memory Reserved?
    {
        // Was Image Data Loaded
        if( _data != NULL) {
            free(_data);                       // If So, Release The Image Data
        }

        fclose(file);                                       // Close The File
        return false;                                       // Return False
    }

    for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)     // Loop Through The Image Data
    {                                                       // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
        temp=_data[i];                         // Temporarily Store The Value At Image Data 'i'
        _data[i] = _data[i + 2];  // Set The 1st Byte To The Value Of The 3rd Byte
        _data[i + 2] = temp;                   // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
    }

    fclose (file);                                          // Close The File

    // Build A Texture From The Data
    glGenTextures(1, &_texture);                    // Generate OpenGL texture IDs

    glBindTexture(GL_TEXTURE_2D, _texture);         // Bind Our Texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear Filtered
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear Filtered
    
    if (_bpp==24)                                 // Was The TGA 24 Bits
    {
        type=GL_RGB;                                        // If So Set The 'type' To GL_RGB
    }

    glTexImage2D(GL_TEXTURE_2D, 0, type, _width, _height, 0, type, GL_UNSIGNED_BYTE, _data);
    return true;
}