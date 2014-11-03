//
//  SceneTutorial22.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial22.h"

#define MAX_EMBOSS (GLfloat)0.01f
#define __ARB_ENABLE true                           // Used To Disable ARB Extensions Entirely
// #define EXT_INFO                             // Uncomment To See Your Extensions At Start-Up?
#define MAX_EXTENSION_SPACE 10240                       // Characters For Extension-Strings
#define MAX_EXTENSION_LENGTH 256                        // Maximum Characters In One Extension-String

#define GL_COMBINE_EXT                      0x8570
#define GL_COMBINE_RGB_EXT                  0x8571



SceneTutorial22* SceneTutorial22::Create()
{
    SceneTutorial22 *pRet = new SceneTutorial22;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial22::Init()
{
    glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);


    data = new GLfloat[24 * 5]{
        // FRONT FACE
        0.0f, 0.0f, -1.0f, -1.0f, +1.0f,
        1.0f, 0.0f, +1.0f, -1.0f, +1.0f,
        1.0f, 1.0f, +1.0f, +1.0f, +1.0f,
        0.0f, 1.0f, -1.0f, +1.0f, +1.0f,
        // BACK FACE
        1.0f, 0.0f, -1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f, +1.0f, -1.0f,
        0.0f, 1.0f, +1.0f, +1.0f, -1.0f,
        0.0f, 0.0f, +1.0f, -1.0f, -1.0f,
        // Top Face
        0.0f, 1.0f, -1.0f, +1.0f, -1.0f,
        0.0f, 0.0f, -1.0f, +1.0f, +1.0f,
        1.0f, 0.0f, +1.0f, +1.0f, +1.0f,
        1.0f, 1.0f, +1.0f, +1.0f, -1.0f,
        // Bottom Face
        1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
        0.0f, 1.0f, +1.0f, -1.0f, -1.0f,
        0.0f, 0.0f, +1.0f, -1.0f, +1.0f,
        1.0f, 0.0f, -1.0f, -1.0f, +1.0f,
        // Right Face
        1.0f, 0.0f, +1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, +1.0f, +1.0f, -1.0f,
        0.0f, 1.0f, +1.0f, +1.0f, +1.0f,
        0.0f, 0.0f, +1.0f, -1.0f, +1.0f,
        // Left Face
        0.0f, 0.0f, -1.0f, -1.0f, -1.0f,
        1.0f, 0.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };


    // textures
    MyImage *img;
    int width, height;
    unsigned char *data;

    img = MyImage::LoadImage("Textures/Base.bmp");
    width = img->GetWidth();
    height = img->GetHeight();
    data = img->GetData();
    {
        glGenTextures(3, baseTextures);									// Create Three Textures

        // Create Nearest Filtered Texture
        glBindTexture(GL_TEXTURE_2D, baseTextures[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //                             ========
        // Use GL_RGB8 Instead Of "3" In glTexImage2D. Also Defined By GL: GL_RGBA8 Etc.
        // NEW: Now Creating GL_RGBA8 Textures, Alpha Is 1.0f Where Not Specified By Format.

        // Create Linear Filtered Texture
        glBindTexture(GL_TEXTURE_2D, baseTextures[1]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Create MipMapped Texture
        glBindTexture(GL_TEXTURE_2D, baseTextures[2]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    SAFE_DELETE(img);

    img = MyImage::LoadImage("Textures/Bump.bmp");
    {
        int width = img->GetWidth();
        int height = img->GetHeight();
        unsigned char *data = img->GetData();

        glPixelTransferf(GL_RED_SCALE,0.5f);						// Scale RGB By 50%, So That We Have Only
        glPixelTransferf(GL_GREEN_SCALE,0.5f);						// Half Intenstity
        glPixelTransferf(GL_BLUE_SCALE,0.5f);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);	// No Wrapping, Please!
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,Gray);

        glGenTextures(3, bumpTextures);										// Create Three Textures

        // Create Nearest Filtered Texture
        glBindTexture(GL_TEXTURE_2D, bumpTextures[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Create Linear Filtered Texture
        glBindTexture(GL_TEXTURE_2D, bumpTextures[1]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Create MipMapped Texture
        glBindTexture(GL_TEXTURE_2D, bumpTextures[2]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);


        for (int i=0; i<3*width*height; i++)		// Invert The Bumpmap
            data[i]=255-data[i];

        glGenTextures(3, invBumpTextures);								// Create Three Textures

        // Create Nearest Filtered Texture
        glBindTexture(GL_TEXTURE_2D, invBumpTextures[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Create Linear Filtered Texture
        glBindTexture(GL_TEXTURE_2D, invBumpTextures[1]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Create MipMapped Texture
        glBindTexture(GL_TEXTURE_2D, invBumpTextures[2]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

        glPixelTransferf(GL_RED_SCALE,1.0f);				// Scale RGB Back To 100% Again
        glPixelTransferf(GL_GREEN_SCALE,1.0f);
        glPixelTransferf(GL_BLUE_SCALE,1.0f);
    }
    SAFE_DELETE(img);

    img = MyImage::LoadImage("Textures/OpenGL_ALPHA.bmp");
    char *alpha = NULL;
    if( img != NULL ) {
        int width = img->GetWidth();
        int height = img->GetHeight();
        unsigned char *data = img->GetData();

        alpha=new char[4*width*height];		// Create Memory For RGBA8-Texture
        for (int a=0; a<width*height; a++)
            alpha[4*a+3]=data[a*3];					// Pick Only Red Value As Alpha!

        SAFE_DELETE(img);


        img = MyImage::LoadImage("Textures/OpenGL.bmp");
        width = img->GetWidth();
        height = img->GetHeight();
        data = img->GetData();
        for (int a=0; a<width*height; a++) {
            alpha[4*a]=data[a*3];					// R
            alpha[4*a+1]=data[a*3+1];				// G
            alpha[4*a+2]=data[a*3+2];				// B
        }

        glGenTextures(1, &textureLogo);							// Create One Textures

        // Create Linear Filtered RGBA8-Texture
        glBindTexture(GL_TEXTURE_2D, textureLogo);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
        delete alpha;

        SAFE_DELETE(img);
    }

    img = MyImage::LoadImage("Textures/multi_on_alpha.bmp");
    alpha = NULL;
    if( img != NULL ) {
        int width = img->GetWidth();
        int height = img->GetHeight();
        unsigned char *data = img->GetData();

        alpha=new char[4*width*height];		// Create Memory For RGBA8-Texture
        for (int a=0; a<width*height; a++)
            alpha[4*a+3]=data[a*3];					// Pick Only Red Value As Alpha!

        SAFE_DELETE(img);


        img = MyImage::LoadImage("Textures/multi_on.bmp");
        width = img->GetWidth();
        height = img->GetHeight();
        data = img->GetData();
        for (int a=0; a<width*height; a++) {
            alpha[4*a]=data[a*3];					// R
            alpha[4*a+1]=data[a*3+1];				// G
            alpha[4*a+2]=data[a*3+2];				// B
        }

        glGenTextures(1, &textureMulti);							// Create One Textures

        // Create Linear Filtered RGBA8-Texture
        glBindTexture(GL_TEXTURE_2D, textureMulti);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
        delete alpha;

        SAFE_DELETE(img);
    }



    // light
    glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Load Light-Parameters Into GL_LIGHT1
    glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT1);
    
    return true;
}

void SceneTutorial22::OnExit()
{
    delete data;
}

void SceneTutorial22::Update(float dt)
{
    Scene::Update(dt);

    xrot += xspeed * dt;
    yrot += yspeed * dt;
}

void SceneTutorial22::Draw()
{
    Scene::Draw();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();
    
    if (bumps) {
        if (useMultiTexture && maxTexelUnits>1) {
            doMesh2TexelUnits();
        }
        else  {
            doMesh1TexelUnits();
        }
    }
    else {
        doMeshNoBumps();
    }

    glutSwapBuffers();
}

void SceneTutorial22::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == 'E' || key == 'e' ) {
        emboss = !emboss;
    }

    if( key == 'M' || key == 'm' ) {
        useMultiTexture = ((!useMultiTexture) && multiTextureSupported);
    }

    if( key == 'B' || key == 'b' ) {
        bumps = !bumps;
    }

    if( key == 'F' || key == 'f' ) {
        filter = (filter + 1) % 3;
    }
}

void SceneTutorial22::doCube() {
    int i;
    glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, +1.0f);
    for (i=0; i<4; i++) {
        glTexCoord2f(data[5*i],data[5*i+1]);
        glVertex3f(data[5*i+2],data[5*i+3],data[5*i+4]);
    }
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);
    for (i=4; i<8; i++) {
        glTexCoord2f(data[5*i],data[5*i+1]);
        glVertex3f(data[5*i+2],data[5*i+3],data[5*i+4]);
    }
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);
    for (i=8; i<12; i++) {
        glTexCoord2f(data[5*i],data[5*i+1]);
        glVertex3f(data[5*i+2],data[5*i+3],data[5*i+4]);
    }
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);
    for (i=12; i<16; i++) {
        glTexCoord2f(data[5*i],data[5*i+1]);
        glVertex3f(data[5*i+2],data[5*i+3],data[5*i+4]);
    }
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);
    for (i=16; i<20; i++) {
        glTexCoord2f(data[5*i],data[5*i+1]);
        glVertex3f(data[5*i+2],data[5*i+3],data[5*i+4]);
    }
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    for (i=20; i<24; i++) {
        glTexCoord2f(data[5*i],data[5*i+1]);
        glVertex3f(data[5*i+2],data[5*i+3],data[5*i+4]);
    }
    glEnd();
}

void SceneTutorial22::doLogo() {
    glDepthFunc(GL_ALWAYS);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureLogo);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);	glVertex3f(0.23f, -0.4f,-1.0f);
    glTexCoord2f(1.0f,0.0f);	glVertex3f(0.53f, -0.4f,-1.0f);
    glTexCoord2f(1.0f,1.0f);	glVertex3f(0.53f, -0.25f,-1.0f);
    glTexCoord2f(0.0f,1.0f);	glVertex3f(0.23f, -0.25f,-1.0f);
    glEnd();
    if (useMultiTexture) {
        glBindTexture(GL_TEXTURE_2D, textureMulti);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);	glVertex3f(-0.53f, -0.4f,-1.0f);
        glTexCoord2f(1.0f,0.0f);	glVertex3f(-0.33f, -0.4f,-1.0f);
        glTexCoord2f(1.0f,1.0f);	glVertex3f(-0.33f, -0.3f,-1.0f);
        glTexCoord2f(0.0f,1.0f);	glVertex3f(-0.53f, -0.3f,-1.0f);
        glEnd();
    }
    glDepthFunc(GL_LEQUAL);
}

