#ifndef gh
#define gh

#include <fstream>
#include <iostream>
#include <windows.h>
#include "structsanddefs.h"
#include "functions.h"
using namespace std;


//Functions Prototype

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the game specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

/*A function to draw the 11 floors*/
void DrawFloors();

/* A function that draws an elevator */
void DrawElev(elev &E);

/*A function that draws a passanger */
void DrawPass(pass* P, elev* pE);

/*A function to draw a list of passnegers exist in all regions and ensure there is no overflow in the drawing*/
void DrawPassengers(pass* passes[], int size, elev* pE);

/*Student use this function to print his/her message*/
void PrintMsg(char*msg);

void updateUI(elev *e1,elev *e2,floorx *floors);

void drawqueues(floorx *floors);

void displaystatus(int time, elev* e1, elev* e2,floorx* floors, int numberofdonepass, pass** printlist);
#endif