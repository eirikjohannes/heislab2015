#include "hwAndIo.h"
#include "queue.h"
#include "timer.h"
#include "elev.h"
#include "elevatorStateMachine.h"


#define OPEN 1
#define CLOSE 0

static bool stopButtonPushed = false;

bool getStopButtonSignal(void){ return stopButtonPushed; }

int getFloor(void){	return elev_get_floor_sensor_signal(); }

void setMotorDirection(elev_motor_direction_t dir)
{
	//may eventually add delay so that elevator cart 
	//stops at center of floor sensor
	elev_set_motor_direction(dir);
}

//Private function for turning on/of the opendoor light
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
	for (int i=0; i<numberOfFloors; i++)
	{
		for (int j=0; j<numberOfButtons; j++)
		{
			if ((i==0 && j==BUTTON_CALL_DOWN)||
			(i==(numberOfFloors-1)&&j==BUTTON_CALL_UP)) continue;
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
		if(getFloor()!=-1){
			doorCtrl(OPEN);
		}
		deleteAllOrders();
		while(stop)
		{
			elev_set_motor_direction(DIRN_STOP);
			stop=elev_get_stop_signal();
		}
		elev_set_stop_lamp(0);
		if(getFloor()!=-1){
			arriveAtFloor();
		}
		return true;
	}	
	return false;

}

void arriveAtFloor()
{
	doorCtrl(OPEN);
	printOrders();
	startTimer();
	
	while(!timerIsDone()){
		checkStopButton();
		checkButtons();
	}
	deleteOrder(getLastFloor(),getDesiredDir());
	doorCtrl(CLOSE);
	printOrders();
}
