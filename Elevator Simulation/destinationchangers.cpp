#include "structsanddefs.h"
#include "functions.h"



void callelevup (floorx floor, elev *e1, elev *e2)
{
	if(passiswtgup(floor)) 
	{
		if(e1->floor==floor.floornum||e2->floor==floor.floornum) return;
		if((e1->floor<floor.floornum && e1->Dir==UP&&e1->FinalDestination>floor.floornum)|| (e2->floor<floor.floornum && e2->Dir==UP&&e2->FinalDestination>floor.floornum)) return;
		if(floor.floornum>e1->floor && floor.floornum>e2->floor)//awal case kbeera
		{
			if(e1->Dir!=DOWN && e2->Dir!=DOWN)
			{
				if(e1->floor>e2->floor)
					{
						e1->FinalDestination=floor.floornum;
						return;
					}
				else if(e1->floor<e2->floor)
					{
						e2->FinalDestination=floor.floornum;
						return;
					}
				else
					{
						if(e1->Dir==UP)
							{
								e1->FinalDestination=floor.floornum;
								return;
							}
						else
							{
								e2->FinalDestination=floor.floornum;
								return;
							}

					}
			}
			else if(e1->Dir==UP)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
			else if(e2->Dir==UP)
				{
						e2->FinalDestination=floor.floornum;
						return;
				}

			else if(e1->Dir==STOP)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
			else if(e2->Dir==STOP)
				{
						e2->FinalDestination=floor.floornum;
						return;
				}
		}

		else if(e1->floor>floor.floornum && e2->floor>floor.floornum)//tanee case kbeera(to be modified in down and up)
		{
			if(e1->Dir==STOP && e2->Dir==STOP)
			{
				if(e1->floor<e2->floor)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
				else
				{
					e2->FinalDestination=floor.floornum;
					return;
				}
			}
			if(e1->Dir==STOP)
			{
					e1->FinalDestination=floor.floornum;
					return;
			}

			if(e2->Dir==STOP)
			{
					e2->FinalDestination=floor.floornum;
					return;
			}
		}
		else if(e1->floor<floor.floornum)//talet case kbeera
		{
			if(e1->Dir!=DOWN)
			{
				e1->FinalDestination=floor.floornum;
				return;
			}
			else
			{
				if(e2->Dir!=UP&&e2->FinalDestination>floor.floornum)
				{
					e2->FinalDestination=floor.floornum;
					return;
				}
			}
		}

		else //rabe3 case kbeera
		{
			if(e2->Dir!=DOWN)
			{
				e2->FinalDestination=floor.floornum;
				return;
			}
			else
			{
				if(e1->Dir!=UP&&e1->FinalDestination>floor.floornum)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
			}
		}
		}
}

void callelevdown (floorx floor, elev *e1, elev *e2)
{
	if(passiswtgdown(floor)) 
	{
	if(e1->floor==floor.floornum||e2->floor==floor.floornum) return;
	if((e1->floor>floor.floornum && e1->Dir==DOWN && e1->FinalDestination<floor.floornum)|| (e2->floor>floor.floornum && e2->Dir==DOWN&&e2->FinalDestination<floor.floornum)) return;

	if(floor.floornum<e1->floor && floor.floornum<e2->floor)//awal case kbeera
		{
			if(e1->Dir!=UP && e2->Dir!=UP)
			{
				if(e1->floor<e2->floor)
					{
						e1->FinalDestination=floor.floornum;
						return;
					}
				else if(e1->floor>e2->floor)
					{
						e2->FinalDestination=floor.floornum;
						return;
					}
				else
					{
						if(e1->Dir==DOWN)
							{
								e1->FinalDestination=floor.floornum;
								return;
							}
						else
							{
								e2->FinalDestination=floor.floornum;
								return;
							}//////checkpoint

					}
			}
			else if(e1->Dir==DOWN)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
			else if(e2->Dir==DOWN)
				{
						e2->FinalDestination=floor.floornum;
						return;
				}

			else if(e1->Dir==STOP)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
			else if(e2->Dir==STOP)
				{
						e2->FinalDestination=floor.floornum;
						return;
				}
		}////checkpoint
		else if(e1->floor<floor.floornum && e2->floor<floor.floornum)//tanee case kbeera(to be modified in down and up)
		{
			if(e1->Dir==STOP && e2->Dir==STOP)
			{
				if(e1->floor>e2->floor)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
				else
				{
					e2->FinalDestination=floor.floornum;
					return;
				}
			}
			if(e1->Dir==STOP)
			{
					e1->FinalDestination=floor.floornum;
					return;
			}
			if(e2->Dir==STOP)
			{
					e2->FinalDestination=floor.floornum;
					return;
			}
		}
	else if(e1->floor>floor.floornum)//talet case kbeera
		{
			if(e1->Dir!=UP)
			{
				e1->FinalDestination=floor.floornum;
				return;
			}
			else
			{
				if(e2->Dir!=DOWN&&e2->FinalDestination<floor.floornum)
				{
					e2->FinalDestination=floor.floornum;
					return;
				}
			}
		}

	else //rabe3 case kbeera
		{
			if(e2->Dir!=UP)
			{
				e2->FinalDestination=floor.floornum;
				return;
			}
			else
			{
				if(e1->Dir!=DOWN&&e1->FinalDestination<floor.floornum)
				{
					e1->FinalDestination=floor.floornum;
					return;
				}
			}
		}

	}
}

void directelev(elev *e)
{
	if(e->Dir==UP)
	{
		if(e->PassList[e->PassCnt-1]->Dest_floor>e->FinalDestination)
		{
			e->FinalDestination=e->PassList[e->PassCnt-1]->Dest_floor;
		}
	}

	else if(e->Dir==DOWN)
	{
		if(e->PassList[e->PassCnt-1]->Dest_floor<e->FinalDestination)
		{
			e->FinalDestination=e->PassList[e->PassCnt-1]->Dest_floor;
		}
	}

	else
	{
			e->FinalDestination=e->PassList[e->PassCnt-1]->Dest_floor;
			updateelevdirection(e);
	}
}

void satisfypass(floorx* floors,elev* e1,elev* e2)
{
	for(int i=0;i<NumberOfFloors;i++)
	{
		callelevup(floors[i],e1,e2);
		callelevdown(floors[i],e1,e2);
	}
}
