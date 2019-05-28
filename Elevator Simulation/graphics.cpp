#include "graphics.h"

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to set the command window lenght and height for the GUI specification*/
void SetWindow()
{
	system("mode 150,55");   //Set mode to ensure window does not exceed buffer size
	SMALL_RECT WinRect = { 0, 0, CmdWidth, CmdHeight };   //New dimensions for window in 8x12 pixel chars
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to color the cmd text*/
void color(int thecolor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		thecolor | FOREGROUND_INTENSITY);
}
/*A function to draw the 11 floors*/
///////////////////////////////////////////////////////////////////////////////////////
void DrawFloors()
{
	system("CLS");
	SetWindow();
	color(FOREGROUND_RED | FOREGROUND_BLUE);

	for (int j = NumberOfFloors; j >= 0; j--)
	{
		gotoxy(0, (NumberOfFloors - j)*FloorHeight);
		if (j == NumberOfFloors)	cout << "Roof          ";
		else if (j == 0) cout << "Ground Floor ";
		else { cout << "Floor number " << j; }

		for (int i = 0; i < CmdWidth - 15; i++)
			cout << "-";

	}
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(0, CmdHeight - 6);
}
///////////////////////////////////////////////////////////////////////////////////////////
/*A function that draws a passanger */
void DrawPass(pass* P, elev* pE)
{
	int xpass;
	int ypass;
	if (!pE && P->validrequest)	//Not in an elevator
	{
		xpass = 20 + P->num * 2;
		if(P->Source_floor>P->Dest_floor)	ypass = GND_LINE - (P->Current_floor* FloorHeight) - 1;
		else ypass = GND_LINE - (P->Current_floor* FloorHeight)-3;
	}
	else
	{
		xpass = pE->Xstrt + P->num * 2;
		ypass = pE->Ystrt + FloorHeight - 1;
	}

	color(FOREGROUND_GREEN);
	gotoxy(xpass + 1, ypass);
	cout << (char)PassShape << P->ID; //Draw the passanger

	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(0, CmdHeight - 6);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*A function to draw a list of passnegers exist in all regions and ensure there is no overflow in the drawing*/
void DrawPassengers(pass* passes[], int size, elev* pE)
{

	for (int i = 0; i<size; i++)
	{
		if (pE)	//passenger is inside an elevator
			passes[i]->Current_floor = pE->floor; //update passenger floor

		passes[i]->num = i;
		DrawPass(passes[i], pE);
	}

}
/* A function that draws an elevator and its passengers*/
//////////////////////////////////////////////////////////////////////////////////////////////////
void DrawElev(elev & E)
{
	E.Xstrt = (E.E_ID - 1)* (E.W + 2) + WTG_list_Wdth + 5;
	E.Ystrt = GND_LINE - (E.drawfloor + 1)*FloorHeight;
	gotoxy(E.Xstrt, E.Ystrt);
	color(FOREGROUND_RED | FOREGROUND_GREEN);
	for (int i = 0; i < E.W; i++)
	{
		cout << "=";
	}

	gotoxy(E.Xstrt, (E.Ystrt + 1));
	cout << " Elev " << E.E_ID;
	gotoxy(E.Xstrt, (E.Ystrt + FloorHeight));
	for (int i = 0; i < E.W; i++)
	{
		cout << "=";
	}

	for (int j = 0; j < FloorHeight + 1; j++)
	{
		gotoxy(E.Xstrt, E.Ystrt + j);
		cout << "|";
		gotoxy(E.Xstrt + E.W, E.Ystrt + j);
		cout << "|";
	}

	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(0, CmdHeight - 6);

	//Now draw the passengers inside this elevator
	DrawPassengers(E.PassList, E.PassCnt, &E);
}
///////////////////////////////////////////////////////////////////////////////////////

/*Use this function to print a message, statistics to the user*/
void PrintMsg(char*msg)
{
	cout << msg;
}

void updateUI(elev *e1,elev *e2,floorx *floors)
{
	DrawFloors();
	drawqueues(floors);
	DrawElev(*e1);
	DrawElev(*e2);
	gotoxy(0, CmdHeight);
}

void drawqueues(floorx *floors)
{
	pass*ptr;
	for(int i=0;i<NumberOfFloors;i++)
	{
	    ptr=floors[i].uppasswtglistfront;
		while(ptr&&ptr->validrequest)
		{
			DrawPass(ptr,NULL);
			ptr=ptr->next;
		}
		ptr=floors[i].downpasswtglistfront;
		while(ptr&&ptr->validrequest)
		{
			DrawPass(ptr,NULL);
			ptr=ptr->next;
		}
	}
}

void displaystatus(int time, elev* e1, elev* e2,floorx* floors, int numberofdonepass, pass** printlist)
{
	cout<<"Simulation time: "<<time<<endl;
	cout<<"Elevator 1\tFloor="<<e1->floor<<" Direction="<<e1->Dir<<" Capacity="<<e1->Capacity<<" Passenger count="<<e1->PassCnt<<endl;
	cout<<"Elevator 2\tFloor="<<e2->floor<<" Direction="<<e2->Dir<<" Capacity="<<e2->Capacity<<" Passenger count="<<e2->PassCnt<<endl;
	cout<<"Waiting Valid List: "<<updatequeues(floors,printlist,numberofdonepass,time)<<endl;
}
