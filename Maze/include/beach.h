/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef BEACH_H
#define BEACH_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class beach
{
    public:
        beach();                            // constructor
        virtual ~beach();                   // De constructor
        beach(int);                         // overload constructor

            void drawbeach();               // Draw the Maze beach
            void beachInit(int, char *);    // initialize the beach
            void placebeach(int, int);      // place the beach

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool livebeach;                 // beach status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc beachBrk;                 // viewport location of the beach
              GLuint beachTex;              // beach texture handler
              GridLoc GetbeachLoc;          // Grid Location of the beach
};

#endif // beach_H
