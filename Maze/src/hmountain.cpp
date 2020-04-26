/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <hmountain.h>
#include <iostream>

using namespace std;


hmountain::hmountain()
{
    //ctor
    livehmountain = true;

    red=green=blue=alpha = 1.0;
}

hmountain::~hmountain()
{
    //dtor
}

void hmountain::hmountainInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    hmountainTex = TextureLoader(FileName);
}

void hmountain::drawhmountain()
{
    if(livehmountain)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,hmountainTex);

    glPushMatrix();
    glTranslatef(hmountainBrk.x,hmountainBrk.y,0.0);

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

void hmountain::placehmountain(int x, int y)
{
    GethmountainLoc.x= x;
    GethmountainLoc.y= y;

    x+=1;
    y+=1;

    hmountainBrk.x =  (unitWidth)*x-1-unitWidth/2;
    hmountainBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




