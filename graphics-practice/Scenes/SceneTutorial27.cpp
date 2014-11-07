//
//  SceneTutorial27.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 14..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial27.h"

// Definition Of "INFINITY" For Calculating The Extension Vector For The Shadow Volume
#define INFINITY    100


SceneTutorial27* SceneTutorial27::Create()
{
    SceneTutorial27 *pRet = new SceneTutorial27;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial27::Init()
{
    if (!InitObjects())
        return false;					// Function For Initializing Our Object(s)
    
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glClearStencil(0);									// Stencil Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Set Light1 Position
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);			// Set Light1 Ambience
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);			// Set Light1 Diffuse
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc);		// Set Light1 Specular
    glEnable(GL_LIGHT1);								// Enable Light1
    glEnable(GL_LIGHTING);								// Enable Lighting
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);			// Set Material Ambience
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);			// Set Material Diffuse
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpc);		// Set Material Specular
    glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);		// Set Material Shininess
    
    glCullFace(GL_BACK);								// Set Culling Face To Back Face
    glEnable(GL_CULL_FACE);								// Enable Culling
    glClearColor(0.1f, 1.0f, 0.5f, 1.0f);				// Set Clear Color (Greenish Color)
    
    q = gluNewQuadric();								// Initialize Quadratic
    gluQuadricNormals(q, GL_SMOOTH);					// Enable Smooth Normal Generation
    gluQuadricTexture(q, GL_FALSE);						// Disable Auto Texture Coords

    
    _cameraPosition.Set(0, 0, 2);
    _cameraScale.Set(1.0f, 1.0f, 1.0f);
    

    return true;
}

void SceneTutorial27::OnExit()
{

}

void SceneTutorial27::Update(float dt)
{
    Scene::Update(dt);
    
    xrot += xrotspeed * dt;                                  // Update X Rotation Angle By xrotspeed
    yrot += yrotspeed * dt;                                  // Update Y Rotation Angle By yrotspeed
    
    // Adjust Light's Position
    if (Keyboard::PressedNormal('L')) LightPos[0] += 0.05f;				// 'L' Moves Light Right
    if (Keyboard::PressedNormal('J')) LightPos[0] -= 0.05f;				// 'J' Moves Light Left
    
    if (Keyboard::PressedNormal('I')) LightPos[1] += 0.05f;				// 'I' Moves Light Up
    if (Keyboard::PressedNormal('K')) LightPos[1] -= 0.05f;				// 'K' Moves Light Down
    
    if (Keyboard::PressedNormal('O')) LightPos[2] += 0.05f;				// 'O' Moves Light Toward Viewer
    if (Keyboard::PressedNormal('U')) LightPos[2] -= 0.05f;				// 'U' Moves Light Away From Viewer
}

