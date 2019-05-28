#ifndef fh
#define fh

#include "structsanddefs.h"
#include "destinationchangers.h"
#include <fstream>
#include <iostream>
#include <windows.h>
using namespace std;




void createfloors(floorx *&floors);

void ReadElevsStatus(float &e1sf, int &e1c, float &e2sf, int &e2c,string filename);

void InitElevStatus(elev *&E1, elev *&E2,string filename);

void enqueuewtglist(pass *addition, pass *&rear, pass *&front,int &qcount);

pass* dequeuewtglist(pass*& front, pass*&rear);

void ReadPassWtgLists(floorx *floors, string filename,int &num);

void addpass(pass*addedpass, elev* e);

bool wtglisttoelev(pass*& front, pass*& rear, elev * e,int currtick);

void elev2prnt(pass** print, int &count, elev *E, int i, int time);

void filterelev(elev *e, int currtick, pass** printlist,int &numberofdonepass);

int updatequeues(floorx *floors,pass** printlist,int &count,int time);

bool passiswtgdown(floorx floor);

bool passiswtgup(floorx floor);

void printoutput(pass**print, int numberofpass);

void moveelev(elev * e, floorx  floor,int time);

void Insertsort(pass* p, pass** print, int &count);

void deletearray(pass **print, int count);

bool passpresent(floorx* floors);

void updateelevdirection(elev* e);

void transpasstoelev(elev* e,floorx &floor,int time);

void updatepasscurrfloor(elev* e);

void emptyi(pass** print,int &count, int empty);

bool passiswaitingforsec(floorx floor, int time);

#endif