//
//  SceneTutorial28.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial28.h"


SceneTutorial28* SceneTutorial28::Create()
{
    SceneTutorial28 *pRet = new SceneTutorial28;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial28::Init()
{
    glEnable(GL_TEXTURE_2D);                    // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);                    // Enable Smooth Shading
    glClearColor(0.05f, 0.05f, 0.05f, 0.5f);            // Black Background
    glClearDepth(1.0f);                     // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                    // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                     // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really Nice Perspective Calculations
    
    initBezier();                           // Initialize the Bezier's Control Grid ( NEW )
    
    MyImage *img = MyImage::LoadImage("Textures/NeHe.bmp");
    mybezier.texture = img->GetTexture();
    SAFE_DELETE(img);
    
    mybezier.dlBPatch = genBezier(mybezier, divs);          // Generate The Patch ( NEW )
    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    

    return true;
}

void SceneTutorial28::OnExit()
{

}

void SceneTutorial28::Update(float dt)
{
    Scene::Update(dt);
    
    rotz += 1.0f;
}

void SceneTutorial28::Draw()
{
    Scene::Draw();
    
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear Screen And Depth Buffer
    glLoadIdentity();                       // Reset The Current Modelview Matrix
    glTranslatef(0.0f,0.0f,-4.0f);                  // Move Left 1.5 Units And Into The Screen 6.0
    glRotatef(-75.0f,1.0f,0.0f,0.0f);
    glRotatef(rotz,0.0f,0.0f,1.0f);                 // Rotate The Triangle On The Z-Axis
    
    glCallList(mybezier.dlBPatch);                  // Call The Bezier's Display List
    // This Need Only Be Updated When The Patch Changes
    
    if (showCPoints) {                      // If Drawing The Grid Is Toggled On
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0f,0.0f,0.0f);
        for(i=0;i<4;i++) {                   // Draw The Horizontal Lines
            glBegin(GL_LINE_STRIP);
            for(j=0;j<4;j++)
                glVertex3d(mybezier.anchors[i][j].x, mybezier.anchors[i][j].y, mybezier.anchors[i][j].z);
            glEnd();
        }
        for(i=0;i<4;i++) {                   // Draw The Vertical Lines
            glBegin(GL_LINE_STRIP);
            for(j=0;j<4;j++)
                glVertex3d(mybezier.anchors[j][i].x, mybezier.anchors[j][i].y, mybezier.anchors[j][i].z);
            glEnd();
        }
        glColor3f(1.0f,1.0f,1.0f);
        glEnable(GL_TEXTURE_2D);
    }
    
    glutSwapBuffers();
}

void SceneTutorial28::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if (key == 'a') {              // Resolution Up ( NEW )
        divs++;
        mybezier.dlBPatch = genBezier(mybezier, divs);  // Update The Patch
    }
    if (key == 's' && divs > 1) {     // Resolution Down ( NEW )
        divs--;
        mybezier.dlBPatch = genBezier(mybezier, divs);  // Update The Patch
    }
}


SceneTutorial28::POINT_3D SceneTutorial28::pointAdd(POINT_3D p, POINT_3D q)
{
    p.x += q.x;     p.y += q.y;     p.z += q.z;
    return p;
}

// Multiplies A Point And A Constant. Don't Just Use '*'
SceneTutorial28::POINT_3D SceneTutorial28::pointTimes(double c, POINT_3D p)
{
    p.x *= c;   p.y *= c;   p.z *= c;
    return p;
}

// Function For Quick Point Creation
SceneTutorial28::POINT_3D SceneTutorial28::makePoint(double a, double b, double c)
{
    POINT_3D p;
    p.x = a;    p.y = b;    p.z = c;
    return p;
}

SceneTutorial28::POINT_3D SceneTutorial28::Bernstein(float u, POINT_3D *p) {
    POINT_3D    a, b, c, d, r;
    
    a = pointTimes(pow(u,3), p[0]);
    b = pointTimes(3*pow(u,2)*(1-u), p[1]);
    c = pointTimes(3*u*pow((1-u),2), p[2]);
    d = pointTimes(pow((1-u),3), p[3]);
    
    r = pointAdd(pointAdd(a, b), pointAdd(c, d));
    
    return r;
}