void SceneTutorial27::Draw()
{
    Scene::Draw();
    
    float Minv[16];
    float wlp[4];
    float lp[4];
    
    // Clear Color Buffer, Depth Buffer, Stencil Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glLoadIdentity();									// Reset Modelview Matrix
    glTranslatef(0.0f, 0.0f, -20.0f);					// Zoom Into Screen 20 Units
    glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Position Light1
    glTranslatef(SpherePos[0], SpherePos[1], SpherePos[2]);	// Position The Sphere
    gluSphere(q, 1.5f, 32, 16);							// Draw A Sphere
    
    // calculate light's position relative to local coordinate system
    // dunno if this is the best way to do it, but it actually works
    // if u find another aproach, let me know ;)
    
    // we build the inversed matrix by doing all the actions in reverse order
    // and with reverse parameters (notice -xrot, -yrot, -ObjPos[], etc.)
    glLoadIdentity();									// Reset Matrix
    glRotatef(-yrot, 0.0f, 1.0f, 0.0f);					// Rotate By -yrot On Y Axis
    glRotatef(-xrot, 1.0f, 0.0f, 0.0f);					// Rotate By -xrot On X Axis
    glGetFloatv(GL_MODELVIEW_MATRIX,Minv);				// Retrieve ModelView Matrix (Stores In Minv)
    lp[0] = LightPos[0];								// Store Light Position X In lp[0]
    lp[1] = LightPos[1];								// Store Light Position Y In lp[1]
    lp[2] = LightPos[2];								// Store Light Position Z In lp[2]
    lp[3] = LightPos[3];								// Store Light Direction In lp[3]
    VMatMult(Minv, lp);									// We Store Rotated Light Vector In 'lp' Array
    glTranslatef(-ObjPos[0], -ObjPos[1], -ObjPos[2]);	// Move Negative On All Axis Based On ObjPos[] Values (X, Y, Z)
    glGetFloatv(GL_MODELVIEW_MATRIX,Minv);				// Retrieve ModelView Matrix From Minv
    wlp[0] = 0.0f;										// World Local Coord X To 0
    wlp[1] = 0.0f;										// World Local Coord Y To 0
    wlp[2] = 0.0f;										// World Local Coord Z To 0
    wlp[3] = 1.0f;
    VMatMult(Minv, wlp);								// We Store The Position Of The World Origin Relative To The
    // Local Coord. System In 'wlp' Array
    lp[0] += wlp[0];									// Adding These Two Gives Us The
    lp[1] += wlp[1];									// Position Of The Light Relative To
    lp[2] += wlp[2];									// The Local Coordinate System
    
    glColor4f(0.7f, 0.4f, 0.0f, 1.0f);					// Set Color To An Orange
    glLoadIdentity();									// Reset Modelview Matrix
    glTranslatef(0.0f, 0.0f, -20.0f);					// Zoom Into The Screen 20 Units
    DrawGLRoom();										// Draw The Room
    glTranslatef(ObjPos[0], ObjPos[1], ObjPos[2]);		// Position The Object
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);					// Spin It On The X Axis By xrot
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);					// Spin It On The Y Axis By yrot
    DrawShadowedObject(obj);									// Procedure For Drawing The Loaded Object
    castShadow(obj, lp  );								// Procedure For Casting The Shadow Based On The Silhouette
    
    glColor4f(0.7f, 0.4f, 0.0f, 1.0f);					// Set Color To Purplish Blue
    glDisable(GL_LIGHTING);								// Disable Lighting
    glDepthMask(GL_FALSE);								// Disable Depth Mask
    glTranslatef(lp[0], lp[1], lp[2]);					// Translate To Light's Position
    // Notice We're Still In Local Coordinate System
    gluSphere(q, 0.2f, 16, 8);							// Draw A Little Yellow Sphere (Represents Light)
    glEnable(GL_LIGHTING);								// Enable Lighting
    glDepthMask(GL_TRUE);								// Enable Depth Mask
    
    glutSwapBuffers();
}

void SceneTutorial27::ProcessNormalKeys(unsigned char key, int x, int y)
{

}

bool SceneTutorial27::InitObjects()
{
    if( ! readObject("Data/Object2.txt", obj) ) {
        return false;
    }
    
    return true;
}

bool SceneTutorial27::readObject(const char *filename, ShadowedObject& object )
{
    FILE *pInputFile;
    int i;
    
    pInputFile = fopen( filename, "r" );
    if ( pInputFile == NULL )
    {
        cerr << "Unable to open the object file: " << filename << endl;
        return false;
    }
    
    // Read Vertices
    fscanf( pInputFile, "%d", &object.nVertices );
    object.pVertices = new Vector3[object.nVertices];
    for ( i = 0; i < object.nVertices; i++ )
    {
        fscanf( pInputFile, "%f", &object.pVertices[i].x );
        fscanf( pInputFile, "%f", &object.pVertices[i].y );
        fscanf( pInputFile, "%f", &object.pVertices[i].z );
    }
    
    // Read Faces
    fscanf( pInputFile, "%d", &object.nFaces );
    object.pFaces = new Face[object.nFaces];
    for ( i = 0; i < object.nFaces; i++ )
    {
        int j;
        Face *pFace = &object.pFaces[i];
        
        for ( j = 0; j < 3; j++ )
            pFace->neighbourIndices[j] = -1; // No Neigbours Set Up Yet
        
        for ( j = 0; j < 3; j++ )
        {
            fscanf( pInputFile, "%d", &pFace->vertexIndices[j] );
            pFace->vertexIndices[j]--;       // Files Specify Them With A 1 Array Base, But We Use A 0 Array Base
        }
        
        for ( j = 0; j < 3; j++ )
        {
            fscanf( pInputFile, "%f", &pFace->normals[j].x );
            fscanf( pInputFile, "%f", &pFace->normals[j].y );
            fscanf( pInputFile, "%f", &pFace->normals[j].z );
        }
    }
    return true;
}

