/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef DESERT_H
#define DESERT_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class desert
{
    public:
        desert();                            // constructor
        virtual ~desert();                   // De constructor
        desert(int);                         // overload constructor

            void drawdesert();               // Draw the Maze desert
            void desertInit(int, char *);    // initialize the desert
            void placedesert(int, int);      // place the desert

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool livedesert;                 // desert status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc desertBrk;                 // viewport location of the desert
              GLuint desertTex;              // desert texture handler
              GridLoc GetdesertLoc;          // Grid Location of the desert
};

#endif // desert_H
