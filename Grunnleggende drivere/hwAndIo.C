
#include "hwAndIo.h"
#include "queue.h"
#include "timer.h"
#include "testelev.h"
//#include "elevatorStateMachine.h"

//#define DOWN 0
//#define UP 1
#define OPEN 1
#define CLOSE 0


void setMotorDirection(elev_motor_direction_t dir)
{
	//Husk å stoppe heisen skikkelig....
	elev_set_motor_direction(dir);
}

void doorCtrl(int ctrl)
{
	if (ctrl==OPEN){
		elev_set_door_open_lamp(1);	
	}
	else if (ctrl==CLOSE){
		elev_set_door_open_lamp(0);	
	}
}
void checkButtons(void)
{
	checkStopButton();
	int floor=4,buttons=3;
	for (int i=0; i<floor; i++)
	{
		for (int j=0; j<buttons; j++)
		{
			if ((i==0 && j==1)||(i==3&&j==0)) continue;
			if(elev_get_button_signal((elev_button_type_t)j,i))
			{
				order((elev_button_type_t)j,i);
				stopButtonPushed=false;
			}
		}
	}
}

bool checkStopButton(void)
{
	bool stop=true;
	stop=elev_get_stop_signal();
	if(stop)
	{
		stopButtonPushed=true;
		elev_set_stop_lamp(1);
		while(stop)
		{
			elev_set_motor_direction(DIRN_STOP);
			stop=elev_get_stop_signal();
		}
		elev_set_stop_lamp(0);
		deleteAllOrders();
		return true;
	}	
	return false;

}

void arriveAtFloor()
{
	doorCtrl(OPEN);
	startTimer();
	while(!timerIsDone()){
		checkStopButton();
		checkButtons();
	}
	elev_motor_direction_t currentDir=(getState()).currentDir;
	deleteOrder(getFloor(),currentDir);
	doorCtrl(CLOSE);
}

int getFloor(){
	return elev_get_floor_sensor_signal();
}