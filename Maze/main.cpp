/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>                         //for characters (fish, human, etc)

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <wall.h>
#include <math.h>

#include <beach.h>
#include <desert.h>
#include <foothills.h>
#include <forest.h>
#include <hmountain.h>
#include <mmountain.h>
#include <ocean.h>
#include <plain.h>


#include <bits/stdc++.h>

#include <vector>

/* GLUT callback Handlers */

using namespace std;

const int gridSize = 8;


Maze *M = new Maze(gridSize);                       // Set Maze grid size
Player *P = new Player();                    // create player

wall W[100];                                 // wall with number of bricks

vector<beach>BT;
vector<desert>DT;
vector<foothills>HT;
vector<forest>FT;
vector<hmountain>TT;
vector<mmountain>MT;
vector<ocean>OT;
vector<plain>PT;


wall highlighter[100];

Timer *T0 = new Timer();                     // animation timer

Timer *T1 = new Timer();                     // animation timer


float wWidth, wHeight;                       // display window width and Height
int xPos,yPos;                               // Viewport mapping

string dir[20];
int counter = 0;


int destX, destY;
bool playerSelected = false;


void display(void);                          // Main Display : this runs in a loop
void playerActions();


void resize(int width, int height)           // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_COLOR_MATERIAL);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();
    T1->Start();                                       // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


   // M->generateTerrain();

    M->loadBackgroundImage("images/bak.jpg");           // Load maze background image

    P->initPlayer(M->getGridSize(),"images/p.png",6);   // initialize player pass grid size,image and number of frames
    P->placePlayer(3,0);   // Place player

    cout << HT.size();
    TT.push_back(hmountain());
    TT[0].hmountainInit(M->getGridSize(),"images/mountain.png");
    TT[0].placehmountain(0,0);
    TT.push_back(hmountain());
    TT[1].hmountainInit(M->getGridSize(),"images/mountain.png");
    TT[1].placehmountain(0,1);


    for(int i=0; i< M->getGridSize();i++)
    {
      W[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
      W[i].placeWall(i,5);

      highlighter[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
      highlighter[i].placeWall(-1,-1);

      highlighter[i].red= 1.0;
      highlighter[i].green= 0.0;
      highlighter[i].blue= 0.0;
      highlighter[i].alpha= 0.4;
    }
    W[5].placeWall(0,3);                                // moved 5th brick away
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();           // Display Background
        glPopMatrix();

        for(int i=0; i<M->getGridSize();i++)
        {
           W[i].drawWall();
           highlighter[i].drawWall();
        }

        TT[0].drawhmountain();
        TT[1].drawhmountain();


        glPushMatrix();
            M->drawGrid();              // Draw the grid
        glPopMatrix();

        glPushMatrix();
             P->drawplayer();           // Draw Player move actions
        glPopMatrix();


    glutSwapBuffers();
}

/*
void playerActions()
{
     // Your path code is here
     // here is player moving example
     if(P->action ==1)
     {P->movePlayer("up",6);
    // Sample of how to get player location
    //(remove this after you figure it out)
    // print only when you moving up
   // cout<<"Player Location  :  "<<P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
     }
     else if(P->action ==2)P->movePlayer("down",6);
     else if(P->action ==3)P->movePlayer("left",6);
     else if(P->action ==4)P->movePlayer("right",6);
     else P->movePlayer("stand",6);
}
*/

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
          //   P->shootArrow();           // Shoot (optional )
        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}


 void GetOGLPos(int x, int y)          // Mouse map coordinates
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    xPos =(int) (posX *M->getGridSize()/2 +M->getGridSize()/2); // update mouse position X
    yPos =(int) (posY *M->getGridSize()/2 +M->getGridSize()/2);

   // cout<<"Mouse Click location : "<< xPos<<" "<<yPos <<endl;   // print out grid value
}

void movePlayer(Player* character, string direction, int frames){

   char* buffer = new char[direction.length()];


   strcpy(buffer,direction.c_str());

    if(character->steps > character->unitWidth){
        character->steps =0;
        strcpy(buffer,"stand");
        character->placePlayer(character->getPlayerLoc().x,character->getPlayerLoc().y);
        if(T1->GetTicks()>500){
            counter++;
            T1->Reset();
        }
    }
    else{
        if(character->activePlayer){
            character->movePlayer(buffer,frames);
        }
        delete []buffer;
    }
}

 void idle(void)
{
   //Your Code in this section
    if(T0->GetTicks()>30 && counter<8)
      {




         movePlayer(P,dir[counter],6);//check for active is inside movePlayer function. add here instead

         T0->Reset();
      }
    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON: // left mouse button for picking player

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);

              if (xPos == P->getPlayerLoc().x && yPos == P->getPlayerLoc().y){
                P->activePlayer = true;
                playerSelected = true;
                //set all other players to false
              }

             }
            break;


      case GLUT_RIGHT_BUTTON: // right mouse button for picking destination

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);

              if(playerSelected){
                destX = xPos;
                destY = yPos;

                highlighter[0].placeWall(7,0);
                highlighter[1].placeWall(8,0);

                dir[0] = "up";// algorithm called here. Should genereate these steps
                dir[1] = "up";
                dir[2] = "up";
                dir[3] = "right";
                dir[4] = "right";
                dir[5] = "down";
                dir[6] = "left";

                counter = 0;


                playerSelected = false;
              }

            }
            break;
    }
     glutPostRedisplay();
};

void Specialkeys(int key, int x, int y)
{
     cout<<"Player Location  :  "<<P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
    switch(key)
    {
 /*   case GLUT_KEY_UP:
        P->action =1;
         break;

    case GLUT_KEY_DOWN:
        P->action =2;
         break;

    case GLUT_KEY_LEFT:
        P->action =3;
         break;

    case GLUT_KEY_RIGHT:
        P->action =4;
         break;
   */
   }
   // comment this after you debug


  glutPostRedisplay();

}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}
