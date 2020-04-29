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

#include <fstream>


#include <bits/stdc++.h>

#include <vector>

/* GLUT callback Handlers */

using namespace std;

const int num = 17;
Maze *M = new Maze(num);                       // Set Maze grid size
Player *P = new Player();                    // create player

char level[num][num];

//vector <wall> W;                                 // wall
vector<beach>BT;                             //beach array for graphics
vector<desert>DT;                            //desert array for graphics
vector<foothills>HT;                        //foothills array for graphics
vector<forest>FT;                           //forest array for graphics
vector<hmountain>TT;                        //high mountain array for graphics
vector<mmountain>MT;                        //mid mountain array for graphics
vector<ocean>OT;                            //ocean array for graphics
vector<plain>PT;                            //plain array for graphics


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


    M->generateTerrain();

    M->loadBackgroundImage("images/bak.jpg");           // Load maze background image

    P->initPlayer(M->getGridSize(),"images/p.png",6);   // initialize player pass grid size,image and number of frames
    P->placePlayer(3,0);   // Place player


    for(int i = 0; i < 1; i++){ //loads level from text file and will add graphics according to characters in text file
        int y = M->getGridSize()-1; //start at top left (y = gridsize-1)
        //int Wcount = 0;
        int BTcount = 0;
        int DTcount = 0;
        int HTcount = 0;
        int FTcount = 0;
        int TTcount = 0;
        int MTcount = 0;
        int OTcount = 0;
        int PTcount = 0;
        ifstream read;
        read.open("terrain.txt");
        string line;
        while (getline(read,line)){
            int x = 0;
            for(char c : line){

                level[x][y] = c;

                if (c == 'O'){
          /*          W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/ocean.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    OT.push_back(ocean());
                    OT[OTcount].oceanInit(M->getGridSize(),"images/ocean.png");
                    OT[OTcount].placeocean(x,y);
                    OTcount++;
                }

                if (c == 'B'){
/*                    W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/beach.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    BT.push_back(beach());
                    BT[BTcount].beachInit(M->getGridSize(),"images/beach.png");
                    BT[BTcount].placebeach(x,y);
                    BTcount++;
                    level[x][y]='B';
                }

                if (c == 'D'){
/*                    W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/desert.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    DT.push_back(desert());
                    DT[DTcount].desertInit(M->getGridSize(),"images/desert.png");
                    DT[DTcount].placedesert(x,y);
                    DTcount++;
                }

                if (c == 'F'){
/*                    W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/forest.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    FT.push_back(forest());
                    FT[FTcount].forestInit(M->getGridSize(),"images/forest.png");
                    FT[FTcount].placeforest(x,y);
                    FTcount++;
                }

                if (c == 'P'){
/*                   W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/plains.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    PT.push_back(plain());
                    PT[PTcount].plainInit(M->getGridSize(),"images/plains.png");
                    PT[PTcount].placeplain(x,y);
                    PTcount++;
                }
                if (c == 'H'){
/*                    W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/foothills.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    HT.push_back(foothills());
                    HT[HTcount].foothillsInit(M->getGridSize(),"images/foothills.png");
                    HT[HTcount].placefoothills(x,y);
                    HTcount++;
                }
                if (c == 'M'){
/*                    W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/mountain.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    MT.push_back(mmountain());
                    MT[MTcount].mmountainInit(M->getGridSize(),"images/mountain.png");
                    MT[MTcount].placemmountain(x,y);
                    MTcount++;
                }
                if (c == 'T'){
/*                    W.push_back(wall());
                    W[Wcount].wallInit(M->getGridSize(),"images/mountainpeak.png");
                    W[Wcount].placeWall(x,y);
                    Wcount++;*/
                    TT.push_back(hmountain());
                    TT[TTcount].hmountainInit(M->getGridSize(),"images/mountainpeak.png");
                    TT[TTcount].placehmountain(x,y);
                    TTcount++;
                }
                x++;

            }
            y--;
        }
    }


/*)
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
*/
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();           // Display Background
        glPopMatrix();

        /*for(int i=0; i<M->getGridSize();i++)
        {
           W[i].drawWall();
           highlighter[i].drawWall();
        }*/

/*        for(int i=0; i< W.size(); i++){
            W[i].drawWall();
        }*/

        for(int i=0;i< OT.size();i++){
            OT[i].drawocean();           //display ocean tiles
        }

        for(int i=0;i< BT.size();i++){
            BT[i].drawbeach();          //display beach tiles
        }

        for(int i=0;i< DT.size();i++){
            DT[i].drawdesert();         //display desert tiles
        }

        for(int i=0;i< FT.size();i++){
            FT[i].drawforest();         //display forest tiles
        }

        for(int i=0;i< PT.size();i++){
            PT[i].drawplain();          //display plain tiles
        }

        for(int i=0;i< HT.size();i++){
            HT[i].drawfoothills();      //display foothills tiles
        }

        for(int i=0;i< MT.size();i++){
            MT[i].drawmmountain();      //display mid mountain tiles
        }

        for(int i=0;i< TT.size();i++){
            TT[i].drawhmountain();      //display high mountain tiles
        }



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
