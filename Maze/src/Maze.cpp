/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <Maze.h>
#include <fstream>
#include <vector>
Maze::Maze()
{

}

Maze::Maze(int gSize)                                        // Constructor
{
    //ctor
    gridSize = gSize;
    unitWidth = (float)2/gridSize;

}

Maze::~Maze()
{
    //dtor
}


void Maze::loadBackgroundImage(char* FileName)
{
   bakTex = TextureLoader(FileName);
}



int Maze::getGridSize()
{
  return gridSize;
}


void Maze::drawBackground()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,bakTex);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}


void Maze::drawGrid()
{
   float a;
   glColor4f(1.0,1.0,1.0,0.2);
   glDisable(GL_TEXTURE_2D);
   glPointSize(1);
   glBegin(GL_LINES);

   for(int i =0;i<gridSize;i++)
    {
         a = -1+(float)unitWidth*i;
         glVertex3f(a,1,-0.4);
         glVertex3f(a,-1,-0.4);
         glVertex3f(-1,a,0.4);
         glVertex3f(1,a,0.4);
    }
    glEnd();
    glEnable(GL_TEXTURE_2D);
}


loc Maze::converter(int x, int y)
{
       loc val;

        x+=1;
        y+=1;
       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}


void Maze::diamondStep(vector<vector<int>>& Array, int x, int y, int i, int j, int step) //diamond step of midpoint displacement
{
    int count = 0; //count of how many values are being averaged
    int average = 0;
    if ((i - step >= 0) && (j - step >= 0)) // checks if bottom-left corner exists
    {
        average += Array[i - step][j - step];
        count++;
    }
    if ((i - step >= 0) && (j + step < y)) // checks if top-left corner exists
    {
        average += Array[i - step][j + step];
        count++;
    }
    if ((i + step < x) && (j - step >= 0)) // checks if bottom-right corner exists
    {
        average += Array[i + step][j - step];
        count++;
    }
    if ((i + step < x) && (j + step < y)) // checks if top-right corner exists
    {
        average += Array[i + step][j + step];
        count++;
    }
    average = average / count;
    average += rand() % step; // add a small random value as an offset
    Array[i][j] = average ;
}

void Maze::squareStep(vector<vector<int>> &Array, int x, int y, int i, int j, int step) //square step of midpoint displacement
{
    int count = 0;
    int average = 0;
    if (i - step >= 0) // checks if element is being inserted into left-edge
    {
        average += Array[i - step][j];
        count++;
    }
    if (i + step < x) // checks if element is being inserted into right-edge
    {
        average += Array[i + step][j];
        count++;
    }
    if (j - step >= 0) // checks if element is being inserted into bottom-edge
    {
        average += Array[i][j - step];
        count++;
    }
    if (j + step < y) // checks if element is being inserted into top-edge
    {
        average += Array[i][j + step];
        count++;
    }
    average = average / count;
    average += rand() % step; // adds a small offset
   Array[i][j] = average;

}


void Maze::mdp(vector<vector<int>> &arr, int x, int y, int bound) { //mdp is the midpoint displacement function


    int mid = bound / 2; // value halfway from the top-bounding index.
    if (mid >= 1) {//midpoint displacement requires at least a 2x2 array
        for (int j = mid; j < y; j += bound) {
            for (int i = mid; i < x; i += bound) { //for loops setting the index of the point to be found using the diamond step

                diamondStep(arr, x, y, i, j, mid);

            }
        }

        int iter = 1; // checks which iteration of squareStep we are on

        for (int i = 0; i < x; i += mid) {
            if (iter % 2 == 1) { // if on odd iteration
                for (int j = mid; j < y; j += bound) {
                    squareStep(arr, x, y, i, j, mid); // squareStep is being performed on values west and east of midpoint value
                }
            }

            else {
                for (int j = 0; j < y; j += bound) {
                    squareStep(arr, x, y, i, j, mid);  // squareStep is being performed on values south and north of midpoint value
                }
            }
            iter++;
        }
          mdp(arr, x, y, bound/ 2);//recursive call to mdp, with the bounding index cut in half to perform algorithm on subgrid.
    }
}

void Maze::generateTerrain() { //function to procedurally generate terrain using diamond-square algorithm
    int n = 1;
    int i = (2 ^ n) + 1;
    while (i < getGridSize()) { //finds an i-value that fits the form 2^n + 1.
        n++;
        i = pow(2,n) + 1;
    }

// note: Diamond-Square (midpoint displacement) requires the form 2^n + 1.

    vector<vector<int>> temp(i, vector<int>(i, 0)); // temporary 2-D vector to hold values generated.
    int bound = i - 1; //vector's indexes will be from 0 : i-1

    temp[0][0] = rand() % 120; // assign random value to first corner (0,0)
    temp[0][bound] = rand() % 120; // assign random value to second corner (0,i-1)
    temp[bound][0] = rand() % 120; // assign random value to third corner (i-1,0)
    temp[bound][bound] = rand() % 120; // assign random value to fourth corner (i-1,i-1)

    // using these four corners as seed values, the function mdp will procedurally generate values.

    mdp(temp, i, i, bound);

    ofstream myfile;
    myfile.open("terrain.txt"); //opens (or creates) a text file to store the generated terrain

    for (int q = 0; q < i; q++) {
        for (int r = 0; r < i; r++) { // distributes the generated values into the range for their elements
            int check = temp[q][r] / 15; //120 possible values, 8 possible terrain elements.
            if (check == 0) {
                myfile << "O"; //Ocean
            }
            else if (check == 1){
                myfile << "B"; //Beach
            }
            else if (check == 2){
                myfile << "D"; //Desert
            }
            else if (check == 3){
                myfile << "F"; //Forest
            }
            else if (check == 4){
                myfile << "P"; //Plain
            }
            else if (check == 5){
                myfile << "H"; //Foothills
            }
            else if (check == 6){
                myfile << "M"; //Middle Mountain
            }
            else {
                myfile << "T"; //High Mountain
            }

            cout << "(" << q << "," << r << ")" << temp[q][r] << endl; // for debugging purposes
        }
        myfile << "\n"; // creates a new line after each column value for that row has been written
    }
    myfile.close();

}

