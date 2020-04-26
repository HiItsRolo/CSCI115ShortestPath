/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef MMOUNTAIN_H
#define MMOUNTAIN_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class mmountain
{
    public:
        mmountain();                            // constructor
        virtual ~mmountain();                   // De constructor
        mmountain(int);                         // overload constructor

            void drawmmountain();               // Draw the Maze mmountain
            void mmountainInit(int, char *);    // initialize the mmountain
            void placemmountain(int, int);      // place the mmountain

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool livemmountain;                 // mmountain status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc mmountainBrk;                 // viewport location of the mmountain
              GLuint mmountainTex;              // mmountain texture handler
              GridLoc GetmmountainLoc;          // Grid Location of the mmountain
};

#endif // mmountain_H
