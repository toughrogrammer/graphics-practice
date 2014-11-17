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
    
    image = new MyImage( texture, data, width, height );
    return image;
}

// RAW format is so special, so we need independent method
MyImage* MyImage::LoadImageFromRAW(string path, int width, int height, int format)
{
    MyImage *img = new MyImage;
    img->_width = width;
    img->_height = height;
    img->_data = new unsigned char[width * height];
    img->_bpp = format;
    
    FILE *f;
    int i,j,k,done=0;
    int stride = width * format;				// Size Of A Row (Width * Bytes Per Pixel)
    unsigned char *p = NULL;
    
    f = fopen(path.c_str(), "rb");									// Open "filename" For Reading Bytes
    if( f == NULL ) {
        SAFE_DELETE( img );
        return NULL;
    }
    
    for( i = height-1; i >= 0 ; i-- )				// Loop Through Height (Bottoms Up - Flip Image)
    {
        p = img->_data + (i * stride);					//
        for ( j = 0; j < width ; j++ )				// Loop Through Width
        {
            for ( k = 0 ; k < format-1 ; k++, p++, done++ )
            {
                *p = fgetc(f);								// Read Value From File And Store In Memory
            }
            *p = 255; p++;									// Store 255 In Alpha Channel And Increase Pointer
        }
    }
    fclose(f);												// Close The File
    
    return img;
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

    int bitPerPixel = header[4]; // Grab The TGA's Bits Per Pixel (24 or 32)
    _bpp = bitPerPixel * 8;
    
    bytesPerPixel   = bitPerPixel / 8;                       // Divide By 8 To Get The Bytes Per Pixel
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
    
    if (bitPerPixel == 24)                                 // Was The TGA 24 Bits
    {
        type=GL_RGB;                                        // If So Set The 'type' To GL_RGB
    }

    glTexImage2D(GL_TEXTURE_2D, 0, type, _width, _height, 0, type, GL_UNSIGNED_BYTE, _data);
    return true;
}

void MyImage::GenerateTexture(int magFilter, int minFilter, int type)
{
    if( _texture != 0 ) {
        glDeleteTextures(1, &_texture);
    }
    
    int format = GL_RGB;
    if( GetBitPerPixel() == 32 ) {
        format = GL_RGBA;
    }
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, type, _width, _height, 0, format, type, _data);
}

void MyImage::Blit(MyImage *src, MyImage *dst, int src_xstart, int src_ystart, int src_width, int src_height, int dst_xstart, int dst_ystart, int blend, int alpha)
{
    int i,j,k;
    unsigned char *s, *d;										// Source & Destination
    
    // Clamp Alpha If Value Is Out Of Range
    if( alpha > 255 ) alpha = 255;
    if( alpha < 0 ) alpha = 0;
    
    // Check For Incorrect Blend Flag Values
    if( blend < 0 ) blend = 0;
    if( blend > 1 ) blend = 1;
    
    int bppSrc = src->GetBytePerPixel();
    int bppDst = dst->GetBytePerPixel();
    int widthSrc = src->GetWidth();
    int widthDst = dst->GetWidth();
    
    d = dst->GetData() + (dst_ystart * widthDst * bppDst);    // Start Row - dst (Row * Width In Pixels * Bytes Per Pixel)
    s = src->GetData() + (src_ystart * widthSrc * bppSrc);    // Start Row - src (Row * Width In Pixels * Bytes Per Pixel)
    
    for (i = 0 ; i < src_height ; i++ )							// Height Loop
    {
        s = s + (src_xstart * bppSrc);						// Move Through Src Data By Bytes Per Pixel
        d = d + (dst_xstart * bppDst);						// Move Through Dst Data By Bytes Per Pixel
        for (j = 0 ; j < src_width ; j++ )						// Width Loop
        {
            for( k = 0 ; k < bppSrc ; k++, d++, s++)		// "n" Bytes At A Time
            {
                if (blend)										// If Blending Is On
                    *d = ( (*s * alpha) + (*d * (255-alpha)) ) >> 8; // Multiply Src Data*alpha Add Dst Data*(255-alpha)
                else											// Keep in 0-255 Range With >> 8
                    *d = *s;									// No Blending Just Do A Straight Copy
            }
        }
        d = d + (widthDst - (src_width + dst_xstart)) * bppDst;	// Add End Of Row */
        s = s + (widthSrc - (src_width + src_xstart)) * bppSrc;	// Add End Of Row */
    }
}