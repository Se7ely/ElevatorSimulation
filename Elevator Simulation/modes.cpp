#include "modes.h"

void InteractiveMode()
{
	string filename="input.txt";
	floorx *floors=NULL;
	createfloors(floors);
	elev *e1=NULL, *e2=NULL;
	InitElevStatus(e1,e2,filename);
	int numberofpass=0;
	int numberofdonepass=0;
	ReadPassWtgLists(floors,filename,numberofpass);
	pass** printlist=new pass*[numberofpass];
	int time=0;
	while(passpresent(floors)||e1->PassCnt||e2->PassCnt)
	{
		
		time++;
		//pass pick up and drop off
		if(updatequeues(floors,printlist,numberofdonepass,time))
		{
			satisfypass(floors,e1,e2);
			moveelev(e1,floors[e1->floor],time);
			moveelev(e2,floors[e2->floor],time);
			updateelevdirection(e1);
			updateelevdirection(e2);
			updatepasscurrfloor(e1);
			updatepasscurrfloor(e2);
			filterelev(e1,time,printlist,numberofdonepass);
			filterelev(e2,time,printlist,numberofdonepass);
			transpasstoelev(e1,floors[e1->floor],time);
			transpasstoelev(e2,floors[e2->floor],time);	
		}
		//pass drop off
		else
		{
			moveelev(e1,floors[e1->floor],time);
			moveelev(e2,floors[e2->floor],time);
			updateelevdirection(e1);
			updateelevdirection(e2);
			updatepasscurrfloor(e1);
			updatepasscurrfloor(e2);
			filterelev(e1,time,printlist,numberofdonepass);
			filterelev(e2,time,printlist,numberofdonepass);
		}
		updateUI(e1,e2,floors);
		displaystatus(time,e1,e2,floors,numberofdonepass,printlist);
		Sleep(1000);
	}
	printoutput(printlist,numberofdonepass);
	deletearray(printlist,numberofdonepass);
	delete []floors;
	delete e1;
	delete e2;
	floors=NULL;
	e1=NULL;
	e2=NULL;
}

void StepByStepMode()
{
string filename="input.txt";
	floorx *floors=NULL;
	createfloors(floors);
	elev *e1=NULL, *e2=NULL;
	InitElevStatus(e1,e2,filename);
	int numberofpass=0;
	int numberofdonepass=0;
	ReadPassWtgLists(floors,filename,numberofpass);
	pass** printlist=new pass*[numberofpass];
	int time=0;
	while(passpresent(floors)||e1->PassCnt||e2->PassCnt)
	{
		
		time++;
		//pass pick up and drop off
		if(updatequeues(floors,printlist,numberofdonepass,time))
		{
			satisfypass(floors,e1,e2);
			moveelev(e1,floors[e1->floor],time);
			moveelev(e2,floors[e2->floor],time);
			updateelevdirection(e1);
			updateelevdirection(e2);
			updatepasscurrfloor(e1);
			updatepasscurrfloor(e2);
			filterelev(e1,time,printlist,numberofdonepass);
			filterelev(e2,time,printlist,numberofdonepass);
			transpasstoelev(e1,floors[e1->floor],time);
			transpasstoelev(e2,floors[e2->floor],time);	
		}
		//pass drop off
		else
		{
			moveelev(e1,floors[e1->floor],time);
			moveelev(e2,floors[e2->floor],time);
			updateelevdirection(e1);
			updateelevdirection(e2);
			updatepasscurrfloor(e1);
			updatepasscurrfloor(e2);
			filterelev(e1,time,printlist,numberofdonepass);
			filterelev(e2,time,printlist,numberofdonepass);
		}
		updateUI(e1,e2,floors);
		displaystatus(time,e1,e2,floors,numberofdonepass,printlist);
		cin.get();
	}
	printoutput(printlist,numberofdonepass);
	deletearray(printlist,numberofdonepass);
	delete []floors;
	delete e1;
	delete e2;
	floors=NULL;
	e1=NULL;
	e2=NULL;
}


void SilentMode()
{
	string filename="input.txt";
	floorx *floors=NULL;
	createfloors(floors);
	elev *e1=NULL, *e2=NULL;
	InitElevStatus(e1,e2,filename);
	int numberofpass=0;
	int numberofdonepass=0;
	ReadPassWtgLists(floors,filename,numberofpass);
	pass** printlist=new pass*[numberofpass];
	int time=0;
	while(passpresent(floors)||e1->PassCnt||e2->PassCnt)
	{
		time++;
		//pass pick up and drop off
		if(updatequeues(floors,printlist,numberofdonepass,time))
		{
			satisfypass(floors,e1,e2);
			moveelev(e1,floors[e1->floor],time);
			moveelev(e2,floors[e2->floor],time);
			updateelevdirection(e1);
			updateelevdirection(e2);
			updatepasscurrfloor(e1);
			updatepasscurrfloor(e2);
			filterelev(e1,time,printlist,numberofdonepass);
			filterelev(e2,time,printlist,numberofdonepass);
			transpasstoelev(e1,floors[e1->floor],time);
			transpasstoelev(e2,floors[e2->floor],time);	
		}
		//pass drop off
		else
		{
			moveelev(e1,floors[e1->floor],time);
			moveelev(e2,floors[e2->floor],time);
			updateelevdirection(e1);
			updateelevdirection(e2);
			updatepasscurrfloor(e1);
			updatepasscurrfloor(e2);
			filterelev(e1,time,printlist,numberofdonepass);
			filterelev(e2,time,printlist,numberofdonepass);
		}
	}
	printoutput(printlist,numberofdonepass);
	deletearray(printlist,numberofdonepass);
	delete []floors;
	delete e1;
	delete e2;
	floors=NULL;
	e1=NULL;
	e2=NULL;
}

