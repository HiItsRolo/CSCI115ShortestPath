/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef FOREST_H
#define FOREST_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class forest
{
    public:
        forest();                            // constructor
        virtual ~forest();                   // De constructor
        forest(int);                         // overload constructor

            void drawforest();               // Draw the Maze forest
            void forestInit(int, char *);    // initialize the forest
            void placeforest(int, int);      // place the forest

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool liveforest;                 // forest status (broken or not)
            float red,green,blue,alpha;
    protected:

    private:
              loc forestBrk;                 // viewport location of the forest
              GLuint forestTex;              // forest texture handler
              GridLoc GetforestLoc;          // Grid Location of the forest
};

#endif // forest_H
