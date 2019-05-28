#include "functions.h"

/*A function to set the position of cursor on the screen*/

void createfloors(floorx *&floors)
{
	floors=new floorx[NumberOfFloors];
	for(int i=0;i<NumberOfFloors;i++)
	{
		floors[i].floornum=i;
		floors[i].uppasswtglistfront=NULL;
		floors[i].uppasswtglistrear=NULL;
		floors[i].downpasswtglistfront=NULL;
		floors[i].downpasswtglistrear=NULL;
		floors[i].upqcount=0;
		floors[i].downqcount=0;
	}
}

void ReadElevsStatus(float &e1sf, int &e1c, float &e2sf, int &e2c,string filename)
{
	ifstream fin;
	fin.open(filename, ios::in);
	fin >> e1sf >> e1c >> e2sf >> e2c;
	fin.close();
}

void InitElevStatus(elev *&E1, elev *&E2, string filename)
{
	E1=new elev;
	E2=new elev;
	ReadElevsStatus(E1->drawfloor,E1->Capacity,E2->drawfloor,E2->Capacity, filename);
	E1->floor=E1->drawfloor;
	E2->floor=E2->drawfloor;
	E1->PassCnt = 0;
	E2->PassCnt = 0;
	E1->E_ID = 1;
	E2->E_ID = 2;
	E1->Dir=STOP;
	E2->Dir=STOP;
	E1->FinalDestination=E1->floor;
	E2->FinalDestination=E2->floor;
	E1->dooropen=0;
	E2->dooropen=0;
	E1->PassList = new pass*[E1->Capacity];
	E2->PassList = new pass*[E2->Capacity];
}

void enqueuewtglist(pass *addition, pass *&rear, pass *&front,int &qcount)
{
		addition->next=NULL;
		addition->num=qcount;
		qcount++;
		if (front == NULL) //empty list
		{
			rear=addition;
			front = rear;
			return;
		}
		//populated list
		rear->next = addition;
		rear = addition;
}

void ReadPassWtgLists(floorx *floors, string filename,int &num)
{
	ifstream fin(filename, ios::in);
		char dummy[10];
		fin.getline(dummy,10,'\n');
		while (!fin.eof())
		{
			pass *readpass=new pass;
			fin >> readpass->ID;
			if (readpass->ID == -1)//if reached -1 end function
			{
				delete readpass;
				readpass = NULL;
				return;
			}
			num++;
			fin >> readpass->Req_Time >> readpass->Source_floor >> readpass->Dest_floor;//read data
			readpass->Current_floor = readpass->Source_floor;
			readpass->E_ID = 0;
			readpass->num = 0;
			readpass->next = NULL;
			readpass->timeserved=0;
			readpass->timeleave=0;
			readpass->validrequest=0;
			if(readpass->Dest_floor>readpass->Source_floor)
				enqueuewtglist(readpass,floors[readpass->Source_floor].uppasswtglistrear,floors[readpass->Source_floor].uppasswtglistfront,floors[readpass->Source_floor].upqcount);
			else
				enqueuewtglist(readpass,floors[readpass->Source_floor].downpasswtglistrear,floors[readpass->Source_floor].downpasswtglistfront,floors[readpass->Source_floor].downqcount);
		}
}

pass* dequeuewtglist(pass*& front, pass*&rear)
{
	pass* d=front;
		front = front->next;
		if (front == NULL)
		{
			rear = NULL;
		}
		return d;
}

void addpass(pass*addedpass, elev* e)
{
		e->PassCnt++;
	    e->PassList[e->PassCnt - 1] = addedpass;
	    e->PassList[e->PassCnt - 1]->E_ID=e->E_ID;
		e->PassList[e->PassCnt - 1]->num = e->PassCnt-1;
		e->PassList[e->PassCnt - 1]->next=NULL;
}

bool wtglisttoelev(pass*& front, pass*& rear, elev * e,int currtick)
{
	if(e->PassCnt!=e->Capacity)
		{
		front->timeserved = currtick;
		addpass(dequeuewtglist(front, rear), e);
		return 1;
		}
	return 0;
}

