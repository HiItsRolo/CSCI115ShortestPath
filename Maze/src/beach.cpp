/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <beach.h>
#include <iostream>

using namespace std;


beach::beach()
{
    //ctor
    livebeach = true;

    red=green=blue=alpha = 1.0;
}

beach::~beach()
{
    //dtor
}

void beach::beachInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    beachTex = TextureLoader(FileName);
}

void beach::drawbeach()
{
    if(livebeach)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,beachTex);

    glPushMatrix();
    glTranslatef(beachBrk.x,beachBrk.y,0.0);

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

void beach::placebeach(int x, int y)
{
    GetbeachLoc.x= x;
    GetbeachLoc.y= y;

    x+=1;
    y+=1;

    beachBrk.x =  (unitWidth)*x-1-unitWidth/2;
    beachBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