// Generates A Display List Based On The Data In The Patch
// And The Number Of Divisions
GLuint SceneTutorial28::genBezier(SceneTutorial28::BEZIER_PATCH patch, int divs) {
    int     u = 0, v;
    float       py, px, pyold;
    GLuint      drawlist = glGenLists(1);           // Make The Display List
    POINT_3D    temp[4];
    POINT_3D    *last = (POINT_3D*)malloc(sizeof(POINT_3D)*(divs+1));
    // Array Of Points To Mark The First Line Of Polys
    
    if (patch.dlBPatch != NULL)                 // Get Rid Of Any Old Display Lists
        glDeleteLists(patch.dlBPatch, 1);
    
    temp[0] = patch.anchors[0][3];                  // The First Derived Curve (Along X-Axis)
    temp[1] = patch.anchors[1][3];
    temp[2] = patch.anchors[2][3];
    temp[3] = patch.anchors[3][3];
    
    for (v=0;v<=divs;v++) {                      // Create The First Line Of Points
        px = ((float)v)/((float)divs);              // Percent Along Y-Axis
        // Use The 4 Points From The Derived Curve To Calculate The Points Along That Curve
        last[v] = Bernstein(px, temp);
    }
    
    glNewList(drawlist, GL_COMPILE);                // Start A New Display List
    glBindTexture(GL_TEXTURE_2D, patch.texture);            // Bind The Texture
    
    for (u=1;u<=divs;u++) {
        py    = ((float)u)/((float)divs);           // Percent Along Y-Axis
        pyold = ((float)u-1.0f)/((float)divs);          // Percent Along Old Y Axis
        
        temp[0] = Bernstein(py, patch.anchors[0]);      // Calculate New Bezier Points
        temp[1] = Bernstein(py, patch.anchors[1]);
        temp[2] = Bernstein(py, patch.anchors[2]);
        temp[3] = Bernstein(py, patch.anchors[3]);
        
        glBegin(GL_TRIANGLE_STRIP);             // Begin A New Triangle Strip
        
        for (v=0;v<=divs;v++) {
            px = ((float)v)/((float)divs);          // Percent Along The X-Axis
            
            glTexCoord2f(pyold, px);            // Apply The Old Texture Coords
            glVertex3d(last[v].x, last[v].y, last[v].z);    // Old Point
            
            last[v] = Bernstein(px, temp);          // Generate New Point
            glTexCoord2f(py, px);               // Apply The New Texture Coords
            glVertex3d(last[v].x, last[v].y, last[v].z);    // New Point
        }
        
        glEnd();                        // END The Triangle Strip
    }
    
    glEndList();                            // END The List
    
    free(last);                         // Free The Old Vertices Array
    return drawlist;                        // Return The Display List
}

void SceneTutorial28::initBezier() {
    mybezier.anchors[0][0] = makePoint(-0.75,   -0.75,  -0.50); // Set The Bezier Vertices
    mybezier.anchors[0][1] = makePoint(-0.25,   -0.75,   0.00);
    mybezier.anchors[0][2] = makePoint( 0.25,   -0.75,   0.00);
    mybezier.anchors[0][3] = makePoint( 0.75,   -0.75,  -0.50);
    mybezier.anchors[1][0] = makePoint(-0.75,   -0.25,  -0.75);
    mybezier.anchors[1][1] = makePoint(-0.25,   -0.25,   0.50);
    mybezier.anchors[1][2] = makePoint( 0.25,   -0.25,   0.50);
    mybezier.anchors[1][3] = makePoint( 0.75,   -0.25,  -0.75);
    mybezier.anchors[2][0] = makePoint(-0.75,    0.25,   0.00);
    mybezier.anchors[2][1] = makePoint(-0.25,    0.25,  -0.50);
    mybezier.anchors[2][2] = makePoint( 0.25,    0.25,  -0.50);
    mybezier.anchors[2][3] = makePoint( 0.75,    0.25,   0.00);
    mybezier.anchors[3][0] = makePoint(-0.75,    0.75,  -0.50);
    mybezier.anchors[3][1] = makePoint(-0.25,    0.75,  -1.00);
    mybezier.anchors[3][2] = makePoint( 0.25,    0.75,  -1.00);
    mybezier.anchors[3][3] = makePoint( 0.75,    0.75,  -0.50);
    mybezier.dlBPatch = NULL;                   // Go Ahead And Initialize This To NULL
}