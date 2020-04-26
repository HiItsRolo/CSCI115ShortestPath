/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <plain.h>
#include <iostream>

using namespace std;


plain::plain()
{
    //ctor
    liveplain = true;

    red=green=blue=alpha = 1.0;
}

plain::~plain()
{
    //dtor
}

void plain::plainInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    plainTex = TextureLoader(FileName);
}

void plain::drawplain()
{
    if(liveplain)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,plainTex);

    glPushMatrix();
    glTranslatef(plainBrk.x,plainBrk.y,0.0);

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

void plain::placeplain(int x, int y)
{
    GetplainLoc.x= x;
    GetplainLoc.y= y;

    x+=1;
    y+=1;

    plainBrk.x =  (unitWidth)*x-1-unitWidth/2;
    plainBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




