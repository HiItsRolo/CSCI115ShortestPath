/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <desert.h>
#include <iostream>

using namespace std;


desert::desert()
{
    //ctor
    livedesert = true;

    red=green=blue=alpha = 1.0;
}

desert::~desert()
{
    //dtor
}

void desert::desertInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    desertTex = TextureLoader(FileName);
}

void desert::drawdesert()
{
    if(livedesert)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,desertTex);

    glPushMatrix();
    glTranslatef(desertBrk.x,desertBrk.y,0.0);

    glScalef(1.0/(float)gridSize,1.0/(float)gridSize,1);


     glBegin(GL_POLYGON);
            glTexCoord2f(0,0);
            glVertex3f(1,1,0.0f);

            glTexCoord2f(1,0);
            glVertex3f(-1,1,0.0f);

            glTexCoord2f(1,1);
            glVertex3f(-1,-1,0.0f);

            glTexCoord2f(0,1);
            glVertex3f(1,-1,0.0f);
    glEnd();
    glPopMatrix();
    }
}

void desert::placedesert(int x, int y)
{
    GetdesertLoc.x= x;
    GetdesertLoc.y= y;

    x+=1;
    y+=1;

    desertBrk.x =  (unitWidth)*x-1-unitWidth/2;
    desertBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




