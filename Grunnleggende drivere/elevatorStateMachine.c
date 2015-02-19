
#include "elevatorStateMachine.h"
#include <stdio.h>


static struct stateInfoT currentState;


void initializeStateMachine()
{
	//remember to init elev before doing this!
	initializeQueue();
	currentState.state=stationary;
	currentState.currentFloor=0;
	currentState.floorToReach=0;
	currentState.currentDir=DIRN_STOP;
	currentState.currentMotorDir=DIRN_STOP;
}

void setEvent()
{	
	int floorSensor=0;
	floorSensor=getFloor();
	if(floorSensor!=-1)
	{
		currentState.currentFloor=floorSensor;
		elev_set_floor_indicator(currentState.currentFloor);
	}
	
	
	checkButtons();
	currentState.floorToReach=getNextFloor(currentState.currentFloor, currentState.currentDir);
	
	
	
	//Checking the stopbutton
	if(checkStopButton() || stopButtonPushed){

		currentState.currentMotorDir=DIRN_STOP;
		setMotorDirection(currentState.currentMotorDir);
		currentState.floorToReach=-1;
		currentState.state=stopped;
	}
	//Updating the floor indicator and the currentfloor status
	
	
	//While we dont have any orders, and the elevator isnt stopped by the stop button
	if(currentState.floorToReach==-1 && currentState.state!=stopped)//&& getFloor()!=-1)
	{
		
		currentState.currentDir=DIRN_STOP;
		currentState.currentMotorDir=DIRN_STOP;
		setMotorDirection(currentState.currentDir);
		currentState.state=stationary;
	}

		//Arrives at the correct floor
	else if(currentState.currentFloor==currentState.floorToReach && 
	currentState.state!=stopped &&currentState.floorToReach!=-1 &&floorSensor!=-1)
	{
		currentState.currentMotorDir=DIRN_STOP;
		setMotorDirection(currentState.currentMotorDir);
		currentState.state=stationary;
		
		if(currentState.currentFloor==3)
			currentState.currentDir=DIRN_DOWN;
		if(currentState.currentFloor==0)
			currentState.currentDir=DIRN_UP;
		printf("kjorer arrive at floor\n");
		arriveAtFloor();
	}

	//If the elevator is stuck between floors after stopbuttonevent, do this
	else if(currentState.state==stopped && floorSensor==-1 && 
	currentState.floorToReach==currentState.currentFloor)
	{
		//Invertering av retning
		currentState.currentDir=((elev_motor_direction_t)((currentState.currentDir)*-1));
		currentState.currentMotorDir=currentState.currentDir;		
		setMotorDirection(currentState.currentMotorDir);
		if(currentState.currentMotorDir)
			currentState.state=movingDown;
		else
			currentState.state=movingUp;
	}

	//If floor to reach is above the current floor
	else if(currentState.floorToReach>currentState.currentFloor 
	&&currentState.floorToReach!=-1){
		currentState.currentDir=DIRN_UP;
		currentState.currentMotorDir=DIRN_UP;
		setMotorDirection(currentState.currentMotorDir);
		currentState.state=movingUp;
	}
	//if the floor to reach is below the current floor
	else if(currentState.floorToReach<currentState.currentFloor
	 &&currentState.floorToReach!=-1){
	 	printf("Got here, eirik was right somehow\n");
		currentState.currentDir=DIRN_DOWN;
		currentState.currentMotorDir=DIRN_DOWN;
		setMotorDirection(currentState.currentDir);
		currentState.state=movingDown;
	}
	
}

struct stateInfoT getState(void)
{
	return currentState;
}



