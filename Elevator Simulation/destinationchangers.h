#ifndef dh
#define dh

#include "functions.h"
#include "structsanddefs.h"

void callelevup (floorx floor, elev *e1, elev *e2);

void callelevdown (floorx floor, elev *e1, elev *e2);

void directelev(elev *e);

void satisfypass(floorx* floors,elev* e1,elev* e2);
#endif