/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <mmountain.h>
#include <iostream>

using namespace std;


mmountain::mmountain()
{
    //ctor
    livemmountain = true;

    red=green=blue=alpha = 1.0;
}

mmountain::~mmountain()
{
    //dtor
}

void mmountain::mmountainInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    mmountainTex = TextureLoader(FileName);
}

void mmountain::drawmmountain()
{
    if(livemmountain)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,mmountainTex);

    glPushMatrix();
    glTranslatef(mmountainBrk.x,mmountainBrk.y,0.0);

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

void mmountain::placemmountain(int x, int y)
{
    GetmmountainLoc.x= x;
    GetmmountainLoc.y= y;

    x+=1;
    y+=1;

    mmountainBrk.x =  (unitWidth)*x-1-unitWidth/2;
    mmountainBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




