
#include "hwAndIo.h"
#include "queue.h"
#include <stdbool.h>

#define DOWN=0;
#define UP=1;

setMotorDirection(elev_motor_direction_t dir)
{
	elev_set_motor_direction(dir);
}

void checkButtons(void)
{
	int floor=4,buttons=3;
	for (int i=0; i<floor; i++)
	{
		for (int j=0; j<buttons; j++)
		{
			if(elev_get_button_signal(j,i) && j==2)
			{
				orderIn(i,getState().currentFloor,getState().currentDir);
				elev_set_button_lamp(j,i,1);
			}
			else if(elev_get_button_signal(j,i) && j==1) //down btn
			{
				orderOut(i,DOWN,getState().currentFloor,getState().currentDir);
				elev_set_button_lamp(j,i,1);
			}
			else if(elev_get_button_signal(j,i) && j==0) //up btn
			{
				orderOut(i,UP,getState().currentFloor,getState().currentDir);
				elev_set_button_lamp(j,i,1);
			}
		}
	}
}

void checkStopButton(void)
{
	bool stop=false;
	stop=elev_get_stop_signal();
	if(stop)
	{
		elev_set_stop_lamp(1);
		while(stop)
		{
			elev_set_motor_direction(DIRN_STOP);
			stop=elev_get_stop_signal();
		}
		elev_set_stop_lamp(0);
		deleteAllOrders();
		
	}	
}

void arriveAtFloor(void)
{
	
}
