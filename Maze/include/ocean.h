/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef OCEAN_H
#define OCEAN_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class ocean
{
    public:
        ocean();                            // constructor
        virtual ~ocean();                   // De constructor
        ocean(int);                         // overload constructor

            void drawocean();               // Draw the Maze ocean
            void oceanInit(int, char *);    // initialize the ocean
            void placeocean(int, int);      // place the ocean

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool liveocean;                 // ocean status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc oceanBrk;                 // viewport location of the ocean
              GLuint oceanTex;              // ocean texture handler
              GridLoc GetoceanLoc;          // Grid Location of the ocean
};

#endif // ocean_H