bool SceneTutorial22::doMesh1TexelUnits() {

    GLfloat c[4]={0.0f,0.0f,0.0f,1.0f};					// Holds Current Vertex
    GLfloat n[4]={0.0f,0.0f,0.0f,1.0f};					// Normalized Normal Of Current Surface
    GLfloat s[4]={0.0f,0.0f,0.0f,1.0f};					// s-Texture Coordinate Direction, Normalized
    GLfloat t[4]={0.0f,0.0f,0.0f,1.0f};					// t-Texture Coordinate Direction, Normalized
    GLfloat l[4];										// Holds Our Lightposition To Be Transformed Into Object Space
    GLfloat Minv[16];									// Holds The Inverted Modelview Matrix To Do So.
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

    // Build Inverse Modelview Matrix First. This Substitutes One Push/Pop With One glLoadIdentity();
    // Simply Build It By Doing All Transformations Negated And In Reverse Order.
    glLoadIdentity();
    glRotatef(-yrot,0.0f,1.0f,0.0f);
    glRotatef(-xrot,1.0f,0.0f,0.0f);
    glTranslatef(0.0f,0.0f,-z);
    glGetFloatv(GL_MODELVIEW_MATRIX,Minv);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,z);

    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);

    // Transform The Lightposition Into Object Coordinates:
    l[0]=LightPosition[0];
    l[1]=LightPosition[1];
    l[2]=LightPosition[2];
    l[3]=1.0f;											// Homogenous Coordinate
    VMatMult(Minv,l);

