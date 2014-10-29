//
//  SceneTutorial24.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 29..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial24.h"


SceneTutorial24* SceneTutorial24::Create()
{
    SceneTutorial24 *pRet = new SceneTutorial24;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial24::Init()
{
    if( ! LoadTGA(imageFont, "Textures/Font.tga") ) {
        return false;
    }
    
    BuildFont();

    glShadeModel(GL_SMOOTH);                                // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                                     // Depth Buffer Setup
    glBindTexture(GL_TEXTURE_2D, imageFont._textureID);        // Select Our Font Texture

    _cameraPosition.Set(0, 0, 10);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);

    swidth = 640;
    sheight = 480;


    return true;
}

void SceneTutorial24::OnExit()
{
    
}

void SceneTutorial24::Update(float dt)
{
    Scene::Update(dt);
}

void SceneTutorial24::Draw()
{
    Scene::Draw();

    // set projection
    glMatrixMode(GL_PROJECTION);                            // Select The Projection Matrix
    glLoadIdentity();                                       // Reset The Projection Matrix
    glOrtho(0.0f,640,480,0.0f,-1.0f,1.0f);                  // Create Ortho 640x480 View (0,0 At Top Left)
    glMatrixMode(GL_MODELVIEW);                             // Select The Modelview Matrix
    glLoadIdentity();                                       // Reset The Modelview Matrix
    
    // draw
    char    *token;                                         // Storage For Our Token
    int     cnt=0;                                          // Local Counter Variable

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear Screen And Depth Buffer

    glColor3f(1.0f,0.5f,0.5f);                              // Set Color To Bright Red
    glPrint(50,16,1,"Renderer");                            // Display Renderer
    glPrint(80,48,1,"Vendor");                              // Display Vendor Name
    glPrint(66,80,1,"Version");                             // Display Version

    glColor3f(1.0f,0.7f,0.4f);                              // Set Color To Orange
    glPrint(200,16,1,(char *)glGetString(GL_RENDERER));     // Display Renderer
    glPrint(200,48,1,(char *)glGetString(GL_VENDOR));       // Display Vendor Name
    glPrint(200,80,1,(char *)glGetString(GL_VERSION));      // Display Version

    glColor3f(0.5f,0.5f,1.0f);                              // Set Color To Bright Blue
    glPrint(192,432,1,"NeHe Productions");                  // Write NeHe Productions At The Bottom Of The Screen

    glLoadIdentity();                                       // Reset The ModelView Matrix
    glColor3f(1.0f,1.0f,1.0f);                              // Set The Color To White
    glBegin(GL_LINE_STRIP);                                 // Start Drawing Line Strips (Something New)
        glVertex2d(639,417);                                // Top Right Of Bottom Box
        glVertex2d(  0,417);                                // Top Left Of Bottom Box
        glVertex2d(  0,480);                                // Lower Left Of Bottom Box
        glVertex2d(639,480);                                // Lower Right Of Bottom Box
        glVertex2d(639,128);                                // Up To Bottom Right Of Top Box
    glEnd();                                                // Done First Line Strip
    glBegin(GL_LINE_STRIP);                                 // Start Drawing Another Line Strip
        glVertex2d(  0,128);                                // Bottom Left Of Top Box
        glVertex2d(639,128);                                // Bottom Right Of Top Box                              
        glVertex2d(639,  1);                                // Top Right Of Top Box
        glVertex2d(  0,  1);                                // Top Left Of Top Box
        glVertex2d(  0,417);                                // Down To Top Left Of Bottom Box
    glEnd();                                                // Done Second Line Strip

    glScissor(1 ,int(0.135416f*sheight),swidth-2,int(0.597916f*sheight));   // Define Scissor Region
    glEnable(GL_SCISSOR_TEST);                              // Enable Scissor Testing

    char* text=(char *)malloc(strlen((char *)glGetString(GL_EXTENSIONS))+1);    // Allocate Memory For Our Extension String
    strcpy (text,(char *)glGetString(GL_EXTENSIONS));       // Grab The Extension List, Store In Text

    token=strtok(text," ");                                 // Parse 'text' For Words, Seperated By " " (spaces)
    while(token!=NULL)                                      // While The Token Isn't NULL
    {
        cnt++;                                              // Increase The Counter
        if (cnt>maxtokens)                                  // Is 'maxtokens' Less Than 'cnt'
        {
            maxtokens=cnt;                                  // If So, Set 'maxtokens' Equal To 'cnt'
        }

        glColor3f(0.5f,1.0f,0.5f);                          // Set Color To Bright Green
        glPrint(0,96+(cnt*32)-scroll,0,"%i",cnt);           // Print Current Extension Number
        glColor3f(1.0f,1.0f,0.5f);                          // Set Color To Yellow
        glPrint(50,96+(cnt*32)-scroll,0,token);             // Print The Current Token (Parsed Extension Name)
        token=strtok(NULL," ");                             // Search For The Next Token
    }

    glDisable(GL_SCISSOR_TEST);                             // Disable Scissor Testing

    free(text);                                             // Free Allocated Memory

    glutSwapBuffers();
}

void SceneTutorial24::ProcessNormalKeys(unsigned char key, int x, int y)
{

}

