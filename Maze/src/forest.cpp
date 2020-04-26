/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <forest.h>
#include <iostream>

using namespace std;


forest::forest()
{
    //ctor
    liveforest = true;

    red=green=blue=alpha = 1.0;
}

forest::~forest()
{
    //dtor
}

void forest::forestInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    forestTex = TextureLoader(FileName);
}

void forest::drawforest()
{
    if(liveforest)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,forestTex);

    glPushMatrix();
    glTranslatef(forestBrk.x,forestBrk.y,0.0);

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

void forest::placeforest(int x, int y)
{
    GetforestLoc.x= x;
    GetforestLoc.y= y;

    x+=1;
    y+=1;

    forestBrk.x =  (unitWidth)*x-1-unitWidth/2;
    forestBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




