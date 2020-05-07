/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef MAZE_H
#define MAZE_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */
#include <vector>


class Maze
{
    public:
        Maze();                           // Constructor
        Maze(int);                        // Overload Constructor
        virtual ~Maze();                  // Deconstructor

      void loadBackgroundImage(char *);   // set an image for the background

      void drawBackground();              // Draw background image
      void drawGrid();                    // Draw Grid

      int getGridSize();                  // return grid size

      void generateTerrain();               //generates terrain using Diamond-Square algorithm (requires 2^n +1)

    protected:

      int gridSize;                       // grid size
      float unitWidth;                    // Unit width of the grid


    private:


    void squareStep(vector<vector<int>>&,int,int,int,int,int); //square step. Parameters are grid vector, x bound, y bound, x index being generated, y index being generated, step
    void diamondStep(vector<vector<int>>&,int,int,int,int,int); //diamond step. Parameters are same as squarestep
    void mdp(vector<vector<int>>&,int,int,int); //recursively calls midpoint algorithm. Parameters are: vector of grid, top of x bound (gridsize), top of y bound (gridsize), step

      GLuint bakTex;                       // Handler for background texture

      loc converter(int, int);             // convert grid size to viewport
};

#endif // MAZE_H