void SceneTutorial24::glPrint(GLint x, GLint y, int set, const char *fmt, ...) // Where The Printing Happens
{
    char        text[1024];                                 // Holds Our String
    va_list     ap;                                         // Pointer To List Of Arguments

    if (fmt == NULL)                                        // If There's No Text
        return;                                             // Do Nothing

    va_start(ap, fmt);                                      // Parses The String For Variables
        vsprintf(text, fmt, ap);                            // And Converts Symbols To Actual Numbers
    va_end(ap);                                             // Results Are Stored In Text

    if (set>1)                                              // Did User Choose An Invalid Character Set?
    {
        set=1;                                              // If So, Select Set 1 (Italic)
    }

    glEnable(GL_TEXTURE_2D);                                // Enable Texture Mapping
    glLoadIdentity();                                       // Reset The Modelview Matrix
    glTranslated(x,y,0);                                    // Position The Text (0,0 - Top Left)
    glListBase(base-32+(128*set));                          // Choose The Font Set (0 or 1)

    glScalef(1.0f,2.0f,1.0f);                               // Make The Text 2X Taller

    glCallLists((GLsizei)strlen(text),
                GL_UNSIGNED_BYTE,
                text);       // Write The Text To The Screen
    glDisable(GL_TEXTURE_2D);                               // Disable Texture Mapping
}

void SceneTutorial24::BuildFont()                                    // Build Our Font Display List
{
    base=glGenLists(256);                                   // Creating 256 Display Lists
    glBindTexture(GL_TEXTURE_2D, imageFont._textureID);        // Select Our Font Texture
    for (int loop1=0; loop1<256; loop1++)                   // Loop Through All 256 Lists
    {
        float cx=float(loop1%16)/16.0f;                     // X Position Of Current Character
        float cy=float(loop1/16)/16.0f;                     // Y Position Of Current Character

        glNewList(base+loop1,GL_COMPILE);                   // Start Building A List
            glBegin(GL_QUADS);                              // Use A Quad For Each Character
                glTexCoord2f(cx,1.0f-cy-0.0625f);           // Texture Coord (Bottom Left)
                glVertex2d(0,16);                           // Vertex Coord (Bottom Left)
                glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);   // Texture Coord (Bottom Right)
                glVertex2i(16,16);                          // Vertex Coord (Bottom Right)
                glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);    // Texture Coord (Top Right)
                glVertex2i(16,0);                           // Vertex Coord (Top Right)
                glTexCoord2f(cx,1.0f-cy-0.001f);            // Texture Coord (Top Left)
                glVertex2i(0,0);                            // Vertex Coord (Top Left)
            glEnd();                                        // Done Building Our Quad (Character)
            glTranslated(14,0,0);                           // Move To The Right Of The Character
        glEndList();                                        // Done Building The Display List
    }                                                       // Loop Until All 256 Are Built
}

void SceneTutorial24::KillFont(void)                                     // Delete The Font From Memory
{
    glDeleteLists(base,256);                                // Delete All 256 Display Lists
}

bool SceneTutorial24::LoadTGA(TextureImage &textureImage, string path)
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

    textureImage._width  = header[1] * 256 + header[0];          // Determine The TGA Width  (highbyte*256+lowbyte)
    textureImage._height = header[3] * 256 + header[2];          // Determine The TGA Height (highbyte*256+lowbyte)
    
    if( textureImage._width  <=0 ||                              // Is The Width Less Than Or Equal To Zero
        textureImage._height <=0 ||                              // Is The Height Less Than Or Equal To Zero
        (header[4]!=24 && header[4]!=32))                   // Is The TGA 24 or 32 Bit?
    {
        fclose(file);                                       // If Anything Failed, Close The File
        return false;                                       // Return False
    }

    textureImage._bpp    = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)
    bytesPerPixel   = textureImage._bpp/8;                       // Divide By 8 To Get The Bytes Per Pixel
    imageSize       = textureImage._width * textureImage._height * bytesPerPixel; // Calculate The Memory Required For The TGA Data

    textureImage._imageData = (GLubyte *)malloc(imageSize);        // Reserve Memory To Hold The TGA Data

    if( textureImage._imageData==NULL ||                         // Does The Storage Memory Exist?
        fread(textureImage._imageData, 1, imageSize, file)!=imageSize)   // Does The Image Size Match The Memory Reserved?
    {
        if(textureImage._imageData!=NULL)                        // Was Image Data Loaded
            free(textureImage._imageData);                       // If So, Release The Image Data

        fclose(file);                                       // Close The File
        return false;                                       // Return False
    }

    for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)     // Loop Through The Image Data
    {                                                       // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
        temp=textureImage._imageData[i];                         // Temporarily Store The Value At Image Data 'i'
        textureImage._imageData[i] = textureImage._imageData[i + 2];  // Set The 1st Byte To The Value Of The 3rd Byte
        textureImage._imageData[i + 2] = temp;                   // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
    }

    fclose (file);                                          // Close The File

    // Build A Texture From The Data
    glGenTextures(1, &textureImage._textureID);                    // Generate OpenGL texture IDs

    glBindTexture(GL_TEXTURE_2D, textureImage._textureID);         // Bind Our Texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear Filtered
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear Filtered
    
    if (textureImage._bpp==24)                                 // Was The TGA 24 Bits
    {
        type=GL_RGB;                                        // If So Set The 'type' To GL_RGB
    }

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 type,
                 textureImage._width,
                 textureImage._height,
                 0,
                 type,
                 GL_UNSIGNED_BYTE,
                 textureImage._imageData);

    return true;    
}