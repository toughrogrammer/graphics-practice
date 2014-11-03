//
//  SceneTutorial21.cpp
//  graphics-practice
//
//  Created by loki on 2014. 10. 28..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "SceneTutorial21.h"


SceneTutorial21* SceneTutorial21::Create()
{
    SceneTutorial21 *pRet = new SceneTutorial21;
    if( pRet->Init() ) {
        return pRet;
    }
    
    SAFE_DELETE( pRet );
    return pRet;
}

bool SceneTutorial21::Init()
{
    int width = 640;
    int height = 480;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);                 // Set Line Antialiasing
    glEnable(GL_BLEND);                         // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          // Type Of Blending To Use


    for( int i = 0; i < 11; i ++ ) {
        for( int j = 0; j < 10; j ++ ) {
            vline[i][j] = 0;
            hline[j][i] = 0;
        }
    }

    filled = false;
    gameover = false;
    anti = true;
    delay = 0;
    adjust = 3;
    lives = 5;
    level = 1;
    level2 = level;
    stage = 1;


    img = MyImage::LoadImage("Textures/Image.bmp");

    ResetObjects();


    return true;
}

void SceneTutorial21::OnExit()
{
    SAFE_DELETE( img );
}

void SceneTutorial21::Update(float dt)
{
    Scene::Update(dt);

    if (!gameover)							// If Game Isn't Over And Programs Active Move Objects
    {
        for (loop1=0; loop1<(stage*level); loop1++)		// Loop Through The Different Stages
        {
            if ((enemy[loop1].x<player.x) && (enemy[loop1].fy==enemy[loop1].y*40))
            {
                enemy[loop1].x += dt;						// Move The Enemy Right
            }

            if ((enemy[loop1].x>player.x) && (enemy[loop1].fy==enemy[loop1].y*40))
            {
                enemy[loop1].x -= dt;						// Move The Enemy Left
            }

            if ((enemy[loop1].y<player.y) && (enemy[loop1].fx==enemy[loop1].x*60))
            {
                enemy[loop1].y += dt;						// Move The Enemy Down
            }

            if ((enemy[loop1].y>player.y) && (enemy[loop1].fx==enemy[loop1].x*60))
            {
                enemy[loop1].y -= dt;						// Move The Enemy Up
            }

            if (delay>(3-level) && (hourglass.fx!=2))	// If Our Delay Is Done And Player Doesn't Have Hourglass
            {
                delay=0;								// Reset The Delay Counter Back To Zero
                for (loop2=0; loop2<(stage*level); loop2++)	// Loop Through All The Enemies
                {
                    if (enemy[loop2].fx<enemy[loop2].x*60)	// Is Fine Position On X Axis Lower Than Intended Position?
                    {
                        enemy[loop2].fx+=steps[adjust];	// If So, Increase Fine Position On X Axis
                        enemy[loop2].spin+=steps[adjust];	// Spin Enemy Clockwise
                    }
                    if (enemy[loop2].fx>enemy[loop2].x*60)	// Is Fine Position On X Axis Higher Than Intended Position?
                    {
                        enemy[loop2].fx-=steps[adjust];	// If So, Decrease Fine Position On X Axis
                        enemy[loop2].spin-=steps[adjust];	// Spin Enemy Counter Clockwise
                    }
                    if (enemy[loop2].fy<enemy[loop2].y*40)	// Is Fine Position On Y Axis Lower Than Intended Position?
                    {
                        enemy[loop2].fy+=steps[adjust];	// If So, Increase Fine Position On Y Axis
                        enemy[loop2].spin+=steps[adjust];	// Spin Enemy Clockwise
                    }
                    if (enemy[loop2].fy>enemy[loop2].y*40)	// Is Fine Position On Y Axis Higher Than Intended Position?
                    {
                        enemy[loop2].fy-=steps[adjust];	// If So, Decrease Fine Position On Y Axis
                        enemy[loop2].spin-=steps[adjust];	// Spin Enemy Counter Clockwise
                    }
                }
            }

            // Are Any Of The Enemies On Top Of The Player?
            if ((enemy[loop1].fx==player.fx) && (enemy[loop1].fy==player.fy))
            {
                lives--;								// If So, Player Loses A Life

                if (lives==0)							// Are We Out Of Lives?
                {
                    gameover=true;						// If So, gameover Becomes TRUE
                }

                ResetObjects();							// Reset Player / Enemy Positions
//                PlaySound("Data/Die.wav", NULL, SND_SYNC);	// Play The Death Sound
            }
        }

        if (Keyboard::PressedSpecial(GLUT_KEY_RIGHT) && (player.x<10) && (player.fx==player.x*60) && (player.fy==player.y*40))
        {
            hline[player.x][player.y]=true;				// Mark The Current Horizontal Border As Filled
            player.x += 5 * dt;									// Move The Player Right
        }
        if (Keyboard::PressedSpecial(GLUT_KEY_LEFT) && (player.x>0) && (player.fx==player.x*60) && (player.fy==player.y*40))
        {
            player.x--;									// Move The Player Left
            hline[player.x][player.y]=true;				// Mark The Current Horizontal Border As Filled
        }
        if (Keyboard::PressedSpecial(GLUT_KEY_DOWN) && (player.y<10) && (player.fx==player.x*60) && (player.fy==player.y*40))
        {
            vline[player.x][player.y]=true;				// Mark The Current Verticle Border As Filled
            player.y++;									// Move The Player Down
        }
        if (Keyboard::PressedSpecial(GLUT_KEY_UP) && (player.y>0) && (player.fx==player.x*60) && (player.fy==player.y*40))
        {
            player.y--;									// Move The Player Up
            vline[player.x][player.y]=true;				// Mark The Current Verticle Border As Filled
        }

        if (player.fx<player.x*60)						// Is Fine Position On X Axis Lower Than Intended Position?
        {
            player.fx+=steps[adjust];					// If So, Increase The Fine X Position
        }
        if (player.fx>player.x*60)						// Is Fine Position On X Axis Greater Than Intended Position?
        {
            player.fx-=steps[adjust];					// If So, Decrease The Fine X Position
        }
        if (player.fy<player.y*40)						// Is Fine Position On Y Axis Lower Than Intended Position?
        {
            player.fy+=steps[adjust];					// If So, Increase The Fine Y Position
        }
        if (player.fy>player.y*40)						// Is Fine Position On Y Axis Lower Than Intended Position?
        {
            player.fy-=steps[adjust];					// If So, Decrease The Fine Y Position
        }
    }
    else												// Otherwise
    {
        if (Keyboard::PressedNormal(' '))									// If Spacebar Is Being Pressed
        {
            gameover=false;								// gameover Becomes FALSE
            filled=true;								// filled Becomes TRUE
            level=1;									// Starting Level Is Set Back To One
            level2=1;									// Displayed Level Is Also Set To One
            stage=0;									// Game Stage Is Set To Zero
            lives=5;									// Lives Is Set To Five
        }
    }

    if (filled)											// Is The Grid Filled In?
    {
//        PlaySound("Data/Complete.wav", NULL, SND_SYNC);	// If So, Play The Level Complete Sound
        stage++;										// Increase The Stage
        if (stage>3)									// Is The Stage Higher Than 3?
        {
            stage=1;									// If So, Set The Stage To One
            level++;									// Increase The Level
            level2++;									// Increase The Displayed Level
            if (level>3)								// Is The Level Greater Than 3?
            {
                level=3;								// If So, Set The Level To 3
                lives++;								// Give The Player A Free Life
                if (lives>5)							// Does The Player Have More Than 5 Lives?
                {
                    lives=5;							// If So, Set Lives To Five
                }
            }
        }

        ResetObjects();									// Reset Player / Enemy Positions

        for (loop1=0; loop1<11; loop1++)				// Loop Through The Grid X Coordinates
        {
            for (loop2=0; loop2<11; loop2++)			// Loop Through The Grid Y Coordinates
            {
                if (loop1<10)							// If X Coordinate Is Less Than 10
                {
                    hline[loop1][loop2]=false;			// Set The Current Horizontal Value To FALSE
                }
                if (loop2<10)							// If Y Coordinate Is Less Than 10
                {
                    vline[loop1][loop2]=false;			// Set The Current Vertical Value To FALSE
                }
            }
        }
    }

    // If The Player Hits The Hourglass While It's Being Displayed On The Screen
    if ((player.fx==hourglass.x*60) && (player.fy==hourglass.y*40) && (hourglass.fx==1))
    {
        // Play Freeze Enemy Sound
//        PlaySound("Data/freeze.wav", NULL, SND_ASYNC | SND_LOOP);
        hourglass.fx=2;									// Set The hourglass fx Variable To Two
        hourglass.fy=0;									// Set The hourglass fy Variable To Zero
    }

    player.spin+=0.5f*steps[adjust];					// Spin The Player Clockwise
    if (player.spin>360.0f)								// Is The spin Value Greater Than 360?
    {
        player.spin-=360;								// If So, Subtract 360
    }

    hourglass.spin-=0.25f*steps[adjust];				// Spin The Hourglass Counter Clockwise
    if (hourglass.spin<0.0f)							// Is The spin Value Less Than 0?
    {
        hourglass.spin+=360.0f;							// If So, Add 360
    }

    hourglass.fy+=steps[adjust];						// Increase The hourglass fy Variable
    if ((hourglass.fx==0) && (hourglass.fy>6000/level))	// Is The hourglass fx Variable Equal To 0 And The fy
    {													// Variable Greater Than 6000 Divided By The Current Level?
//        PlaySound("Data/hourglass.wav", NULL, SND_ASYNC);	// If So, Play The Hourglass Appears Sound
        hourglass.x=rand()%10+1;						// Give The Hourglass A Random X Value
        hourglass.y=rand()%11;							// Give The Hourglass A Random Y Value
        hourglass.fx=1;									// Set hourglass fx Variable To One (Hourglass Stage)
        hourglass.fy=0;									// Set hourglass fy Variable To Zero (Counter)
    }

    if ((hourglass.fx==1) && (hourglass.fy>6000/level))	// Is The hourglass fx Variable Equal To 1 And The fy
    {													// Variable Greater Than 6000 Divided By The Current Level?
        hourglass.fx=0;									// If So, Set fx To Zero (Hourglass Will Vanish)
        hourglass.fy=0;									// Set fy to Zero (Counter Is Reset)
    }

    if ((hourglass.fx==2) && (hourglass.fy>500+(500*level)))	// Is The hourglass fx Variable Equal To 2 And The fy
    {													// Variable Greater Than 500 Plus 500 Times The Current Level?
//        PlaySound(NULL, NULL, 0);						// If So, Kill The Freeze Sound
        hourglass.fx=0;									// Set hourglass fx Variable To Zero
        hourglass.fy=0;									// Set hourglass fy Variable To Zero
    }

    delay++;											// Increase The Enemy Delay Counter
}

