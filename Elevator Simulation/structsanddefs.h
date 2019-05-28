#ifndef sh
#define sh

//constants
#define NumberOfFloors  11
#define FloorHeight	    4

#define CmdWidth		150
#define CmdHeight		55

#define ElevWidth		40
#define ElevHeight	    3

#define WTG_list_Wdth   50	//Width of the waiting list on the screen

#define ELEV1XStrt		60
//#define ELEV1YStrt		FloorHeight*NumberOfFloors
//Ground line position on the screen
#define GND_LINE		FloorHeight*NumberOfFloors

#define ELEV2XStrt		ELEV1XStrt + ElevWidth + 5 
//#define ELEV2YStrt		FloorHeight*NumberOfFloors

#define PassShape		219  //ASCII code of passenger char shape 

enum DIRECTION
{
	STOP, UP, DOWN  //Possible elevator states 
};

struct pass
{
	int ID;				//Each passenger has a unique ID (sequence number)
	int E_ID;			//which elevator 1 or 2 (0 if not inside any elevator)
	float Current_floor;	//For drawing (Graphical info) 
	int Source_floor;	//Source Floor
	int Dest_floor;		//Destination Floor
	int Req_Time;		//Request Time
	bool validrequest;
	int num; // refers to the passenger's number in the elev or on the floor , just to draw without overlapping
	int timeserved;
	int timeleave;
	pass* next;
};

struct elev
{
	//Graphical info for elevator
	int Xstrt;
	int Ystrt;
	const static int W = ElevWidth;	//width
	const static int L = ElevHeight;  //Height
	float drawfloor;
									  //Simulation info for elevetor
	int floor;		//current floor
	bool dooropen;
	DIRECTION Dir;	//elevator moving direction
	int E_ID;		// elevator ID
	int Capacity;	//elevator capacity
	int FinalDestination;
	// check if equal zero is correct
	
	int PassCnt;	//number of current passengers in this elevator

					//Note: for the sake of demo, passengers list in the elevator is created using very simple
					//Data Structure
					//You MUST change that to a more suitable DS
	pass **PassList;
};

struct floorx
{
	int upqcount;
	int downqcount;
	int floornum;
	pass *uppasswtglistrear;
	pass *uppasswtglistfront;
	pass *downpasswtglistrear;
	pass *downpasswtglistfront;
};

#endif