void elev2prnt(pass** print, int &count, elev *E, int i, int time)
{
    
    E->PassList[i]->timeleave = time-1;
    Insertsort(E->PassList[i], print, count);
    if (i==E->PassCnt-1)
    {
		E->PassList[--E->PassCnt]=NULL;
        return;
    }
    E->PassList[i] = E->PassList[E->PassCnt - 1];
    E->PassList[--E->PassCnt]=NULL;
    if(E->PassCnt>0)
        E->PassList[i]->num = i;
    return;
}

void deletearray(pass **print, int count) //count is no of passengers, new function
{
	for (int i = 0; i < count; i++)
	{
		delete print[i];
		print[i] = NULL;
	}
}//delete array in the main function

void filterelev(elev *e, int currtick, pass** printlist,int &count)//modified phase 2, modified again
{
	if(e->dooropen)
	{
	for (int i = 0; i < e->PassCnt; i++)
	{
		if (e->floor == e->PassList[i]->Dest_floor)
		{
			elev2prnt(printlist,count,e,i, currtick);
			i--;
		}	
	}
	}
}

int updatequeues(floorx *floors,pass** printlist,int &count,int time)
{
	pass *ptr;
	int counter=0;
	for(int i=0;i<NumberOfFloors;i++)
	{
		ptr=floors[i].uppasswtglistfront;
		while(ptr)
		{
			if(ptr->Req_Time<=time)
			{
				ptr->validrequest=1;
				ptr=ptr->next;
				counter++;
			}
			else break;
		}
		ptr=floors[i].uppasswtglistfront;
		while(ptr)
		{
			if(time-ptr->Req_Time==60)
			{
				ptr->timeserved=ptr->Req_Time+60;
				Insertsort(dequeuewtglist(floors[i].uppasswtglistfront,floors[i].uppasswtglistrear),printlist,count);
				ptr=floors[i].uppasswtglistfront;
				counter--;
			}
			else break;
		}
		ptr=floors[i].downpasswtglistfront;
		while(ptr)
		{
			if(ptr->Req_Time<=time)
			{
				ptr->validrequest=1;
				ptr=ptr->next;
				counter++;
			}
			else break;
		}
		ptr=floors[i].downpasswtglistfront;
		while(ptr)
		{
			if(time-ptr->Req_Time==60)
			{
				ptr->timeserved=ptr->Req_Time+60;
				Insertsort(dequeuewtglist(floors[i].downpasswtglistfront,floors[i].downpasswtglistrear),printlist,count);
				ptr=floors[i].downpasswtglistfront;
				counter--;
			}
			else break;
		}
	}
	return counter;
}

bool passiswtgdown(floorx floor)//modified phase 2
{
	if (floor.downpasswtglistfront)if(floor.downpasswtglistfront->validrequest)return 1;
	return 0;
}

bool passiswtgup(floorx floor)//modified phase 2
{
	if (floor.uppasswtglistfront)if(floor.uppasswtglistfront->validrequest)return 1;
	return 0;
}

void Insertsort(pass* p, pass** print, int &count)
{
	int index=count;
	if(count==0)
	{
		index=0;
		count++;
	}
	else
	{
		while(index!=0&&print[index-1]->timeserved>p->timeserved)
		{
			index--;
		}
		while(index!=0&&print[index-1]->ID>p->ID && print[index-1]->timeserved==p->timeserved)
			{
				index--;
			}
		emptyi(print,count,index);
	}
	print[index]=p;
}