/*	PASS#1: Use Texture "Bump"
			No Blend
			No Lighting
			No Offset Texture-Coordinates */
    glBindTexture(GL_TEXTURE_2D, bumpTextures[filter]);
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    doCube();

/* PASS#2:	Use Texture "Invbump"
			Blend GL_ONE To GL_ONE
			No Lighting
			Offset Texture Coordinates
			*/
    glBindTexture(GL_TEXTURE_2D,invBumpTextures[filter]);
    glBlendFunc(GL_ONE,GL_ONE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);

    glBegin(GL_QUADS);
    // Front Face
    n[0]=0.0f;		n[1]=0.0f;		n[2]=1.0f;
    s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=0; i<4; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glTexCoord2f(data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Back Face
    n[0]=0.0f;		n[1]=0.0f;		n[2]=-1.0f;
    s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=4; i<8; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glTexCoord2f(data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Top Face
    n[0]=0.0f;		n[1]=1.0f;		n[2]=0.0f;
    s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
    for (i=8; i<12; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glTexCoord2f(data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Bottom Face
    n[0]=0.0f;		n[1]=-1.0f;		n[2]=0.0f;
    s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
    for (i=12; i<16; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glTexCoord2f(data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Right Face
    n[0]=1.0f;		n[1]=0.0f;		n[2]=0.0f;
    s[0]=0.0f;		s[1]=0.0f;		s[2]=-1.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=16; i<20; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glTexCoord2f(data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Left Face
    n[0]=-1.0f;		n[1]=0.0f;		n[2]=0.0f;
    s[0]=0.0f;		s[1]=0.0f;		s[2]=1.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=20; i<24; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glTexCoord2f(data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    glEnd();

/* PASS#3:	Use Texture "Base"
			Blend GL_DST_COLOR To GL_SRC_COLOR (Multiplies By 2)
			Lighting Enabled
			No Offset Texture-Coordinates
			*/
    if (!emboss) {
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, baseTextures[filter]);
        glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
        glEnable(GL_LIGHTING);
        doCube();
    }

    xrot+=xspeed;
    yrot+=yspeed;
    if (xrot>360.0f) xrot-=360.0f;
    if (xrot<0.0f) xrot+=360.0f;
    if (yrot>360.0f) yrot-=360.0f;
    if (yrot<0.0f) yrot+=360.0f;

/*	LAST PASS:	Do The Logos! */
    doLogo();

    return true;										// Keep Going
}

bool SceneTutorial22::doMesh2TexelUnits() {

    GLfloat c[4]={0.0f,0.0f,0.0f,1.0f};					// holds current vertex
    GLfloat n[4]={0.0f,0.0f,0.0f,1.0f};					// normalized normal of current surface
    GLfloat s[4]={0.0f,0.0f,0.0f,1.0f};					// s-texture coordinate direction, normalized
    GLfloat t[4]={0.0f,0.0f,0.0f,1.0f};					// t-texture coordinate direction, normalized
    GLfloat l[4];										// holds our lightposition to be transformed into object space
    GLfloat Minv[16];									// holds the inverted modelview matrix to do so.
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

    // Build Inverse Modelview Matrix First. This Substitutes One Push/Pop With One glLoadIdentity();
    // Simply Build It By Doing All Transformations Negated And In Reverse Order.
    glLoadIdentity();
    glRotatef(-yrot,0.0f,1.0f,0.0f);
    glRotatef(-xrot,1.0f,0.0f,0.0f);
    glTranslatef(0.0f,0.0f,-z);
    glGetFloatv(GL_MODELVIEW_MATRIX,Minv);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,z);

    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);

    // Transform The Lightposition Into Object Coordinates:
    l[0]=LightPosition[0];
    l[1]=LightPosition[1];
    l[2]=LightPosition[2];
    l[3]=1.0f;											// Homogenous Coordinate
    VMatMult(Minv,l);

/*	PASS#1: Texel-Unit 0:	Use Texture "Bump"
							No Blend
							No Lighting
							No Offset Texture-Coordinates
							Texture-Operation "Replace"
			Texel-Unit 1:	Use Texture "Invbump"
							No Lighting
							Offset Texture Coordinates
							Texture-Operation "Replace"
*/
    // TEXTURE-UNIT #0
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bumpTextures[filter]);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
    // TEXTURE-UNIT #1:
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, invBumpTextures[filter]);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
    // General Switches:
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    // Front Face
    n[0]=0.0f;		n[1]=0.0f;		n[2]=1.0f;
    s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=0; i<4; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,data[5*i]     , data[5*i+1]);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Back Face
    n[0]=0.0f;		n[1]=0.0f;		n[2]=-1.0f;
    s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=4; i<8; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,data[5*i]     , data[5*i+1]);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Top Face
    n[0]=0.0f;		n[1]=1.0f;		n[2]=0.0f;
    s[0]=1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
    for (i=8; i<12; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,data[5*i]     , data[5*i+1]     );
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Bottom Face
    n[0]=0.0f;		n[1]=-1.0f;		n[2]=0.0f;
    s[0]=-1.0f;		s[1]=0.0f;		s[2]=0.0f;
    t[0]=0.0f;		t[1]=0.0f;		t[2]=-1.0f;
    for (i=12; i<16; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,data[5*i]     , data[5*i+1]     );
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Right Face
    n[0]=1.0f;		n[1]=0.0f;		n[2]=0.0f;
    s[0]=0.0f;		s[1]=0.0f;		s[2]=-1.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=16; i<20; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,data[5*i]     , data[5*i+1]     );
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    // Left Face
    n[0]=-1.0f;		n[1]=0.0f;		n[2]=0.0f;
    s[0]=0.0f;		s[1]=0.0f;		s[2]=1.0f;
    t[0]=0.0f;		t[1]=1.0f;		t[2]=0.0f;
    for (i=20; i<24; i++) {
        c[0]=data[5*i+2];
        c[1]=data[5*i+3];
        c[2]=data[5*i+4];
        SetUpBumps(n,c,l,s,t);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,data[5*i]     , data[5*i+1]     );
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,data[5*i]+c[0], data[5*i+1]+c[1]);
        glVertex3f(data[5*i+2], data[5*i+3], data[5*i+4]);
    }
    glEnd();

