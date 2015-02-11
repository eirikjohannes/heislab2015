
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
	}
	if(currentState.currentFloor==currentState.floorToReach && currentState.state!=stopped){
		setMotorDirection(DIRN_STOP);
		currentState.state=stationary;
		arriveAtFloor();
	}
	else if(currentState.floorToReach>currentState.currentFloor){
		setMotorDirection(DIRN_UP);
		currentState.state=movingUp;
	}
	else if(currentState.floorToReach<currentState.currentFloor){
		setMotorDirection(DIRN_DOWN);
		currentState.state=movingDown;
	}
	if(checkStopButton()){
		setMotorDirection(DIRN_STOP);
		currentState.floorToReach==currentFloor;
		currentState.state=stopped;
	}




}

stateT getState(void)
{
	return currentState.state;
}



