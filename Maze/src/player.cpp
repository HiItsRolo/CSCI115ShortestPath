/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Player.h>



Player::Player()
{
    //ctor
    playerDir = "up";
    action= 0;
    activePlayer = false;
}

Player::~Player()
{
    //dtor
}

void Player::drawPlayer()
{

    glColor3f(1.0,1.0,1.0);

    glTranslatef(plyLoc.x ,plyLoc.y,0.0);

    glBindTexture(GL_TEXTURE_2D,plyTex);
    glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);


    glBegin(GL_QUADS);
        glTexCoord2f(xmin,ymin);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(xmax,ymin);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(xmax,ymax);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(xmin,ymax);
        glVertex3f(1,-1,0.0f);
     glEnd();

}


void Player::initPlayer(int gSize,char *FileName,int frms)
{
    gridSize = gSize;
    frames = frms;

    xmax =1/(float)frames;
    ymax =0.25;
    xmin =0;
    ymin =0;

    unitWidth = (float)2/gridSize;
    stepsPerMove =frames;

    T->Start();
    plyLoc.x= -unitWidth;
    plyLoc.y= -unitWidth;

    t= unitWidth/stepsPerMove;
    steps =0;
    plyTex = TextureLoader(FileName);
}

void Player::placePlayer(int x, int y)
{
    plyLoc.x =  converter(x,y).x;
    plyLoc.y =  converter(x,y).y;
}

void Player::movePlayer(char* dir, int frames)
{
   /*
   if(steps >= unitWidth) {
   placePlayer(getPlayerLoc().x,getPlayerLoc().y);
   steps =0;
   }
   */

  if(strcmp(dir, "left")==0)
   {   playerDir = "left";

       if(T->GetTicks()>100)
        {   steps +=t;
            if(plyLoc.x>-1+unitWidth/2)
              {
                 steps<unitWidth? plyLoc.x -= t:NULL;
              }
            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin += 1/(float)frames;
            xmax += 1/(float)frames;
            ymin =0.75;
            ymax =1.0;
            T->Reset();
          }  // end if
       }

   else if(strcmp(dir, "right")==0)
   {
        playerDir = "right";

        if(T->GetTicks()>100)
        {
            steps +=t;
            if(plyLoc.x<1-unitWidth/2)
            steps<unitWidth?plyLoc.x += t:NULL;

            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.5;
            ymax =0.75;
            T->Reset();
        }  // end if
   }


   else if(strcmp(dir, "up")==0)
   {
        playerDir = "up";

        if(T->GetTicks()>100)
        {
            steps +=t;
            if(plyLoc.y< 1-unitWidth/2)
            steps<unitWidth?plyLoc.y += t:NULL;

            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;

            ymin =0.25;
            ymax =0.50;
            T->Reset();
         }  // end if

    }

   else if(strcmp(dir, "down")==0)
   {
         playerDir = "down";

        if(T->GetTicks()>100)
        {
            steps +=t;
            if(plyLoc.y > -1+unitWidth/2)
                steps<unitWidth?plyLoc.y -= t:NULL;
            if(xmax>=1){
                xmax =1/(float)frames;
                xmin =0;
            }
            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.0;
            ymax =0.25;
            T->Reset();
        }  // end if

     }

}