/* PASS#2	Use Texture "Base"
			Blend GL_DST_COLOR To GL_SRC_COLOR (Multiplies By 2)
			Lighting Enabled
			No Offset Texture-Coordinates
			*/
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glDisable(GL_TEXTURE_2D);
    glActiveTextureARB(GL_TEXTURE0_ARB);
    if (!emboss) {
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,baseTextures[filter]);
        glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
        glEnable(GL_BLEND);
        glEnable(GL_LIGHTING);
        doCube();
    }

    xrot+=xspeed;
    yrot+=yspeed;
    if (xrot>360.0f) xrot-=360.0f;
    if (xrot<0.0f) xrot+=360.0f;
    if (yrot>360.0f) yrot-=360.0f;
    if (yrot<0.0f) yrot+=360.0f;

/* LAST PASS:	Do The Logos! */
    doLogo();

    return true;										// Keep Going
}

bool SceneTutorial22::doMeshNoBumps() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();									// Reset The View
    glTranslatef(0.0f,0.0f,z);

    glRotatef(xrot,1.0f,0.0f,0.0f);
    glRotatef(yrot,0.0f,1.0f,0.0f);
    if (useMultiTexture) {
        glActiveTextureARB(GL_TEXTURE1_ARB);
        glDisable(GL_TEXTURE_2D);
        glActiveTextureARB(GL_TEXTURE0_ARB);
    }
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D,baseTextures[filter]);
    glBlendFunc(GL_DST_COLOR,GL_SRC_COLOR);
    glEnable(GL_LIGHTING);
    doCube();

    xrot+=xspeed;
    yrot+=yspeed;
    if (xrot>360.0f) xrot-=360.0f;
    if (xrot<0.0f) xrot+=360.0f;
    if (yrot>360.0f) yrot-=360.0f;
    if (yrot<0.0f) yrot+=360.0f;