void SceneTutorial21::Draw()
{
    Scene::Draw();

    int width = 640;
    int height = 480;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();

    // rendering fonts
    {
        glColor3d(1.0f, 0.5f, 1.0f);
        RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 207, 24, "GRID CRAZY");
        glColor3f(1.0f, 1.0f, 0.0f);
        RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 20, 20, "Level:");
        RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 20, 40, "Stage:");

        if( gameover ) {
            glColor3ub(rand()%255, rand()%255, rand()%255);
            RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 472, 20, "GAME OVER");
            RenderBitmapString(GLUT_BITMAP_HELVETICA_18, 456, 40, "PRESS SPACE");
        }
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    for (loop1=0; loop1<lives-1; loop1++)					// Loop Through Lives Minus Current Life
    {
        glLoadIdentity();									// Reset The View
        glTranslatef(490+(loop1*40.0f),40.0f,0.0f);			// Move To The Right Of Our Title Text
        glRotatef(-player.spin,0.0f,0.0f,1.0f);				// Rotate Counter Clockwise
        glColor3f(0.0f,1.0f,0.0f);							// Set Player Color To Light Green
        glBegin(GL_LINES);									// Start Drawing Our Player Using Lines
        glVertex2d(-5,-5);								// Top Left Of Player
        glVertex2d( 5, 5);								// Bottom Right Of Player
        glVertex2d( 5,-5);								// Top Right Of Player
        glVertex2d(-5, 5);								// Bottom Left Of Player
        glEnd();											// Done Drawing The Player
        glRotatef(-player.spin*0.5f,0.0f,0.0f,1.0f);		// Rotate Counter Clockwise
        glColor3f(0.0f,0.75f,0.0f);							// Set Player Color To Dark Green
        glBegin(GL_LINES);									// Start Drawing Our Player Using Lines
        glVertex2d(-7, 0);								// Left Center Of Player
        glVertex2d( 7, 0);								// Right Center Of Player
        glVertex2d( 0,-7);								// Top Center Of Player
        glVertex2d( 0, 7);								// Bottom Center Of Player
        glEnd();											// Done Drawing The Player
    }

    filled=true;											// Set Filled To True Before Testing
    glLineWidth(2.0f);										// Set Line Width For Cells To 2.0f
    glDisable(GL_LINE_SMOOTH);								// Disable Antialiasing
    glLoadIdentity();										// Reset The Current Modelview Matrix
    for (loop1=0; loop1<11; loop1++)						// Loop From Left To Right
    {
        for (loop2=0; loop2<11; loop2++)					// Loop From Top To Bottom
        {
            glColor3f(0.0f,0.5f,1.0f);						// Set Line Color To Blue
            if (hline[loop1][loop2])						// Has The Horizontal Line Been Traced
            {
                glColor3f(1.0f,1.0f,1.0f);					// If So, Set Line Color To White
            }

            if (loop1<10)									// Dont Draw To Far Right
            {
                if (!hline[loop1][loop2])					// If A Horizontal Line Isn't Filled
                {
                    filled=false;							// filled Becomes False
                }
                glBegin(GL_LINES);							// Start Drawing Horizontal Cell Borders
                glVertex2d(20+(loop1*60),70+(loop2*40));// Left Side Of Horizontal Line
                glVertex2d(80+(loop1*60),70+(loop2*40));// Right Side Of Horizontal Line
                glEnd();									// Done Drawing Horizontal Cell Borders
            }

            glColor3f(0.0f,0.5f,1.0f);						// Set Line Color To Blue
            if (vline[loop1][loop2])						// Has The Horizontal Line Been Traced
            {
                glColor3f(1.0f,1.0f,1.0f);					// If So, Set Line Color To White
            }
            if (loop2<10)									// Dont Draw To Far Down
            {
                if (!vline[loop1][loop2])					// If A Verticle Line Isn't Filled
                {
                    filled=false;							// filled Becomes False
                }
                glBegin(GL_LINES);							// Start Drawing Verticle Cell Borders
                glVertex2d(20+(loop1*60),70+(loop2*40));// Left Side Of Horizontal Line
                glVertex2d(20+(loop1*60),110+(loop2*40));// Right Side Of Horizontal Line
                glEnd();									// Done Drawing Verticle Cell Borders
            }

            glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping
            glColor3f(1.0f,1.0f,1.0f);						// Bright White Color
            glBindTexture(GL_TEXTURE_2D, img->GetTexture());		// Select The Tile Image
            if ((loop1<10) && (loop2<10))					// If In Bounds, Fill In Traced Boxes
            {
                // Are All Sides Of The Box Traced?
                if (hline[loop1][loop2] && hline[loop1][loop2+1] && vline[loop1][loop2] && vline[loop1+1][loop2])
                {
                    glBegin(GL_QUADS);						// Draw A Textured Quad
                    glTexCoord2f(float(loop1/10.0f)+0.1f,1.0f-(float(loop2/10.0f)));
                    glVertex2d(20+(loop1*60)+59,(70+loop2*40+1));	// Top Right
                    glTexCoord2f(float(loop1/10.0f),1.0f-(float(loop2/10.0f)));
                    glVertex2d(20+(loop1*60)+1,(70+loop2*40+1));	// Top Left
                    glTexCoord2f(float(loop1/10.0f),1.0f-(float(loop2/10.0f)+0.1f));
                    glVertex2d(20+(loop1*60)+1,(70+loop2*40)+39);	// Bottom Left
                    glTexCoord2f(float(loop1/10.0f)+0.1f,1.0f-(float(loop2/10.0f)+0.1f));
                    glVertex2d(20+(loop1*60)+59,(70+loop2*40)+39);	// Bottom Right
                    glEnd();								// Done Texturing The Box
                }
            }
            glDisable(GL_TEXTURE_2D);						// Disable Texture Mapping
        }
    }
    glLineWidth(1.0f);										// Set The Line Width To 1.0f

    if (anti)												// Is Anti TRUE?
    {
        glEnable(GL_LINE_SMOOTH);							// If So, Enable Antialiasing
    }

    if (hourglass.fx==1)									// If fx=1 Draw The Hourglass
    {
        glLoadIdentity();									// Reset The Modelview Matrix
        glTranslatef(20.0f+(hourglass.x*60),70.0f+(hourglass.y*40),0.0f);	// Move To The Fine Hourglass Position
        glRotatef(hourglass.spin,0.0f,0.0f,1.0f);			// Rotate Clockwise
        glColor3ub(rand()%255,rand()%255,rand()%255);		// Set Hourglass Color To Random Color
        glBegin(GL_LINES);									// Start Drawing Our Hourglass Using Lines
        glVertex2d(-5,-5);								// Top Left Of Hourglass
        glVertex2d( 5, 5);								// Bottom Right Of Hourglass
        glVertex2d( 5,-5);								// Top Right Of Hourglass
        glVertex2d(-5, 5);								// Bottom Left Of Hourglass
        glVertex2d(-5, 5);								// Bottom Left Of Hourglass
        glVertex2d( 5, 5);								// Bottom Right Of Hourglass
        glVertex2d(-5,-5);								// Top Left Of Hourglass
        glVertex2d( 5,-5);								// Top Right Of Hourglass
        glEnd();											// Done Drawing The Hourglass
    }

    glLoadIdentity();										// Reset The Modelview Matrix
    glTranslatef(player.fx+20.0f,player.fy+70.0f,0.0f);		// Move To The Fine Player Position
    glRotatef(player.spin,0.0f,0.0f,1.0f);					// Rotate Clockwise
    glColor3f(0.0f,1.0f,0.0f);								// Set Player Color To Light Green
    glBegin(GL_LINES);										// Start Drawing Our Player Using Lines
    glVertex2d(-5,-5);									// Top Left Of Player
    glVertex2d( 5, 5);									// Bottom Right Of Player
    glVertex2d( 5,-5);									// Top Right Of Player
    glVertex2d(-5, 5);									// Bottom Left Of Player
    glEnd();												// Done Drawing The Player
    glRotatef(player.spin*0.5f,0.0f,0.0f,1.0f);				// Rotate Clockwise
    glColor3f(0.0f,0.75f,0.0f);								// Set Player Color To Dark Green
    glBegin(GL_LINES);										// Start Drawing Our Player Using Lines
    glVertex2d(-7, 0);									// Left Center Of Player
    glVertex2d( 7, 0);									// Right Center Of Player
    glVertex2d( 0,-7);									// Top Center Of Player
    glVertex2d( 0, 7);									// Bottom Center Of Player
    glEnd();												// Done Drawing The Player

    for (loop1=0; loop1<(stage*level); loop1++)				// Loop To Draw Enemies
    {
        glLoadIdentity();									// Reset The Modelview Matrix
        glTranslatef(enemy[loop1].fx+20.0f,enemy[loop1].fy+70.0f,0.0f);
        glColor3f(1.0f,0.5f,0.5f);							// Make Enemy Body Pink
        glBegin(GL_LINES);									// Start Drawing Enemy
        glVertex2d( 0,-7);								// Top Point Of Body
        glVertex2d(-7, 0);								// Left Point Of Body
        glVertex2d(-7, 0);								// Left Point Of Body
        glVertex2d( 0, 7);								// Bottom Point Of Body
        glVertex2d( 0, 7);								// Bottom Point Of Body
        glVertex2d( 7, 0);								// Right Point Of Body
        glVertex2d( 7, 0);								// Right Point Of Body
        glVertex2d( 0,-7);								// Top Point Of Body
        glEnd();											// Done Drawing Enemy Body
        glRotatef(enemy[loop1].spin,0.0f,0.0f,1.0f);		// Rotate The Enemy Blade
        glColor3f(1.0f,0.0f,0.0f);							// Make Enemy Blade Red
        glBegin(GL_LINES);									// Start Drawing Enemy Blade
        glVertex2d(-7,-7);								// Top Left Of Enemy
        glVertex2d( 7, 7);								// Bottom Right Of Enemy
        glVertex2d(-7, 7);								// Bottom Left Of Enemy
        glVertex2d( 7,-7);								// Top Right Of Enemy
        glEnd();											// Done Drawing Enemy Blade
    }

    glutSwapBuffers();
}

void SceneTutorial21::ProcessNormalKeys(unsigned char key, int x, int y)
{
    if( key == 'a' || key == 'A' ) {
        anti = !anti;
    }
}

void SceneTutorial21::ResetObjects() {
    player.x=0;												// Reset Player X Position To Far Left Of The Screen
    player.y=0;												// Reset Player Y Position To The Top Of The Screen
    player.fx=0;											// Set Fine X Position To Match
    player.fy=0;											// Set Fine Y Position To Match

    enemy.resize(9);
    for (loop1=0; loop1<(stage*level); loop1++)				// Loop Through All The Enemies
    {
        enemy[loop1].x=5+rand()%6;							// Select A Random X Position
        enemy[loop1].y=rand()%11;							// Select A Random Y Position
        enemy[loop1].fx=enemy[loop1].x*60;					// Set Fine X To Match
        enemy[loop1].fy=enemy[loop1].y*40;					// Set Fine Y To Match
    }
}