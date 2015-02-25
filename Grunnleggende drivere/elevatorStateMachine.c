/*
	elevatorStateMachine.c
	StateMachine logic for elevator
	Sivert and Eirik - 2015
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "elevatorStateMachine.h"
#include "queue.h"

static struct stateInfoT currentState;

//Private function used when initializing
void initializeStateMachine()
{
	initializeQueue();
	currentState.state=stationary;
	currentState.currentFloor=getFloor();
	currentState.floorToReach=-1;
	currentState.currentDir=DIRN_STOP;
	currentState.currentMotorDir=DIRN_STOP;
}

StateT getState(void){ return currentState.state; }

int getFloorToReach(void){ return currentState.floorToReach; }

int getLastFloor(void){ return currentState.currentFloor; }

elev_motor_direction_t getDesiredDir(void) { return currentState.currentDir; }

elev_motor_direction_t getMotorDir(void) { return currentState.currentMotorDir; }

void updateFloorStatus(int floorSensorSignal){
	if(floorSensorSignal != -1)
	{
		currentState.currentFloor=floorSensorSignal;
		elev_set_floor_indicator(floorSensorSignal);
	}
	currentState.floorToReach=getNextFloor(currentState.currentFloor, currentState.currentDir);
	if (getStopButtonSignal())
		currentState.state = stopped;
}

void initializeElevator(void){
	if (!elev_init()) {
		printf("Unable to initialize elevator hardware!\n");
		exit(1);
	}

	setMotorDirection(DIRN_DOWN); 
	while(getFloor() == -1){ /* Between floors */ }
	setMotorDirection(DIRN_STOP);

	/*Initializes the statemachine*/
	initializeQueue();
	currentState.state=stationary;
	currentState.currentFloor=getFloor();
	currentState.floorToReach=-1;
	currentState.currentDir=DIRN_STOP;
	currentState.currentMotorDir=DIRN_STOP;

	printf("\nElevator is now initialized\n");
}

void setEvent(EventT input){
	switch (input){
		case stop:
			//currentState.currentDir=DIRN_STOP;
			currentState.currentMotorDir=DIRN_STOP;
			setMotorDirection(currentState.currentMotorDir);
			currentState.state=stopped;
			
			if (getFloorToReach() == getLastFloor() && getFloor() == -1){
				if (currentState.currentDir == DIRN_DOWN)
					setEvent(desiredFloorAbove);
				else 
					setEvent(desiredFloorBelow);
			}
			else if(getFloorToReach() != -1){
				setEvent(stationaryNoOrder);
			}
			
			printf("stopped\n");
					
			break;
			
		case stationaryNoOrder:
			currentState.currentDir=DIRN_STOP;
			currentState.currentMotorDir=DIRN_STOP;
			setMotorDirection(currentState.currentDir);
			currentState.state=stationary;
			printf("stationaryNoOrder\n");
			break;
			
		case arrivesAtDesiredFloor:
			currentState.currentMotorDir=DIRN_STOP;
			setMotorDirection(currentState.currentMotorDir);
			currentState.state=stationary;

			if(currentState.currentFloor==3)
				currentState.currentDir=DIRN_DOWN;
			if(currentState.currentFloor==0)
				currentState.currentDir=DIRN_UP;

			printf("kjorer arrive at floor\n");
			arriveAtFloor();
			printf("arrivesAtDesiredFloor\n");
			break;
			
		case desiredFloorAbove:
			currentState.currentDir=DIRN_UP;
			currentState.currentMotorDir=DIRN_UP;
			setMotorDirection(currentState.currentMotorDir);
			currentState.state=movingUp;
			printf("desiredFloorAbove\n");
			break;
			
		case desiredFloorBelow:
			currentState.currentDir=DIRN_DOWN;
			currentState.currentMotorDir=DIRN_DOWN;
			setMotorDirection(currentState.currentDir);
			currentState.state=movingDown;
			printf("desiredFloorBelow\n");
			break;
			
		default:
			printf("Something went worng in function setEvent()\n");
			break;
	}
}