void SceneTutorial27::VMatMult(float M[16], float v[4])
{
    GLfloat res[4];										// Hold Calculated Results
    res[0]=M[ 0]*v[0]+M[ 4]*v[1]+M[ 8]*v[2]+M[12]*v[3];
    res[1]=M[ 1]*v[0]+M[ 5]*v[1]+M[ 9]*v[2]+M[13]*v[3];
    res[2]=M[ 2]*v[0]+M[ 6]*v[1]+M[10]*v[2]+M[14]*v[3];
    res[3]=M[ 3]*v[0]+M[ 7]*v[1]+M[11]*v[2]+M[15]*v[3];
    v[0]=res[0];										// Results Are Stored Back In v[]
    v[1]=res[1];
    v[2]=res[2];
    v[3]=res[3];										// Homogenous Coordinate
}

void SceneTutorial27::DrawGLRoom()										// Draw The Room (Box)
{
    glBegin(GL_QUADS);									// Begin Drawing Quads
    // Floor
    glNormal3f(0.0f, 1.0f, 0.0f);					// Normal Pointing Up
    glVertex3f(-10.0f,-10.0f,-20.0f);				// Back Left
    glVertex3f(-10.0f,-10.0f, 20.0f);				// Front Left
    glVertex3f( 10.0f,-10.0f, 20.0f);				// Front Right
    glVertex3f( 10.0f,-10.0f,-20.0f);				// Back Right
    // Ceiling
    glNormal3f(0.0f,-1.0f, 0.0f);					// Normal Point Down
    glVertex3f(-10.0f, 10.0f, 20.0f);				// Front Left
    glVertex3f(-10.0f, 10.0f,-20.0f);				// Back Left
    glVertex3f( 10.0f, 10.0f,-20.0f);				// Back Right
    glVertex3f( 10.0f, 10.0f, 20.0f);				// Front Right
    // Front Wall
    glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Away From Viewer
    glVertex3f(-10.0f, 10.0f,-20.0f);				// Top Left
    glVertex3f(-10.0f,-10.0f,-20.0f);				// Bottom Left
    glVertex3f( 10.0f,-10.0f,-20.0f);				// Bottom Right
    glVertex3f( 10.0f, 10.0f,-20.0f);				// Top Right
    // Back Wall
    glNormal3f(0.0f, 0.0f,-1.0f);					// Normal Pointing Towards Viewer
    glVertex3f( 10.0f, 10.0f, 20.0f);				// Top Right
    glVertex3f( 10.0f,-10.0f, 20.0f);				// Bottom Right
    glVertex3f(-10.0f,-10.0f, 20.0f);				// Bottom Left
    glVertex3f(-10.0f, 10.0f, 20.0f);				// Top Left
    // Left Wall
    glNormal3f(1.0f, 0.0f, 0.0f);					// Normal Pointing Right
    glVertex3f(-10.0f, 10.0f, 20.0f);				// Top Front
    glVertex3f(-10.0f,-10.0f, 20.0f);				// Bottom Front
    glVertex3f(-10.0f,-10.0f,-20.0f);				// Bottom Back
    glVertex3f(-10.0f, 10.0f,-20.0f);				// Top Back
    // Right Wall
    glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
    glVertex3f( 10.0f, 10.0f,-20.0f);				// Top Back
    glVertex3f( 10.0f,-10.0f,-20.0f);				// Bottom Back
    glVertex3f( 10.0f,-10.0f, 20.0f);				// Bottom Front
    glVertex3f( 10.0f, 10.0f, 20.0f);				// Top Front
    glEnd();											// Done Drawing Quads
}

// procedure for drawing the object - very simple
void SceneTutorial27::DrawShadowedObject(const ShadowedObject& object){
    glBegin( GL_TRIANGLES );
    for ( int i = 0; i < object.nFaces; i++ )
    {
        const Face& face = object.pFaces[i];
        for ( int j = 0; j < 3; j++ )
        {
            const Vector3& vertex = object.pVertices[face.vertexIndices[j]];
            glNormal3f( face.normals[j].x, face.normals[j].y, face.normals[j].z );
            glVertex3f( vertex.x, vertex.y, vertex.z );
        }
    }
    glEnd();
}

void SceneTutorial27::calculatePlane( const ShadowedObject& object, Face& face )
{
    // Get Shortened Names For The Vertices Of The Face
    const Vector3& v1 = object.pVertices[face.vertexIndices[0]];
    const Vector3& v2 = object.pVertices[face.vertexIndices[1]];
    const Vector3& v3 = object.pVertices[face.vertexIndices[2]];
    face.planeEquation.a = v1.y*(v2.z-v3.z) + v2.y*(v3.z-v1.z) + v3.y*(v1.z-v2.z);
    face.planeEquation.b = v1.z*(v2.x-v3.x) + v2.z*(v3.x-v1.x) + v3.z*(v1.x-v2.x);
    face.planeEquation.c = v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y) + v3.x*(v1.y-v2.y);
    face.planeEquation.d = -( v1.x*( v2.y*v3.z - v3.y*v2.z ) +
                             v2.x*(v3.y*v1.z - v1.y*v3.z) +
                             v3.x*(v1.y*v2.z - v2.y*v1.z) );
}