void printoutput(pass**print, int numberofpass)
{
	int sumst = 0;
	int sumwt = 0;
	int stairs = 0;
	float avgst = 0;
	float avgwt = 0;
	float percentstairs;
	ofstream outputfile("output.txt", ios::out);
	for (int i = 0; i< numberofpass; i++)
	{   
		int st = 0;
		int wt = 0;
		if (print[i]->E_ID)
		{
			st = print[i]->timeleave - print[i]->timeserved;
			wt = print[i]->timeserved - print[i]->Req_Time;
		}
		else
		{
			st = 7*(print[i]->Dest_floor-print[i]->Source_floor);
			if(st<0) st=-st;
			wt = 60;
			stairs++;
		}
		outputfile << print[i]->timeserved << "\t" << print[i]->ID <<"\t"<<print[i]->E_ID<< "\t" << wt << "\t" << st << endl;
		sumst = sumst + st;
		sumwt = sumwt + wt;
	}
	avgst = float (sumst) / numberofpass;
	avgwt =  float (sumwt) / numberofpass;
	percentstairs = (float (stairs) / numberofpass) * 100;
	outputfile << "Average service time: " << avgst << endl;
	outputfile << "Average waiting time: " << avgwt << endl;
	outputfile << "Percentage of people taking the stairs: " << percentstairs << endl;
	outputfile.close();
}

void moveelev(elev * e, floorx  floor,int time)
{
	if (e->floor!=e->drawfloor)
	{
		if (e->Dir == UP)
		{
			e->drawfloor += 0.5;
			e->floor=e->drawfloor;
			return;
		}
		else
		{
			e->drawfloor -= 0.5;
			e->floor=e->drawfloor;
			return;
		}
	}
	if (e->Dir == UP)
	{
		for (int i = 0; i<e->PassCnt; i++)
		{
			if (e->PassList[i]->Dest_floor == e->floor)
			{
				e->dooropen=1;
				return;
			}
		}
		if (e->PassCnt == e->Capacity)
		{
			e->drawfloor += 0.5;
			e->floor=e->drawfloor;
			e->dooropen=0;
			return;
		}
		if(passiswtgup(floor))
			{
				e->dooropen=1;
				return;
			}
		e->drawfloor += 0.5;
		e->floor=e->drawfloor;
		e->dooropen=0;

	}
	if (e->Dir == DOWN)
	{
		for (int i = 0; i<e->PassCnt; i++)
		{
			if (e->PassList[i]->Dest_floor == e->floor)
			{
				e->dooropen=1;
				return;
			}
		}
		if (e->PassCnt == e->Capacity)
		{
				e->drawfloor -= 0.5;
				e->floor=ceil(e->drawfloor);
				e->dooropen=0;
				return ;
		}
		if(passiswtgdown(floor))
			{
				e->dooropen=1;
				return;
			}
		e->drawfloor -= 0.5;
		e->floor=ceil(e->drawfloor);
		e->dooropen=0;
	}
	if(e->Dir==STOP)
	{
		for (int i = 0; i<e->PassCnt; i++)
		{
			if (e->PassList[i]->Dest_floor == e->floor)
			{
				e->dooropen=1;
				return;
			}
		}
		if(passiswaitingforsec(floor,time)) e->dooropen=1;
	}
}

bool passpresent(floorx* floors)
{
	for(int i=0;i<NumberOfFloors;i++)
	{
		if (floors[i].downpasswtglistfront) return 1;
		if (floors[i].uppasswtglistfront) return 1;
	}
	return 0;
}

void updateelevdirection(elev* e)
{
	if (e->FinalDestination == e->floor)
		{
			e->Dir = STOP;
			return;
		}
	if(e->Dir==STOP)
	{
		if(e->FinalDestination>e->floor) e->Dir=UP;
		if(e->FinalDestination<e->floor) e->Dir=DOWN;
	}
}

