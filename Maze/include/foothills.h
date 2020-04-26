/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef FOOTHILLS_H
#define FOOTHILLS_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class foothills
{
    public:
        foothills();                            // constructor
        virtual ~foothills();                   // De constructor
        foothills(int);                         // overload constructor

            void drawfoothills();               // Draw the Maze foothills
            void foothillsInit(int, char *);    // initialize the foothills
            void placefoothills(int, int);      // place the foothills

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool livefoothills;                 // foothills status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc foothillsBrk;                 // viewport location of the foothills
              GLuint foothillsTex;              // foothills texture handler
              GridLoc GetfoothillsLoc;          // Grid Location of the foothills
};

#endif // foothills_H
