/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <ocean.h>
#include <iostream>

using namespace std;


ocean::ocean()
{
    //ctor
    liveocean = true;

    red=green=blue=alpha = 1.0;
}

ocean::~ocean()
{
    //dtor
}

void ocean::oceanInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    oceanTex = TextureLoader(FileName);
}

void ocean::drawocean()
{
    if(liveocean)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,oceanTex);

    glPushMatrix();
    glTranslatef(oceanBrk.x,oceanBrk.y,0.0);

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

void ocean::placeocean(int x, int y)
{
    GetoceanLoc.x= x;
    GetoceanLoc.y= y;

    x+=1;
    y+=1;

    oceanBrk.x =  (unitWidth)*x-1-unitWidth/2;
    oceanBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




