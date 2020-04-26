/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef HMOUNTAIN_H
#define HMOUNTAIN_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class hmountain
{
    public:
        hmountain();                            // constructor
        virtual ~hmountain();                   // De constructor
        hmountain(int);                         // overload constructor

            void drawhmountain();               // Draw the Maze hmountain
            void hmountainInit(int, char *);    // initialize the hmountain
            void placehmountain(int, int);      // place the hmountain

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool livehmountain;                 // hmountain status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc hmountainBrk;                 // viewport location of the hmountain
              GLuint hmountainTex;              // hmountain texture handler
              GridLoc GethmountainLoc;          // Grid Location of the hmountain
};

#endif // HMOUNTAIN_H