/* LAST PASS:	Do The Logos! */
    doLogo();

    return true;										// Keep Going
}

void SceneTutorial22::VMatMult(GLfloat *M, GLfloat *v) {
    GLfloat res[3];
    res[0]=M[ 0]*v[0]+M[ 1]*v[1]+M[ 2]*v[2]+M[ 3]*v[3];
    res[1]=M[ 4]*v[0]+M[ 5]*v[1]+M[ 6]*v[2]+M[ 7]*v[3];
    res[2]=M[ 8]*v[0]+M[ 9]*v[1]+M[10]*v[2]+M[11]*v[3];;
    v[0]=res[0];
    v[1]=res[1];
    v[2]=res[2];
    v[3]=M[15];											// Homogenous Coordinate
}

void SceneTutorial22::SetUpBumps(GLfloat *n, GLfloat *c, GLfloat *l, GLfloat *s, GLfloat *t) {
    GLfloat v[3];							// Vertex From Current Position To Light
    GLfloat lenQ;							// Used To Normalize

    // Calculate v From Current Vector c To Lightposition And Normalize v
    v[0]=l[0]-c[0];
    v[1]=l[1]-c[1];
    v[2]=l[2]-c[2];
    lenQ=(GLfloat) sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    v[0]/=lenQ;		v[1]/=lenQ;		v[2]/=lenQ;
    // Project v Such That We Get Two Values Along Each Texture-Coordinat Axis.
    c[0]=(s[0]*v[0]+s[1]*v[1]+s[2]*v[2])*MAX_EMBOSS;
    c[1]=(t[0]*v[0]+t[1]*v[1]+t[2]*v[2])*MAX_EMBOSS;
}