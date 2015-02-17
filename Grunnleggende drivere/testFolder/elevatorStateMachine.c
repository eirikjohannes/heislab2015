
#include "elevatorStateMachine.h"


static stateInfoT currentState;

initializeStateMachine()
{
	//remember to init elev before doing this!
	initializeQueue();
	currentState.state=stationary;
	currentState.currentFloor=0;
	currentState.floorToReach=0;
	currentState.currentDir=DIRN_STOP;
}

void setEvent()
{	
	currentState.floorToReach=getNextFloor(currentState.currentFloor, currentState.currentDir);
	if(getFloor()!=-1){
		currentState.currentFloor=getFloor();
		elev_set_floor_indicator(currentState.currentFloor);
	}
	if(currentState.currentFloor==currentState.floorToReach && currentState.state!=stopped){
		currentState.currentDir=DIRN_STOP;
		setMotorDirection(currentState.currentDir);
		currentState.state=stationary;
		arriveAtFloor();
	}
	else if(currentState.floorToReach>currentState.currentFloor){
		currentState.currentDir=DIRN_UP;
		setMotorDirection(currentState.currentDir);
		currentState.state=movingUp;
	}
	else if(currentState.floorToReach<currentState.currentFloor){
		currentState.currentDir=DIRN_DOWN;
		setMotorDirection(currentState.currentDir);
		currentState.state=movingDown;
	}
	if(checkStopButton() || stopButtonPushed){
		currentState.currentDir=DIRN_STOP;
		setMotorDirection(currentState.currentDir);
		currentState.floorToReach==currentFloor;
		currentState.state=stopped;
	}
}

stateT getState(void)
{
	return currentState.state;
}



