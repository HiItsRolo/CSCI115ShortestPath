/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <foothills.h>
#include <iostream>

using namespace std;


foothills::foothills()
{
    //ctor
    livefoothills = true;

    red=green=blue=alpha = 1.0;
}

foothills::~foothills()
{
    //dtor
}

void foothills::foothillsInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    foothillsTex = TextureLoader(FileName);
}

void foothills::drawfoothills()
{
    if(livefoothills)
    {

    glColor4f(red,green,blue,alpha);
    glBindTexture(GL_TEXTURE_2D,foothillsTex);

    glPushMatrix();
    glTranslatef(foothillsBrk.x,foothillsBrk.y,0.0);

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

void foothills::placefoothills(int x, int y)
{
    GetfoothillsLoc.x= x;
    GetfoothillsLoc.y= y;

    x+=1;
    y+=1;

    foothillsBrk.x =  (unitWidth)*x-1-unitWidth/2;
    foothillsBrk.y =  (unitWidth)*y-1-unitWidth/2;
}




