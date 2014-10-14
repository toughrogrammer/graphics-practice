//
//  Macro.cpp
//  graphics-practice
//
//  Created by loki on 2014. 9. 26..
//  Copyright (c) 2014년 loki. All rights reserved.
//

#include "Macro.h"


void GLVertexByVector3(Vector3 &v)
{
    glVertex3f( v.x, v.y, v.z );
}

long GetMillisecond(struct timeval tv) {
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void RenderBitmapString(void *font, float x, float y, const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

double Random0to1()
{
    return ((double) rand() / (RAND_MAX));
}

double RandomRangeDouble(double start, double end)
{
    double length = (end - start);
    return Random0to1() * length - length/2;
}

int RandomRangeInt(int start, int end)
{
    int length = (end - start);
    return (int)(Random0to1() * length - length/2);
}