void SceneTutorial27::castShadow(ShadowedObject& object, GLfloat *lightPosition)
{
    // Determine Which Faces Are Visible By The Light.
    for ( int i = 0; i < object.nFaces; i++ )
    {
        const Plane& plane = object.pFaces[i].planeEquation;
        GLfloat side = plane.a*lightPosition[0]+
        plane.b*lightPosition[1]+
        plane.c*lightPosition[2]+
        plane.d;
        if ( side > 0 )
            object.pFaces[i].visible = true;
        else
            object.pFaces[i].visible = false;
    }
    
    glPushAttrib( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT );
    glDisable( GL_LIGHTING ); // Turn Off Lighting
    glDepthMask( GL_FALSE ); // Turn Off Writing To The Depth-Buffer
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_STENCIL_TEST ); // Turn On Stencil Buffer Testing
    glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE ); // Don't Draw Into The Colour Buffer
    glStencilFunc( GL_ALWAYS, 1, 0xFFFFFFFFL );
    
    // First Pass. Increase Stencil Value In The Shadow
    glFrontFace( GL_CCW );
    glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );
    doShadowPass( obj, LightPos );
    // Second Pass. Decrease Stencil Value In The Shadow
    glFrontFace( GL_CW );
    glStencilOp( GL_KEEP, GL_KEEP, GL_DECR );
    doShadowPass( obj, LightPos );
    
    
    glFrontFace( GL_CCW );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE ); // Enable Rendering To Colour Buffer For All Components
    // Draw A Shadowing Rectangle Covering The Entire Screen
    glColor4f( 0.0f, 0.0f, 0.0f, 0.4f );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glStencilFunc( GL_NOTEQUAL, 0, 0xFFFFFFFFL );
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
    glPushMatrix();
    glLoadIdentity();
    glBegin( GL_TRIANGLE_STRIP );
    glVertex3f(-0.1f, 0.1f,-0.10f);
    glVertex3f(-0.1f,-0.1f,-0.10f);
    glVertex3f( 0.1f, 0.1f,-0.10f);
    glVertex3f( 0.1f,-0.1f,-0.10f);
    glEnd();
    glPopMatrix();
    glPopAttrib();
}

void SceneTutorial27::doShadowPass( ShadowedObject& object, GLfloat *lightPosition )
{
    for ( int i = 0; i < object.nFaces; i++ )
    {
        const Face& face = object.pFaces[i];
        if ( face.visible )
        {
            // Go Through Each Edge
            for ( int j = 0; j < 3; j++ )
            {
                int neighbourIndex = face.neighbourIndices[j];
                // If There Is No Neighbour, Or Its Neighbouring Face Is Not Visible, Then This Edge Casts A Shadow
                if ( neighbourIndex == -1 || object.pFaces[neighbourIndex].visible == false )
                {
                    // Get The Points On The Edge
                    const Vector3& v1 = object.pVertices[face.vertexIndices[j]];
                    const Vector3& v2 = object.pVertices[face.vertexIndices[( j+1 )%3]];
                    // Calculate The Two Vertices In Distance
                    Vector3 v3, v4;
                    v3.x = ( v1.x-lightPosition[0] )*INFINITY;
                    v3.y = ( v1.y-lightPosition[1] )*INFINITY;
                    v3.z = ( v1.z-lightPosition[2] )*INFINITY;
                    v4.x = ( v2.x-lightPosition[0] )*INFINITY;
                    v4.y = ( v2.y-lightPosition[1] )*INFINITY;
                    v4.z = ( v2.z-lightPosition[2] )*INFINITY;
                    // Draw The Quadrilateral (As A Triangle Strip)
                    glBegin( GL_TRIANGLE_STRIP );
                    glVertex3f( v1.x, v1.y, v1.z );
                    glVertex3f( v1.x+v3.x, v1.y+v3.y, v1.z+v3.z );
                    glVertex3f( v2.x, v2.y, v2.z );
                    glVertex3f( v2.x+v4.x, v2.y+v4.y, v2.z+v4.z );
                    glEnd();
                }
            }
        }
    }
}