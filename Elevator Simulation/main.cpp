#include <iostream>
#include "functions.h"
#include "graphics.h"
#include "modes.h"
using namespace std;


int main()
{
	int choice;
	cout<<"Please enter desired simulation mode ():Interacive(1), Step-by-Step(2), Silent(3)"<<endl;
	cin>>choice;
	if(choice==1) InteractiveMode();
	else if(choice==2) StepByStepMode();
	else SilentMode();
	return 0;
}