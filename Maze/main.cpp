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

/* GLUT callback Handlers */

using namespace std;

Maze *M = new Maze(8);                       // Set Maze grid size
Player *P = new Player();                    // create player

wall W[100];                                 // wall with number of bricks
Timer *T0 = new Timer();                     // animation timer

float wWidth, wHeight;                       // display window width and Height
int xPos,yPos;                               // Viewport mapping


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
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    M->generateTerrain();
    M->loadBackgroundImage("images/bak.jpg");           // Load maze background image
    M->loadChestImage("images/chest.png");              // load chest image
    M->placeChest(3,3);                                 // place chest in a grid

    M->loadSetOfArrowsImage("images/arrwset.png");      // load set of arrows image
    M->placeStArrws(5,3);                               // place set of arrows

    P->initPlayer(M->getGridSize(),"images/p.png",6);   // initialize player pass grid size,image and number of frames
    P->loadArrowImage("images/arr.png");                // Load arrow image
    P->placePlayer(6,0);                                // Place player

    for(int i=0; i< M->getGridSize();i++)
    {
      W[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
      W[i].placeWall(i,5);                              // place each brick
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
        }

        glPushMatrix();
            M->drawGrid();              // Draw the grid
        glPopMatrix();

        glPushMatrix();
            P->drawArrow();             // Draw arrow when shoot
        glPopMatrix();

         glPushMatrix();
           M->drawChest();              // Draw chest
        glPopMatrix();

        glPushMatrix();
           M->drawArrows();             // Draw arrows pack
        glPopMatrix();

        glPushMatrix();
             playerActions();           // Draw Player move actions
        glPopMatrix();


    glutSwapBuffers();
}

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

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
             P->shootArrow();           // Shoot (optional )
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

    cout<<"Mouse Click location : "<< xPos<<" "<<yPos <<endl;   // print out grid value
}

 void idle(void)
{
   //Your Code in this section
    if(T0->GetTicks()>300)
      {
        // This is to make sure player move one unit
        // And change direction
        if(P->steps >=P->unitWidth)
          {
            // if player is off the center of grid, place it right
            // This may make you player jumpy a bit
            // you can get rid of this line if your player not messing your path
            P->placePlayer(P->getPlayerLoc().x,P->getPlayerLoc().y);
            P->action = (rand()%4)+1; // your code should plug here
            P->steps =0;
          }

         T0->Reset();
      }
    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
             }
            break;


      case GLUT_RIGHT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
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
    case GLUT_KEY_UP:
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
