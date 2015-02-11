
#include "elevatorStateMachine.h"


static stateT currentState;

initializeStateMachine()
{
	
}

void setEvent(stateT desiredState, int currentFloor, elev_motor_direction_t currentDir,queueNode *currentOrderBeingExecuted)
{
	currentFloor=currentFloor;
	currentDir = currentDir;
	currentState=desiredState;
}

stateT& getState(void)
{
	return &currentState;
}