GridLoc Player::getPlayerLoc()
{
   GridLoc val;

   val.x = (int)(ceil((plyLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((plyLoc.y +(1-unitWidth))/unitWidth));

   return val;

}

loc Player::converter(int x, int y)
{
  loc val;
        x+=1;
        y+=1;

       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}


int Player::Dmat(char a, char b, string character) {    //INEFFICIENT, IMPLEMENT HASH TABLE           //return the distance between two terrains
    if (character == "Human"){ //cost for human
        if (a == 'T') {
            if (b == 'T') { //distance between high mountain and high mountain
                return 1000; //human cannot travel reach high mountains so travel to and from is prohibited
            }
            else if (b == 'M') { // distance between high mountain and mid mountain
                return 1000;
            }
            else if (b == 'H') { // distance between high mountain and foothills
                return 1000;
            }
            else if (b == 'P') { // distance between high mountain and plains
                return 1000;
            }
            else if (b == 'F') { // distance between high mountain and forest
                return 1000;
            }
            else if (b == 'D') { // distance between high mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between high mountain and beach
                return 1000;
            }
            else if (b == 'O') { // distance between high mountain and ocean
                return 1000;
            }
        }
        else if (a == 'M') {
            if(b == 'T') { // distance between mid mountain and high mountain
                return 1000;
            }
            else if (b == 'M') { // distance between mid mountain and mid mountain
                return 4;
            }
            else if (b == 'H') { // distance between mid mountain and foothills
                return 2;
            }
            else if (b == 'P') { // distance between mid mountain and plains
                return 3;
            }
            else if (b == 'F') { // distance between mid mountain and forest
                return 4;
            }
            else if (b == 'D') { // distance between mid mountain and desert
                return 5;
            }
            else if (b == 'B') { // distance between mid mountain and beach
                return 5;
            }
            else if (b == 'O') { // distance between mid mountain and ocean
                return 1000;
            }
        }
        else if (a == 'H') {
            if(b == 'T') { // distance between foothills and high mountain
                return 1000;
            }
            else if (b == 'M') {
                return 5;
            }
            else if (b == 'H') {
                return 2;
            }
            else if (b == 'P') {
                return 3;
            }
            else if (b == 'F') {
                return 4;
            }
            else if (b == 'D') {
                return 2;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'P') {
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 6;
            }
            else if (b == 'H') {
                return 3;
            }
            else if (b == 'P') {
                return 1;
            }
            else if (b == 'F') {
                return 2;
            }
            else if (b == 'D') {
                return 2;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'F') {
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 8;
            }
            else if (b == 'H') {
                return 3;
            }
            else if (b == 'P') {
                return 1;
            }
            else if (b == 'F') {
                return 2;
            }
            else if (b == 'D') {
                return 1;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'D'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 9;
            }
            else if (b == 'H') {
                return 2;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 2;
            }
            else if (b == 'D') {
                return 2;
            }
            else if (b == 'B') {
                return 1;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'B'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 15;
            }
            else if (b == 'H') {
                return 15;
            }
            else if (b == 'P') {
                return 3;
            }
            else if (b == 'F') {
                return 7;
            }
            else if (b == 'D') {
                return 4;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'O'){
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        return 1000; //no match was found
    }

    else if (character == "Fish"){ //cost for fish
        if (a == 'T') {
            if (b == 'T') { //distance between high mountain and high mountain
                return 1000; //human cannot travel reach high mountains so travel to and from is prohibited
            }
            else if (b == 'M') { // distance between high mountain and mid mountain
                return 1000;
            }
            else if (b == 'H') { // distance between high mountain and foothills
                return 1000;
            }
            else if (b == 'P') { // distance between high mountain and plains
                return 1000;
            }
            else if (b == 'F') { // distance between high mountain and forest
                return 1000;
            }
            else if (b == 'D') { // distance between high mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between high mountain and beach
                return 1000;
            }
            else if (b == 'O') { // distance between high mountain and ocean
                return 1000;
            }
        }
        else if (a == 'M') {
            if(b == 'T') { // distance between mid mountain and high mountain
                return 1000;
            }
            else if (b == 'M') { // distance between mid mountain and mid mountain
                return 1000;
            }
            else if (b == 'H') { // distance between mid mountain and foothills
                return 1000;
            }
            else if (b == 'P') { // distance between mid mountain and plains
                return 1000;
            }
            else if (b == 'F') { // distance between mid mountain and forest
                return 1000;
            }
            else if (b == 'D') { // distance between mid mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between mid mountain and beach
                return 1000;
            }
            else if (b == 'O') { // distance between mid mountain and ocean
                return 1000;
            }
        }
        else if (a == 'H') {
            if(b == 'T') { // distance between foothills and high mountain
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'P') {
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'F') {
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'D'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'B'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'O'){
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 1;
            }
        }
        return 1000; //if no matching was found
    }

    else if (character == "Frog"){ // cost for frog
        if (a == 'T') {
            if (b == 'T') { //distance between high mountain and high mountain
                return 1000; //human cannot travel reach high mountains so travel to and from is prohibited
            }
            else if (b == 'M') { // distance between high mountain and mid mountain
                return 1000;
            }
            else if (b == 'H') { // distance between high mountain and foothills
                return 1000;
            }
            else if (b == 'P') { // distance between high mountain and plains
                return 1000;
            }
            else if (b == 'F') { // distance between high mountain and forest
                return 1000;
            }
            else if (b == 'D') { // distance between high mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between high mountain and beach
                return 1000;
            }
            else if (b == 'O') { // distance between high mountain and ocean
                return 1000;
            }
        }
        else if (a == 'M') {
            if(b == 'T') { // distance between mid mountain and high mountain
                return 1000;
            }
            else if (b == 'M') { // distance between mid mountain and mid mountain
                return 1000;
            }
            else if (b == 'H') { // distance between mid mountain and foothills
                return 1000;
            }
            else if (b == 'P') { // distance between mid mountain and plains
                return 1000;
            }
            else if (b == 'F') { // distance between mid mountain and forest
                return 1000;
            }
            else if (b == 'D') { // distance between mid mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between mid mountain and beach
                return 1000;
            }
            else if (b == 'O') { // distance between mid mountain and ocean
                return 1000;
            }
        }
        else if (a == 'H') {
            if(b == 'T') { // distance between foothills and high mountain
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 3;
            }
            else if (b == 'P') {
                return 3;
            }
            else if (b == 'F') {
                return 4;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 4;
            }
        }
        else if (a == 'P') {
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 2;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 2;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 3;
            }
        }
        else if (a == 'F') {
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 3;
            }
            else if (b == 'P') {
                return 3;
            }
            else if (b == 'F') {
                return 3;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 3;
            }
        }
        else if (a == 'D'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'B'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 4;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 2;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1;
            }
            else if (b == 'O') {
                return 1;
            }
        }
        else if (a == 'O'){
            if (b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 4;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 4;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1;
            }
            else if (b == 'O') {
                return 2;
            }
        }
        return 1000;
    }

    else if (character == "Bird"){ //cost for bird
       if (a == 'T') {
            if (b == 'T') { //distance between high mountain and high mountain
                return 2; //human cannot travel reach high mountains so travel to and from is prohibited
            }
            else if (b == 'M') { // distance between high mountain and mid mountain
                return 1;
            }
            else if (b == 'H') { // distance between high mountain and foothills
                return 2;
            }
            else if (b == 'P') { // distance between high mountain and plains
                return 2;
            }
            else if (b == 'F') { // distance between high mountain and forest
                return 4;
            }
            else if (b == 'D') { // distance between high mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between high mountain and beach
                return 4;
            }
            else if (b == 'O') { // distance between high mountain and ocean
                return 5;
            }
        }
        else if (a == 'M') {
            if(b == 'T') { // distance between mid mountain and high mountain
                return 3;
            }
            else if (b == 'M') { // distance between mid mountain and mid mountain
                return 2;
            }
            else if (b == 'H') { // distance between mid mountain and foothills
                return 3;
            }
            else if (b == 'P') { // distance between mid mountain and plains
                return 4;
            }
            else if (b == 'F') { // distance between mid mountain and forest
                return 4;
            }
            else if (b == 'D') { // distance between mid mountain and desert
                return 1000;
            }
            else if (b == 'B') { // distance between mid mountain and beach
                return 5;
            }
            else if (b == 'O') { // distance between mid mountain and ocean
                return 5;
            }
        }
        else if (a == 'H') {
            if(b == 'T') { // distance between foothills and high mountain
                return 3;
            }
            else if (b == 'M') {
                return 1;
            }
            else if (b == 'H') {
                return 2;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 3;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 4;
            }
        }
        else if (a == 'P') {
            if (b == 'T') {
                return 2;
            }
            else if (b == 'M') {
                return 3;
            }
            else if (b == 'H') {
                return 2;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 3;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 3;
            }
        }
        else if (a == 'F') {
            if (b == 'T') {
                return 3;
            }
            else if (b == 'M') {
                return 4;
            }
            else if (b == 'H') {
                return 3;
            }
            else if (b == 'P') {
                return 3;
            }
            else if (b == 'F') {
                return 3;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 3;
            }
            else if (b == 'O') {
                return 3;
            }
        }
        else if (a == 'D'){
            if(b == 'T') {
                return 1000;
            }
            else if (b == 'M') {
                return 1000;
            }
            else if (b == 'H') {
                return 1000;
            }
            else if (b == 'P') {
                return 1000;
            }
            else if (b == 'F') {
                return 1000;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 1000;
            }
            else if (b == 'O') {
                return 1000;
            }
        }
        else if (a == 'B'){
            if(b == 'T') {
                return 5;
            }
            else if (b == 'M') {
                return 4;
            }
            else if (b == 'H') {
                return 3;
            }
            else if (b == 'P') {
                return 3;
            }
            else if (b == 'F') {
                return 2;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 2;
            }
        }
        else if (a == 'O'){
            if (b == 'T') {
                return 7;
            }
            else if (b == 'M') {
                return 7;
            }
            else if (b == 'H') {
                return 4;
            }
            else if (b == 'P') {
                return 2;
            }
            else if (b == 'F') {
                return 3;
            }
            else if (b == 'D') {
                return 1000;
            }
            else if (b == 'B') {
                return 2;
            }
            else if (b == 'O') {
                return 2;
            }
        }
        return 1000;
    }

}
