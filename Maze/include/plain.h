/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef PLAIN_H
#define PLAIN_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class plain
{
    public:
        plain();                            // constructor
        virtual ~plain();                   // De constructor
        plain(int);                         // overload constructor

            void drawplain();               // Draw the Maze plain
            void plainInit(int, char *);    // initialize the plain
            void placeplain(int, int);      // place the plain

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool liveplain;                 // plain status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc plainBrk;                 // viewport location of the plain
              GLuint plainTex;              // plain texture handler
              GridLoc GetplainLoc;          // Grid Location of the plain
};

#endif // plain_H