void transpasstoelev(elev* e,floorx &floor,int time)
{
	if(e->floor==e->drawfloor&&e->Capacity>e->PassCnt&&e->dooropen)
	{
	if(e->Dir==UP)
	{
		while(passiswtgup(floor)&&e->Capacity>e->PassCnt)
		{
			if(wtglisttoelev(floor.uppasswtglistfront,floor.uppasswtglistrear,e,time))directelev(e);
		}
	}
	else if(e->Dir==DOWN)
	{
		while(passiswtgdown(floor)&&e->Capacity>e->PassCnt)
		{
			if(wtglisttoelev(floor.downpasswtglistfront,floor.downpasswtglistrear,e,time))directelev(e);
		}
	}
	else if(!passiswtgup(floor)) 
	{
		while(passiswtgdown(floor)&&e->Capacity>e->PassCnt)
		{
			if(wtglisttoelev(floor.downpasswtglistfront,floor.downpasswtglistrear,e,time))directelev(e);
		}
	}
	else if(!passiswtgdown(floor))
	{
		while(passiswtgup(floor)&&e->Capacity>e->PassCnt)
		{
			if(wtglisttoelev(floor.uppasswtglistfront,floor.uppasswtglistrear,e,time))directelev(e);
		}
	}
	else
	{
		if(floor.uppasswtglistfront->Req_Time>floor.downpasswtglistfront->Req_Time)
		{
			while(passiswtgdown(floor)&&e->Capacity>e->PassCnt)
			{
			if(wtglisttoelev(floor.downpasswtglistfront,floor.downpasswtglistrear,e,time))directelev(e);
			}
		}
		else
		{
			while(passiswtgup(floor)&&e->Capacity>e->PassCnt)
			{
			if(wtglisttoelev(floor.uppasswtglistfront,floor.uppasswtglistrear,e,time))directelev(e);
			}
		}
	}
	}
}

void updatepasscurrfloor(elev* e)
{
	for(int i=0;i<e->PassCnt;i++)
	{
		e->PassList[i]->Current_floor=e->drawfloor;
	}
}

void emptyi(pass** print,int &count, int empty)
{
	for(int i=count;i>empty;i--)
	{
		print[i]=print[i-1];
	}
	count++;
}


bool passiswaitingforsec(floorx floor, int time)
{
	if(floor.downpasswtglistfront&&floor.downpasswtglistfront->Req_Time<=time-1) return 1;
	if(floor.uppasswtglistfront&&floor.uppasswtglistfront->Req_Time<=time-1) return 1;
	return 0;
}
/*void phase1_simulate()
{
	floorx *floors=NULL;
	createfloors(floors);
	elev *e1=NULL, *e2=NULL;
	InitElevStatus(e1,e2);
	ReadPassWtgLists(floors);
	int time=0;
	while(1)
	{
		time++;
		cout<<"Time="<<time<<endl;
		cout<<"Number of valid requests: "<<updatequeuevalidity(floors,time)<<endl;
		printelev(e1);
		printelev(e2);
		if(!(passiswtg(floors)||e1->PassCnt!=0||e2->PassCnt!=0))break;
		if(passiswtg(floors))
		{
		for(int i=0;i<NumberOfFloors;i++)
		{
			bool nowait=1;
			while(floors[i].uppasswtglistfront&&nowait)
			{
				if(floors[i].uppasswtglistfront->validrequest)
				{
					if(i%2==0)
					    nowait=wtglisttoelev(floors[i].uppasswtglistfront,floors[i].uppasswtglistrear,e2);
					else
						nowait=wtglisttoelev(floors[i].uppasswtglistfront,floors[i].uppasswtglistrear,e1);
				}
				else break;
			}
			nowait=1;
			while(floors[i].downpasswtglistfront&&nowait)
			{
				if(floors[i].downpasswtglistfront->validrequest)
				{
					if(i%2==0)
					    nowait=wtglisttoelev(floors[i].downpasswtglistfront,floors[i].downpasswtglistrear,e2);
					else
						nowait=wtglisttoelev(floors[i].downpasswtglistfront,floors[i].downpasswtglistrear,e1);
				}
				else break;
			}
		}
		}
		updatetimeinelev(e1);
		updatetimeinelev(e2);
		if(time>=5)
		{
			if(e1->PassCnt!=0||e2->PassCnt!=0)
			{
				filterelev(e1);
				filterelev(e2);
			}
		}
	}
	delete []floors;
	floors=NULL;
	delete e1;
	e1=NULL;
	delete e2;
	e2=NULL;
}*/

