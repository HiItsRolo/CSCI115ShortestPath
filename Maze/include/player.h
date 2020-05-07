/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */
#include <string>



using namespace std;

class Player
{
    public:
        Player();                          // Constructor
        virtual ~Player();                 // Deconstructor

        void drawPlayer();                 // Draw Player image

        void initPlayer(int, char *,int);  // initialize the player with grid size, image, frames
        void placePlayer(int,int);         // place the player
        void movePlayer(char *,int);       // move Player left,right,up,down


        GridLoc getPlayerLoc();            // player current location

        float steps;                       // steps to reach next square

        float unitWidth;                   // Unit width of the grid

        int frames;                        // Number of frames for animation
        char *playerDir;                   // direction of player face
        int action;                        // What action player do
        bool activePlayer;                 // Player is selected

        int Dmat(char a, char b, string character); //returns the value of the edge depending on the character string passed in. (Human, Fish, Bird, Frog will all have different values)

        Timer *T = new Timer();            // Set Timer for animation

    protected:

        float t;                           // Ticker for animation
        void timer();                      // Timer for animation
        int gridSize;                      // Grid Size

    private:

    private:
        float xmax, xmin,ymax,ymin;        // animation texture map
        GLuint plyTex;                     // player image handler
        int arrXdir;                       // arrow direction x;
        int arrYdir;                       // arrow direction y
        float arrAngle;                    // animation direction of the arrow
        loc plyLoc;                        // viewport location of the player
        loc converter(int, int);           // convert Grid location to viewport
        int stepsPerMove;                  // animation steps

};

#endif // PLAYER_H
